/*
 * uhcmod_main.c
 * 
 * Copyright 2012 Kamil Cukrowski <kamil@dyzio.pl>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 * ---------------------------------------------------------------------
 * 
 * most of usb-code is based on USB Skeleton driver - 2.2 , from kernel ver3.5
 * thank you Greg Kroah-Hartman (greg@kroah.com)
 * 
 */
#define _UHCMOD_
#define UHCMOD_VERSION "0.1.6"

#include <generated/autoconf.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/usb.h>

#include "config.h"
#include "uhcmod_lib.h"

#include "hd44780-inst-def.h"
#include "cgram_default.h"
#include "hd44780_charmap.h"


static uint checktime = 5;
module_param(checktime, uint, 0444);
MODULE_PARM_DESC(checktime, "time in sec after checking timer expires. default:5");

static uint lcd_num = 8;
module_param(lcd_num, uint, 0444);
MODULE_PARM_DESC(lcd_num, "default number of controllers that new device has. default:8");\

static unsigned char uhcmod_number = 0; /* number of devices connected */

/* table of devices that work with this driver */
static const struct usb_device_id uhcmod_table[] = {
	{ USB_DEVICE(UHCMOD_USB_VENDOR_ID, UHCMOD_USB_PRODUCT_ID) },
	{ }					/* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, uhcmod_table);

static struct usb_driver uhcmod_driver;

/* ******************* help functions ****************** */

/* realese function to kref counter - uhcmod_dev *dev->kref; */
static void uhcmod_delete(struct kref *kref)
{
	struct uhcmod_dev *dev = container_of(kref, struct uhcmod_dev, kref);
	
	uhcmod_number--;
	
	usb_put_dev(dev->udev);
	kfree(dev->state);
	kfree(dev->lcd);
	kfree(dev->out_buffer);
	kfree(dev->in_buffer);
	kfree(dev);
}

/* ********************** usb send and recv and add to buffer functions *********************  */

static void uhcmod_usb_flush_send_callback(struct urb *urb)
{
	struct uhcmod_dev *dev;
	
	dev = urb->context;
	
	PDEBUG_HD44780(" %s \n", __func__);

	/* sync/async unlink faults aren't errors */
	if (urb->status) {
		if (!(urb->status == -ENOENT ||
		    urb->status == -ECONNRESET ||
		    urb->status == -ESHUTDOWN))
			PERROR("%s - nonzero write bulk status received: %d\n",
				__func__, urb->status);

		dev->errors = urb->status;
	} else {
		dev->usb_write_bytes_count += urb->actual_length;
		dev->usb_write_count++;
	}
	
	
	/* free up our allocated buffer */
	usb_free_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
	up(&dev->limit_sem);
}

static void _uhcmod_usb_do_send(struct uhcmod_dev *dev, char *what, size_t writesize)
{
	int retval;
	struct urb *urb = NULL;
	char *buf = NULL;
	
	/*
	 * limit the number of URBs in flight to stop a user from using up all
	 * RAM
	 */
	retval = down_interruptible(&dev->limit_sem);
	if (retval) {
		if (retval == -EINTR) {
			/* we were interrupted, probably we are going to close */
			retval = 0;
			goto error;
		}
		/* when it was other reason, its a normal error */
		goto error;
	}

	/* create a urb, and a buffer for it, and copy the data to the urb */
	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb) {
		retval = -ENOMEM;
		goto error;
	}

	buf = usb_alloc_coherent(dev->udev, writesize, GFP_KERNEL, &urb->transfer_dma);
	if (!buf) {
		retval = -ENOMEM;
		goto error;
	}
	if (writesize)
		memcpy(buf, what, writesize);

	/* initialize the urb properly */
	usb_fill_bulk_urb(urb, dev->udev,
			usb_sndbulkpipe(dev->udev, dev->out_endpointAddr),
			buf,
			writesize,
			uhcmod_usb_flush_send_callback,
			dev);
	usb_anchor_urb(urb, &dev->submitted);

	/* send the data out the bulk port */
	retval = usb_submit_urb(urb, GFP_KERNEL);
	if (retval) {
		PERROR("%s - failed submitting write urb, error %d\n",
			__func__, retval);
		goto error_unanchor;
	}

	/*
	 * release our reference to this urb, the USB core will eventually free
	 * it entirely
	 */
	usb_free_urb(urb);
	
	return;

error_unanchor:
	usb_unanchor_urb(urb);
error:
	if (urb) {
		usb_free_coherent(dev->udev, writesize, buf, urb->transfer_dma);
		usb_free_urb(urb);
	}
	up(&dev->limit_sem);

	dev->errors = retval;
}

static void uhcmod_usb_flush_send(struct uhcmod_dev *dev)
{
	size_t writesize;
	
	PDEBUG_HD44780(" %s \n", __func__);
		
	if (dev->errors)
		return;
	
	/* protect against array exceding */
	if (dev->out_filled > dev->out_size)
		dev->out_filled = dev->out_size;
	
	writesize = dev->out_filled;
	dev->out_filled = 0; /* buffer copied */
	
	if (!writesize)
		return;
	
	_uhcmod_usb_do_send(dev, dev->out_buffer, writesize);
}

static void uhcmod_usb_flush_send_block(struct uhcmod_dev *dev)
{
	int retval;
	
	PDEBUG_HD44780(" %s \n", __func__);
	
	/* flush all sends */
	uhcmod_usb_flush_send(dev);
	
	/* as far as we are sending data to one endpoint, it will be ready
	 * after processing all the data sended, so we just send an empty packet
	 * at will be accepted only after tha data from other urbs has been processed */
	_uhcmod_usb_do_send(dev, dev->out_buffer, 0);
	
	/* wait for these to complete */
	if (dev->errors)
		return;
	
	retval = usb_wait_anchor_empty_timeout(&dev->submitted, HZ*10);
	if (retval < 0) {
		dev->errors = retval;
		return;
	}
}

static void _uhcmod_usb_add_send(struct uhcmod_dev *dev, u8 data)
{
	if (dev->errors)
		return;
	
	if (dev->out_filled >= dev->out_size) {
		/* send the whole basket */
		uhcmod_usb_flush_send(dev);
		if (dev->errors) {
			/* something is wrong, we will try to carry on */
			return;
		}
	}
	dev->out_buffer[dev->out_filled] = data;
	dev->out_filled++;
}

static void uhcmod_usb_add_send(struct uhcmod_dev *dev, u8 data) 
{
	_uhcmod_usb_add_send(dev, data);
	//uhcmod_usb_add_send(dev, ~data);
}

static void _uhcmod_usb_do_recv(struct uhcmod_dev *dev, unsigned char *in_buffer, size_t in_size, int *in_filled) 
{
	int retval;
	
	PDEBUG(" %s \n", __func__);
	
	if (dev->errors)
		return;
		
	retval = usb_bulk_msg(dev->udev,
				usb_rcvbulkpipe(dev->udev, dev->in_endpointAddr),
				in_buffer,
				in_size,
				in_filled,
				HZ);
	
	
	if (retval <= 0 && retval != -ETIMEDOUT)
		dev->errors = retval;
	else
		*in_filled = 0;
	
	dev->usb_read_bytes_count+=*in_filled;
	dev->usb_read_count++;
}

static void uhcmod_usb_recv(struct uhcmod_dev *dev,  unsigned char *in_buffer, size_t in_size, int *in_filled)
{
	PDEBUG(" %s \n", __func__);
	
	/* set usb SET_READ on out in_endpoint
	 * if this was done before nothing will happen (device should ignore it then ) */
	uhcmod_usb_add_send(dev, CAKE_FILLING_SET_READ);
	/* need to wait for usb to process out request, because SET_READ was the last .. 
	 * this also wait until the last send is completed, so we wait for getting all reads*/
	uhcmod_usb_flush_send_block(dev);
	
	_uhcmod_usb_do_recv(dev, in_buffer, in_size, in_filled);
}

/* ***************************** macros for global use ***************************** */
/* TODO use inline for them */

static inline void uhcmod_usb_add_send2(struct uhcmod_dev *dev, unsigned char flags, unsigned char command) 
{ 
	uhcmod_usb_add_send(dev, flags);
	uhcmod_usb_add_send(dev, command);
}

#define write_inst(dev, ctrl, inst)	uhcmod_usb_add_send2(dev, CAKE_FILLING_RAW | (ctrl<<2) | RS_INST | RW_WRITE, inst)
#define write_data(dev, ctrl, data)	uhcmod_usb_add_send2(dev, CAKE_FILLING_RAW | (ctrl<<2) | RS_DATA | RW_WRITE, data)
#define write_inst_all(dev, inst)	uhcmod_usb_add_send2(dev, CAKE_FILLING_ALL_RAW | RS_INST | RW_WRITE, inst)
#define write_data_all(dev, data)	uhcmod_usb_add_send2(dev, CAKE_FILLING_ALL_RAW | RS_DATA | RW_WRITE, data)

#define send_read_data_all(dev)		uhcmod_usb_add_send(dev, CAKE_FILLING_ALL_RAW | RS_DATA | RW_READ)

#define send_num_read(dev, ctrl, num)	uhcmod_usb_add_send2(dev,  CAKE_FILLING_NUM_READ | ctrl<<2 | RW_READ | RS_DATA, num)
#define send_set_read(dev)		uhcmod_usb_add_send(dev, CAKE_FILLING_SET_READ)

#define read_data(dev)			uhcmod_usb_recv(dev, dev->in_buffer, dev->in_size, &dev->in_filled)

static void clear_read_data_buffer(struct uhcmod_dev *dev)
{
	int i;
	/* variable i does not allow to sleep here forerver */
	for ( i=0xff; i ; i-- ) {
		read_data(dev);
		if (dev->errors)
			break;
		if (!dev->in_filled)
			break;
	}
}

/* ***************************** command level operation functions ***************************** */

static void _cursor_ctrl_set(struct uhcmod_dev *dev, unsigned char ctrl_nr, unsigned char row, unsigned char col)
{
	struct uhcmod_lcd *lcd = &dev->lcd[ctrl_nr];
	lcd->col = col;
	lcd->row = row;
	write_inst(dev, ctrl_nr, HD44780_DDRAM_ADDRESS | ( row << 6 ) | col );
}

static void cursor_ctrl_set(struct uhcmod_dev *dev, unsigned char ctrl_nr, unsigned char row, unsigned char col)
{
	struct uhcmod_lcd *lcd = &dev->lcd[ctrl_nr];
	row &= 0x1; /* wrap row, we have only 2 row displays */
	if ( lcd->row == row && lcd->col == col ) 
		return;
	PDEBUG_OPERATION(" cursor_ctrl_set ctrlnr: %d row/col:%2d/%2d \n", ctrl_nr, row, col);
	_cursor_ctrl_set(dev, ctrl_nr, row, col);
}

static void cursor_ctrl_inc(struct uhcmod_dev *dev, unsigned char ctrl_nr)
{
	struct uhcmod_lcd *lcd = &dev->lcd[ctrl_nr];
	
	if (lcd->col < (DISP_COLS-1) ) {
		lcd->col++;
	} else {
		lcd->col = 0;
		/* (row++)&1 = (row^1)&1 */
		lcd->row = (lcd->row&0x01)^0x01;
	}
}

static void cursor_virtual_inc(struct uhcmod_dev *dev)
{
	if ( dev->col < (DISP_COLS - 1) ) {
		++dev->col;
	} else if ( !test_bit(FLAG_WRAP_OFF, &dev->flags ) && 
			dev->row < (DISP_ROWS - 1) ) {
		dev->col = 0;
		++dev->row;
	}
}

static void _write_DDRAM(struct uhcmod_dev *dev, unsigned char row, unsigned char col, unsigned char data)
{
	const unsigned char ctrl_nr = row / ROWS_PER_CTRL;
	
	PDEBUG_OPERATION("wDDRAM: row:%d per_ctr:%d col:%d per_ctr:%d  data: %#2x %1c stt: %#2x %1c",
		row,ROWS_PER_CTRL,col, dev->lcd_num,  data, data, dev->state[row][col], dev->state[row][col]);
	
	dev->state[row][col] = data;
	cursor_ctrl_set(dev, ctrl_nr, row, col);
	write_data(dev, ctrl_nr, data);
	cursor_ctrl_inc(dev, ctrl_nr);
}

static void write_DDRAM(struct uhcmod_dev *dev, unsigned char row, unsigned char col, unsigned char data)
{
	/* check if we really need to write anything */
	if ( dev->state[row][col] != data ) {
		_write_DDRAM(dev, row, col, data);
	}
}

/** write cgram to the specyfic controler on specified port */
static void write_CGRAM(struct uhcmod_dev *dev, unsigned char ctrl_nr, unsigned char cgram_index, unsigned char *cgram_pixels) 
{
	struct uhcmod_lcd *lcd = &dev->lcd[ctrl_nr];
	int i;
	
	PDEBUG_OPERATION(" %s: ctrl_nr:%d cgram_index:%d \n", __func__, ctrl_nr, cgram_index); 
	
	/* check if cgram changes */
	if( !memcmp(lcd->cgram[cgram_index], cgram_pixels, 8*sizeof(cgram_pixels)) ) 
		return;
	
	/* x<<3 is faster then x*8 */
	write_inst(dev, ctrl_nr, HD44780_CGRAM_ADDRESS | ( cgram_index<<3 ) );
	for (i = 0; i < 8; i++ ) {
		lcd->cgram[cgram_index][i] = cgram_pixels[i];
		write_data(dev, ctrl_nr, cgram_pixels[ i ] );
	}
	
	/* theres not much documentation about writing CGRAM and aspecially about reading[!] CGRAM,
	 * ( theres too much and too less documentation on hd44780 )
	 * in my experience after writing one CGRAM (sending CGRAM_ADDRESS and writing 8 cgram data)
	 * then after[?] writingn the last cgram data the hd44780's cursor gets incremented (like in cursor_ctrl_inc(..) ).
	 * if we will attempt after it to do a write to the hd44780 we will write to the next cgram 
	 * (thats not what we want), so we reset cursor to DDRAM position */
	_cursor_ctrl_set(dev, ctrl_nr, lcd->row, lcd->col);
}

/** write cgram to all lcds */
static void write_CGRAM_all(struct uhcmod_dev *dev, unsigned char cgram_index, unsigned char *cgram_pixels)
{
	unsigned char i, j;
	PDEBUG_OPERATION(" %s: cgram_index:%d \n", __func__, cgram_index); 
	
	/* x<<3 is faster then x*8 */
	write_inst_all(dev, HD44780_CGRAM_ADDRESS | ( cgram_index<<3 ) );
	for (i = 0; i < 8; i++ ) {
		const unsigned char cgram_pixel = cgram_pixels[i];
		
		for (j=0; j<dev->lcd_num; j++) {
			dev->lcd[j].cgram[cgram_index][i] = cgram_pixel;
		}
		write_data_all(dev, cgram_pixel);
	}
	
	/* read comment in write_CGRAM */
	for (i = 0; i < dev->lcd_num; i++ ) {
		_cursor_ctrl_set(dev, i, dev->lcd[i].row, dev->lcd[i].col);
	}
}

/* initialize all controllers */
static int init_displays (struct uhcmod_dev *dev)
{
	int i;
#ifdef LOAD_CGRAM
	char cg[8][8] = DEFAULT_CGRAM;
#endif
	
	PDEBUG("%s", __func__);
	
	write_inst_all(dev,  HD44780_FS_DATAWIDTH8BIT |
			HD44780_FS_TWOLINES |
			HD44780_FS_5x8DOTS);
	write_inst_all(dev,  HD44780_DOOC_DISPLAYON |
			HD44780_DOOC_CURSOROFF |
			HD44780_DOOC_CURSORNOBLINK);
	write_inst_all(dev,  HD44780_CLRDISP);
	write_inst_all(dev,  HD44780_EMS_INC | HD44780_EMS_NOSHIFT);
	/* initialization ends */
	
	/*
	 * write cgram if it is so defined in config.h, config.h should
	 * include specyfic file with table cg[8][8] and function init_charmap() 
	 * This writes all 8 entire (5x8) characters to the CGRAM from cg[i]
	 */
	PDEBUG_OPERATION(" WRITING CGRAM \n");
	for (i = 0; i < 8; i++ ) {
#ifdef LOAD_CGRAM
		write_CGRAM_all(dev, i, cg[i]);
#else
		write_CGRAM_all(dev, i, "00000000");
#endif
	}
	
	PDEBUG_OPERATION("RET HOME\n");
	write_inst_all(dev,  HD44780_RETURNHOME );
	
	for (i = 0; i < dev->lcd_num; i++ )
		_cursor_ctrl_set(dev, i, 0, 0);
	
	clear_read_data_buffer(dev);
	
	write_inst_all(dev, HD44780_CLRDISP);
	for (i=0; i<DISP_ROWS; i++) {
		memset(dev->state[i], ' ', DISP_COLS);
	}
	
	uhcmod_usb_flush_send(dev);
	
	return (dev->errors);
}

/* ************************** getting config from device **************** */

static void get_pic_config(struct uhcmod_dev *dev)
{
	/* this is supported up to 0x0006 realese */
	char buffer[8], again_buffer[8];
	int i;
	
	mutex_lock(&dev->io_mutex);
	
	/* discard any data */
	do {
		read_data(dev);
	} while(dev->in_filled);
	
	/* read 8 bytes */
	uhcmod_usb_add_send(dev, CAKE_FILLING_GET_CONFIG);
	uhcmod_usb_add_send(dev, CAKE_FILLING_SET_READ);
	read_data(dev);
	if (dev->errors || !dev->in_filled ) goto error;
	if ( dev->in_filled != 8 ) goto error;
	memcpy(buffer, dev->in_buffer, sizeof(buffer));
		
	/* read again */
	uhcmod_usb_add_send(dev, CAKE_FILLING_GET_CONFIG);
	uhcmod_usb_add_send(dev, CAKE_FILLING_SET_READ);
	read_data(dev);
	if (dev->errors || !dev->in_filled ) goto error;
	if ( dev->in_filled != 8 ) goto error;
	memcpy(again_buffer, dev->in_buffer, sizeof(again_buffer));
	
	/* check if its the same */
	for(i=0;i<8;i++)
		if ( buffer[i] != again_buffer[i] ) {
			PERROR("buffers not the same %d %x %x ", i, buffer[i], again_buffer[i]);
			goto error;
		}
	
	do {
		/* from specyfication */
		const int _disp_cols = buffer[0];
		const int _disp_rows = buffer[1];
		const int _num_controllers = buffer[2];
		const int _rows_per_ctrl = buffer[3];
		
		/* check input */
		if ( _disp_cols != DISP_COLS ) goto error;
		if ( _rows_per_ctrl != ROWS_PER_CTRL ) goto error;
		if ( _disp_rows != _rows_per_ctrl * _num_controllers ) goto error;
		
		/* lcd_num is max for controllers num */
		if ( _num_controllers > lcd_num ) goto error;
		
		/* finally */
		dev->lcd_num = _num_controllers;
		
	} while(0);
	
	mutex_unlock(&dev->io_mutex);
	return;
	
error:
	mutex_unlock(&dev->io_mutex);
	dev->lcd_num = lcd_num;
}

/* ************************ getting info from device ****************** */

static void get_pic_info(struct uhcmod_dev *dev)
{
	/* TODO */
	/* this is supported up to 0x0006 release */
	return;
}

/* ***************************  error fixing and checking functions ***************************  */

static void _check_and_fix_error(struct uhcmod_dev *dev, unsigned char ctrl_nr, unsigned char row, unsigned char col, unsigned char is_now, unsigned char should_be)
{
	/* check for error */
	if (is_now == should_be)
		/* no error, its all right */
		return;
	
	/* [!] error found ! rewrite the proper character (dev->state[row][col]) to cell with error */
	PDEBUG_CHECKER_ERROR("ERROR row %d col %d ctrl_nr %d: was %x \'%c\' should_be %x \'%c\' \n", row, col, ctrl_nr, is_now, is_now, should_be, should_be);
	
	/* write should_be on a specified row and col 
	 * do not use write_DDRAM here, it checks if dev->state == data */
	_write_DDRAM(dev, row, col, should_be);
	
	/* increment errors counter */
	dev->lcd[ctrl_nr].errors_count++;
}

static void _fixer_method_raw_all(struct uhcmod_dev *dev)
{
	int i;
	int reads_awaited = 0;
	int bufpos = 0;
	
	
	PDEBUG_CHECKER(" %s \n", __func__);
	
	/* ok, how it works
	 * it uses the method of reading from all lcds, so we
	 * set DDRAM address to 0,0
	 * send _RAW_ALL with RW_READ flag
	 * this reads one char from lcd 0 up to lcd number dev->lcd_num
	 * we read the returned values and
	 * and check the values with our dev->state */
	 
	
	dev->in_filled = 0;
	
	for (i=0; i<DISP_SIZE; i++) {
		const unsigned char row_ctrl = (i/dev->lcd_num) / DISP_COLS;
		const unsigned char col = (i/dev->lcd_num) % DISP_COLS;
		const unsigned char ctrl_nr = i%dev->lcd_num;
		const unsigned char row = row_ctrl+ctrl_nr*ROWS_PER_CTRL;
		
		unsigned char is_now, should_be;
		
		if (bufpos == dev->in_filled) { /* when the in buffer ended */
			
			/* bytes are placed at the beginning of in_buffer, so count from 0 */
			bufpos = 0;
		
			if ( !reads_awaited ) { /* if we readed all we wanted to */
				int j;
				
				/* set cursor position to the wanted position :D */
				for (j=0; j<dev->lcd_num; j++) {
					_cursor_ctrl_set(dev, j, row_ctrl, col);
				}
				
				/* add new reads requests
				 * queue so many that we stay below dev->in_size, so it can be transmitted to us
				 * also dont go above DISP_SIZE */
				for (j=0; j+dev->lcd_num <= dev->in_size && (i+j)/dev->lcd_num < DISP_SIZE;) {
					int k;
					
					j += dev->lcd_num;
					send_read_data_all(dev);
					
					/* we will read data from all controllers, so increment cursor posistion on all controllers */
					for (k=0; k<dev->lcd_num; k++) {
						cursor_ctrl_inc(dev, k);
					}
				}
				/* save the number bytes that we want to receive */
				reads_awaited = j;
			}
			
			/* receive what we need to receive */
			read_data(dev);
			
			if (dev->errors) 
				goto error;
			if (!dev->in_filled)
				goto error;
			
			/* substract number of bytes received */
			reads_awaited -= dev->in_filled;
			
			if (reads_awaited > dev->in_size || reads_awaited < 0) {
				/* there were some reads before us? */
				clear_read_data_buffer(dev);
			}
			
		}
		
		/* get the next char readed */
		is_now = dev->in_buffer[bufpos];
		bufpos++;
		
		/* what character should be there */
		should_be = dev->state[row][col];
		
		_check_and_fix_error(dev, ctrl_nr, row, col, is_now, should_be);
	}
	
	return;

error:
	PERROR(" %s %d %d %d \n", __func__, dev->errors, dev->in_filled, i);
}

static void _fixer_method_num_read(struct uhcmod_dev *dev)
{
	/* ************************************
	 * this can be buggy, not tested it much */
	
	int i, j;
	unsigned int pos;
	
	PDEBUG_CHECKER(" %s \n", __func__);
	
	/* pos is the start position of a read block
	 * end_pos - the end position of a read block 
	 * reads_awaited - for how many reads do we wait
	 * start_ctrl - the controller that we start reading from
	 * start_ctrl_len - how many bytes will we read from the first controller 
	 * end ctrl - the controller that we end reading from
	 * end_ctrl_num - how many bytes will we read from the end controller  
	 * */
	for (pos = 0; pos < DISP_SIZE;) {
		const unsigned int end_pos = min(pos + dev->in_size, (size_t)DISP_SIZE);
		const unsigned int reads_awaited = end_pos - pos;
		
		const unsigned char start_ctrl = pos / ONE_CTRL_DISP_SIZE;
		const unsigned char start_ctrl_len = min(reads_awaited, ONE_CTRL_DISP_SIZE - (pos%ONE_CTRL_DISP_SIZE) );
		const unsigned char end_ctrl = end_pos / ONE_CTRL_DISP_SIZE;
		const unsigned char end_ctrl_len = end_pos%ONE_CTRL_DISP_SIZE;
		
		
		/* set cursor position on start_ctrl to pos%ONE_CTRL_DISP_SIZE */
		i =  pos%ONE_CTRL_DISP_SIZE; /* cell number on start_ctrl */
		_cursor_ctrl_set(dev, start_ctrl,  i / DISP_COLS, i % DISP_COLS);
		
		/* send request for start_ctrl_len reads from controller number start_ctrl */
		send_num_read(dev, start_ctrl, start_ctrl_len);
		
		/* increment cursor start_ctrl_len times */
		for (i=0; i<start_ctrl_len; i++)
			cursor_ctrl_inc(dev, start_ctrl);
		
		/* if the end_ctrl differs from the start controller AND end_ctrl_len is not zero */
		if (  end_ctrl_len && start_ctrl != end_ctrl ) {
			
			/* set cursor position to (0,0) */
			_cursor_ctrl_set(dev, end_ctrl, 0, 0);
			
			/* send request for end_ctrl_len reads from controller number end_ctrl */
			send_num_read(dev, end_ctrl, end_ctrl_len);
			
			/* increment cursor end_ctrl_len times */
			for (i=0; i<end_ctrl_len; i++)
				cursor_ctrl_inc(dev, end_ctrl);
			
		}
		
		/* wait for receiving reads_awaited reads
		 * we should make only one read. after three times it displays an error */
		for (j=0; j < reads_awaited; j += dev->in_filled) {
			/* where the checking position is */
			int checkpos = pos+j;
			
			read_data(dev);
			
			if (dev->errors) 
				goto error;
			if (!dev->in_filled)
				goto error;
			
			for (i=0; i < dev->in_filled; i++, checkpos++) {
				const unsigned char ctrl_nr = checkpos / ONE_CTRL_DISP_SIZE;
				const unsigned char row = checkpos / DISP_COLS;
				const unsigned char col = checkpos % DISP_COLS;
				const unsigned char is_now = dev->in_buffer[i];
				const unsigned char should_be = dev->state[row][col];
				
				_check_and_fix_error(dev, ctrl_nr, row, col, is_now, should_be);
			}
			
		}
		
		/* the end becames a new beginning ; loop increment */
		pos = end_pos;
	}
	
	return; /* success */

error:
	PERROR(" %s %d %d %d %d %d \n", __func__, dev->errors, dev->in_filled, pos, i, j);
}

static void _fixer_CGRAM_errors(struct uhcmod_dev *dev)
{
	/* TODO: fix CGRAM errors in both styles: using num_read and/or using all_read */
	return;
}

static void check_and_fix_errors(struct uhcmod_dev *dev)
{
	if ( dev->lcd_num <= dev->in_size ) {
		_fixer_method_raw_all(dev);
	} else {
		_fixer_method_num_read(dev);
	}
	
	_fixer_CGRAM_errors(dev);
	
	/* this is needed, we want to restore cursor positions when we leave */
	uhcmod_usb_flush_send(dev);
}

/* ***************************  timer worker ***************************  */

static void timer_worker(struct work_struct *work)
{
	struct uhcmod_dev *dev;
	dev = container_of(work, struct uhcmod_dev, timer_work.work);
	
	if (dev == NULL) {
		dev->errors = -ENODEV;
		return;
	}
	
	PDEBUG_TIMER(" %s \n", __func__);
	
	mutex_lock(&dev->io_mutex);
	
	check_and_fix_errors(dev);
	
	get_pic_info(dev);
	
	mutex_unlock(&dev->io_mutex);
	
	if (checktime)
		schedule_delayed_work(&dev->timer_work, checktime*HZ );
	
	PDEBUG_TIMER("timer_worker end \n");
}

/* ****************************** proc functions ************************* */


static int proc_read_uhcmod(struct seq_file *s, void *what)
{
	struct uhcmod_dev *dev = (struct uhcmod_dev *)s->private;
	int i, j;
	
	mutex_lock(&dev->io_mutex);
	seq_printf(s,
		"Device minor       %10d\n"
		"USB Reads:         %10lu\n"
		"USB Readed bytes:  %10lu\n"
		"USB Writes:        %10lu\n"
		"USB Writed bytes:  %10lu\n"
		"Flags:             %#10lx\n"
		"Display rows:      %10d\n"
		"Display columns:   %10d\n"
		"Controlers number: %10d\n"
		"RowsPerControler:  %10d\n"
		"Virtual cursor row:%10d\n"
		"Virtual cursor column: %6d\n"
		"Timer seconds:     %10d\n"
		,
		dev->interface->minor,
		dev->usb_read_count,
		dev->usb_read_bytes_count,
		dev->usb_write_count,
		dev->usb_write_bytes_count,
		dev->flags,
		DISP_ROWS, 
		DISP_COLS,
		dev->lcd_num,
		ROWS_PER_CTRL,
		dev->row, 
		dev->col,
		checktime
		);
		
	for ( j = 0; j < dev->lcd_num; j++) {	
		seq_printf(s,
			"Controller number: %10d\n"
			" ^ Cursor row:     %10d\n"
			" ^ Cursor column:  %10d\n"
			" ^ Errors:         %10d\n"
			,
			j,
			dev->lcd[j].row,
			dev->lcd[j].col, 
			dev->lcd[j].errors_count
			);	
		
	}
	
	/* Print display state */
	seq_printf(s, "+" );
	for( i = 0; i < DISP_COLS; i++ )
		seq_printf(s, "-" );
	seq_printf(s, "+" );
	seq_printf(s, " ctrl_nr ");
	seq_printf(s, "\n");
	
	for( i = 0; i < DISP_ROWS ; i++ ) {
		seq_printf(s, "|" );
		for( j = 0; j < DISP_COLS ; j++ ) {
			if ( dev->state[i][j] < 10 ) /* character from CGRAM */
				seq_printf(s, "^");
			else
				seq_printf(s, "%c", dev->state[i][j]);
		}
		seq_printf(s, "| %d \n", (i / ROWS_PER_CTRL));
	}

	seq_printf(s, "+");
	for( i = 0; i < DISP_COLS; i++ )
		seq_printf(s, "-");
	seq_printf(s, "+\n");
	mutex_unlock(&dev->io_mutex);
	return 0;
}

static int proc_read_uhcmod_cgram(struct seq_file *s, void *what)
{
	struct uhcmod_dev *dev = (struct uhcmod_dev *)s->private;
	int j;
	
	mutex_lock(&dev->io_mutex);
	for ( j = 0; j < dev->lcd_num; j++) {
		int k, l;
		seq_printf(s, "Controler number %d\n", j);
		for (k = 0; k < 8; k++) {
			seq_printf(s, " ^ CGRAM[%1d]: ", k);
			for (l=0; l<8; l++) { 
				seq_printf(s, "%02x", dev->lcd[j].cgram[k][l]);
			}
			seq_printf(s, "\n");
		}
	}
	mutex_unlock(&dev->io_mutex);
	return 0;
}

static int proc_read_uhcmod_all(struct seq_file *s, void *what)
{
	struct uhcmod_dev *dev = (struct uhcmod_dev *)s->private;
	
	proc_read_uhcmod_cgram(s, what);
	proc_read_uhcmod(s, what);
	
	mutex_lock(&dev->io_mutex);
	seq_printf(s,
		"Ouput endpoint size: 	%10lu\n"
		"Input endpoint size: 	%10lu\n"
		"Usb errors: 		%10d\n"
		,
		dev->out_size,
		dev->in_size,
		dev->errors);
	mutex_unlock(&dev->io_mutex);
	return 0;
}
static int proc_read_config(struct seq_file *s, void *what)
{
	struct uhcmod_dev *dev = (struct uhcmod_dev *)s->private;
	int i, j;
	int reads_awaited;
	char msg[][30] = {
		"DISP_COLS = %d\n",
		"DISP_ROWS = %d\n",
		"NUM_CONTROLLERS = %d\n",
		"ROWS_PER_CTRL = %d\n",
		"sizeof(lcddev) = %d\n",
		"lcddev.flags = %d\n",
	};
	
	mutex_lock(&dev->io_mutex);
	
	uhcmod_usb_add_send(dev, CAKE_FILLING_GET_CONFIG);
	uhcmod_usb_add_send(dev, CAKE_FILLING_SET_READ);
	reads_awaited = 8;
	
	read_data(dev);
	
	if (dev->errors) 
		goto error;
	if (!dev->in_filled)
		goto error;
	
	for(i=0;i<dev->in_filled && i < sizeof(msg)/sizeof(*msg);i++)
		seq_printf(s, msg[i], dev->in_buffer[i]);
		
		
	uhcmod_usb_add_send(dev, CAKE_FILLING_GET_INFO);
	uhcmod_usb_add_send(dev, CAKE_FILLING_SET_READ);
	reads_awaited = dev->in_buffer[4];
	
	for (j=0; j < reads_awaited; j += dev->in_filled) {
		read_data(dev);
	
		if (dev->errors) 
			goto error;
		if (!dev->in_filled)
			goto error;
		
		for (i=0; i < dev->in_filled; i++) {
			seq_printf(s,"i %x \n", dev->in_buffer[i]);
		}
	}
	
error:
	mutex_unlock(&dev->io_mutex);
	
	return 0;
}

static int proc_read_uhcmod_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_read_uhcmod, PDE_DATA(inode));
}
static int proc_read_uhcmod_cgram_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_read_uhcmod_cgram, PDE_DATA(inode));
}
static int proc_read_uhcmod_all_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_read_uhcmod_all, PDE_DATA(inode));
}
static ssize_t proc_lcd_num_read(struct file *file, char *buffer, size_t length, loff_t * offset)
{
	struct uhcmod_dev *dev;
	char buf;
	
	dev = PDE_DATA(file_inode(file));
	buf = dev->lcd_num + '0'; /* convert to character */
	copy_to_user(buffer, &buf, sizeof(buf));
	return 1;
}
static ssize_t proc_lcd_num_write(struct file *file, const char *buffer, size_t len, loff_t * off)
{
	struct uhcmod_dev *dev;
	char buf;
	
	dev = PDE_DATA(file_inode(file));
	
	if ( copy_from_user(&buf, buffer, sizeof(buf)) )
		return -EFAULT;
	
	buf = buf - '0'; /* convert to int */
	
	if ( buf >= lcd_num || buf < 0 )
		return -EFAULT;
		
	dev->lcd_num = buf;
	
	return 1;
}
static int proc_read_config_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_read_config, PDE_DATA(inode));
}

static const struct file_operations proc_uhcmod_fops = {
	.owner		= THIS_MODULE,
	.open 		= proc_read_uhcmod_open,
	.read           = seq_read,
	.llseek         = seq_lseek,
	.release        = single_release,
};
static const struct file_operations proc_uhcmod_cgram_fops = {
	.owner		= THIS_MODULE,
	.open 		= proc_read_uhcmod_cgram_open,
	.read           = seq_read,
	.llseek         = seq_lseek,
	.release        = single_release,
};
static const struct file_operations proc_uhcmod_all_fops = {
	.owner		= THIS_MODULE,
	.open 		= proc_read_uhcmod_all_open,
	.read           = seq_read,
	.llseek         = seq_lseek,
	.release        = single_release,
};
static const struct file_operations proc_lcd_num_fops = {
	.owner		= THIS_MODULE,
	.read           = proc_lcd_num_read,
	.write 	        = proc_lcd_num_write,
	.llseek		= generic_file_llseek,
};
static const struct file_operations proc_config_fops = {
	.owner		= THIS_MODULE,
	.open 		= proc_read_config_open,
	.read           = seq_read,
	.llseek         = seq_lseek,
	.release        = single_release,
};

static int uhcmod_proc_init(struct uhcmod_dev *dev)
{
	char dirname[20];
	snprintf(dirname, sizeof(dirname), DEV_FILE_NAME"%d", dev->interface->minor);

	dev->procdir = proc_mkdir(dirname, NULL);
	if(!dev->procdir)
		goto fail_proc_mkdir;
		
	if (!proc_create_data("uhcmod", 0444, dev->procdir, &proc_uhcmod_fops, dev))
		goto fail_proc_uhcmod;
		
	if (!proc_create_data("uhcmod_cgram", 0444, dev->procdir, &proc_uhcmod_cgram_fops, dev))	
		goto fail_proc_uhcmod_cgram;
		
	if (!proc_create_data("uhcmod_all", 0444, dev->procdir, &proc_uhcmod_all_fops, dev))
		goto fail_proc_uhcmod_all;
		
	if (!proc_create_data("lcd_num", 0444, dev->procdir, &proc_lcd_num_fops, dev))
		goto fail_proc_lcd_num;

	if (!proc_create_data("config", 0444, dev->procdir, &proc_config_fops, dev))
		goto fail_proc_config;
	
	return 0; /* succes */


	remove_proc_entry("config", dev->procdir);
fail_proc_config:
	remove_proc_entry("lcd_num", dev->procdir);
fail_proc_lcd_num:
	remove_proc_entry("uhcmod_all", dev->procdir);
fail_proc_uhcmod_all:
	remove_proc_entry("uhcmod_cgram", dev->procdir);
fail_proc_uhcmod_cgram:
	remove_proc_entry("uhcmod",dev->procdir);
fail_proc_uhcmod:
	remove_proc_entry(dirname, NULL);
fail_proc_mkdir:
	return(-ENOMEM);
}

static void uhcmod_proc_exit(struct uhcmod_dev *dev)
{
	char dirname[20];
	snprintf(dirname, sizeof(dirname), DEV_FILE_NAME"%d", dev->interface->minor);
	remove_proc_subtree(dirname, NULL);
}


/* ************************** handle input ********************* */

static void global_write_DDRAM(struct uhcmod_dev *dev, unsigned char data)
{
	write_DDRAM(dev, dev->row, dev->col, data);
	cursor_virtual_inc(dev);
}

/* input_state states */
enum {
	NORMAL,
	ESC_,		 /* the [ in escape sequence */
	ESC,			// Escape sequence start
	DCA_Y,			// Direct cursor access, the next input will be the row
	DCA_X,			// Direct cursor access, the next input will be the column
	CGRAM_SELECT_ALL,	 // Selecting which slot to enter new character to all lcds
	CGRAM_GENERATE_ALL,	 // Waiting fot the 8 bytes which define a character for all lcds and flushing them
	CGRAM_SELECT_ONE,	// Selecting which slot to enter a new character and selecting lcd
	CGRAM_SELECT_LCD_ONE, /* selectging which lcd to flash new cgram, input is in unsigned int!!! */
	CGRAM_GENERATE_ONE, /* waiting for the 8 bytes which define a character and flushing them */
	CHAR_BYPAS,	/* write character directly to the LCD without remaping or interpretation */
	INST_BYPAS	/* write instruction directly to the LCD without remaping or interpretation */
};

/* Handle write to device file */
void input_escape_sequence(struct uhcmod_dev *dev,  unsigned char input )
{
	static unsigned int cgram_index = 0;
	static unsigned int cgram_row_count = 0;
	static unsigned int cgram_lcd = 0;
	static unsigned char cgram_pixels[ 8 ] = {[0 ... 7] = 0};
	static int input_state = NORMAL;	// the current state of the input handler
	
	int i, j;
	
	switch ( input_state ) {
	case NORMAL:
		switch ( input ) {
		case 0x08:	// Backspace
			if ( dev->col ) {
				dev->col--;
			}
			write_DDRAM(dev, dev->row, dev->col, ' ' );
			break;
		case 0x09:	// Tabstop
			dev->col = ( ( ( dev->col + 1 ) / TABSTOP ) * TABSTOP ) + TABSTOP - 1;
			break;
		case '\n': /* new line, we have still free lines */
			if (dev->row < DISP_ROWS - 1) {
				++dev->row;
			} else { /* no moere free lines, scroll up */
				for ( i = 0; i < dev->row; i++ ) {
					for( j = 0; j < DISP_COLS; j++ ) {
						write_DDRAM(dev, i, j, dev->state[i + 1][j] );
					}
				}
				for( i = 0; i < DISP_COLS; i++ ){
					write_DDRAM(dev, dev->row, i, charmap[' ']);
				}
			}
			/*break; Since many have trouble grasping the \r\n concept :) */
		case 0x0d:  // Carrage return
			dev->col = 0;
			break;
		case 0x1b:  // esc ie. start of escape sequence
			input_state = ESC_;
			break;
		default:  // The character is looked up in the charmap[]
			global_write_DDRAM(dev, charmap[ input ] );
		} /* switch (input) */
		break;
	case ESC_:
		input_state = ESC;
		break;
	case ESC:
		switch ( input ){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':   // Chararacter from CGRAM
			global_write_DDRAM(dev, input - '0' );
			input_state = NORMAL;
			break;
		case 'A':     // Cursor up
			if ( dev->row )
				dev->row--;
			input_state = NORMAL;
			break;
		case 'B':     // Cursor down
			if ( dev->row < DISP_ROWS - 1 )
				dev->row++;
			input_state = NORMAL;
			break;
		case 'C':     // Cursor Right
			if ( dev->col < DISP_COLS - 1 )
			    dev->col++;
			input_state = NORMAL;
			break;
		case 'D':     // Cursor Left
			if ( dev->col )
				dev->col--;
			input_state = NORMAL;
			break;
		case 'H':     // Cursor home
			dev->row = 0;
			dev->col = 0;
			input_state = NORMAL;
			break;
		case 'J':   // Clear screen, cursor doesn't move
			for (i=0; i<DISP_ROWS;i++)
				memset(dev->state[i], ' ', DISP_COLS);
			write_inst_all(dev, HD44780_CLRDISP);
			input_state = NORMAL;
			break;
		case 'K':     // Erase to end of line, cursor doesn't move
			for (i = dev->col; i < DISP_COLS; ++i)
				write_DDRAM(dev, dev->row, i, charmap[' ']);
			input_state = NORMAL;
			break;
		case 'Y':     // Direct cursor access
			input_state = DCA_Y;
			break;
		case 'R':   // CGRAM select for all lcds
			input_state = CGRAM_SELECT_ALL;
			break;
		case 'r':   // CGRAM select for one lcd
			input_state = CGRAM_SELECT_ONE;
			break;
		case 'V':   // Linewrap on
			clear_bit(FLAG_WRAP_OFF, &(dev->flags));
			input_state = NORMAL;
			break;
		case 'W':   // Linewrap off
			set_bit(FLAG_WRAP_OFF, &(dev->flags));
			input_state = NORMAL;
			break;
		case 'X':   // character bypassing
			input_state = CHAR_BYPAS;
			break;
		default:
			PINFO( "unrecognized escape sequence: %#x ('%c')\n", input, input );
			input_state = NORMAL;
			break;
		} /* case ESC switch(input) */
		break;
	case DCA_Y :
		if ( input < DISP_ROWS ) {
			dev->row = input;
		} else {
			PINFO( "tried to set cursor to off screen location\n" );
			dev->row = DISP_ROWS - 1;
		}
		input_state = DCA_X;
		break;
	case DCA_X :
		if ( input < DISP_COLS ) {
			dev->col = input;
		}  else {
			PINFO( "tried to set cursor to off screen location\n" );
			dev->col = DISP_COLS - 1;
		}
		input_state = NORMAL;
		break;
	case CGRAM_SELECT_ALL :
		if( input > '7' || input < '0' ) {
			PINFO( "Bad CGRAM index %d\n", (int)(input-'0') );
			input_state = NORMAL;
		} else {
			cgram_index = input - '0';
			cgram_row_count = 0;
			input_state = CGRAM_GENERATE_ALL;
		}
		break;
	case CGRAM_GENERATE_ALL :
		cgram_pixels[cgram_row_count] = input;
		++cgram_row_count;
		if( cgram_row_count != 8 ) 
			break; /* wait for 8 characters */
		write_CGRAM_all(dev, cgram_index, cgram_pixels);
		input_state = NORMAL;
		break;
	case CGRAM_SELECT_ONE :
		if( input > '7' || input < '0' ) {
			PINFO( "LCD: Bad CGRAM index %d\n", (int)(input-'0') );
			input_state = NORMAL;
		} else {
			cgram_index = input - '0';
			input_state = CGRAM_SELECT_LCD_ONE;
		}
		break;
	case CGRAM_SELECT_LCD_ONE : /* input is in unsigned int!!! */
		if( (unsigned int)input >= dev->lcd_num) {
			PINFO( "LCD: CGRAM lcd selected out of range: %c\n", input );
			input_state = NORMAL;
		} else {
			cgram_lcd = input;
			cgram_row_count = 0;
			input_state = CGRAM_GENERATE_ONE;
		}
		break;
	case CGRAM_GENERATE_ONE :
		cgram_pixels[cgram_row_count] = input;
		++cgram_row_count;
		if( cgram_row_count != 8 ) break; /* wait for 8 characters */
		write_CGRAM(dev, cgram_lcd, cgram_index, cgram_pixels );
		input_state = NORMAL;
		break;
	case CHAR_BYPAS :
		global_write_DDRAM(dev, input);
		input_state = NORMAL;
		break;
	default:
		PINFO("Unknown signal received\n");
		input_state = NORMAL;
	} /* siwtch(input_state) */
}

/* ***************************  usb class character device functions ***************************  */

static int uhcmod_open(struct inode *inode, struct file *file)
{
	struct uhcmod_dev *dev;
	struct usb_interface *interface;
	int subminor;
	int retval = 0;

	PDEBUG_OPERATION(" %s \n",  __func__);

	subminor = iminor(inode);

	interface = usb_find_interface(&uhcmod_driver, subminor);
	if (!interface) {
		PERROR("%s - error, can't find device for minor %d\n",
			__func__, subminor);
		retval = -ENODEV;
		goto exit;
	}

	dev = usb_get_intfdata(interface);
	if (!dev) {
		retval = -ENODEV;
		goto exit;
	}

	/* increment our usage count for the device */
	kref_get(&dev->kref);

	/* lock the device to allow correctly handling errors
	 * in resumption */
	mutex_lock(&dev->io_mutex);

	retval = usb_autopm_get_interface(interface);
	if (retval)
		goto exit;

	/* save our object in the file's private structure */
	file->private_data = dev;
	
	clear_read_data_buffer(dev);
	mutex_unlock(&dev->io_mutex);

exit:
	return retval;
}

static int uhcmod_release(struct inode *inode, struct file *file)
{
	struct uhcmod_dev *dev;

	dev = file->private_data;
	if (dev == NULL)
		return -ENODEV;

	PDEBUG_OPERATION(" %s \n",  __func__);

	/* allow the device to be autosuspended */
	mutex_lock(&dev->io_mutex);
	if (dev->interface)
		usb_autopm_put_interface(dev->interface);
	mutex_unlock(&dev->io_mutex);

	/* decrement the count on our device */
	kref_put(&dev->kref, uhcmod_delete);
	return 0;
}

static int uhcmod_writeback(struct file *file)
{
	struct uhcmod_dev *dev;
	int res;
	
	dev = file->private_data;
	if (dev == NULL)
		return -ENODEV;

	mutex_lock(&dev->io_mutex);
	if (!dev->interface) { /* disconnect() was called */
		mutex_unlock(&dev->io_mutex);
		return -ENODEV;
	}
	
	res = dev->errors ? (dev->errors == -EPIPE ? -EPIPE : -EIO) : 0;
	dev->errors = 0;
	
	if ( file->f_flags&O_NONBLOCK ) {
		uhcmod_usb_flush_send(dev);
	} else {
		uhcmod_usb_flush_send_block(dev);
	}
		
	mutex_unlock(&dev->io_mutex);
	
	return res;
}

static int uhcmod_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
	return uhcmod_writeback(file);
}

static int uhcmod_flush(struct file *file, fl_owner_t id)
{
	return uhcmod_writeback(file);
}

static ssize_t uhcmod_read(struct file *file, char __user *buffer, size_t count, loff_t *ppos)
{
	struct uhcmod_dev *dev;
	int retval = 0;
	unsigned char i;
	size_t j;
	
	PDEBUG_OPERATION(" %s \n",  __func__);
	
	dev = file->private_data;
	
	/* report and clear errors if any */
	if (dev->errors) {
		int res;
		res = dev->errors == -EPIPE ? -EPIPE : -EIO;
		dev->errors = 0;
		return res;
	}
	
	mutex_lock(&dev->io_mutex);
	if (!dev->interface) { /* disconnect() was called */
		mutex_unlock(&dev->io_mutex);
		return -ENODEV;
	}
	
	/* reading char from state variable */
	j = min((size_t)DISP_SIZE, count);
	for (i=0; i < DISP_ROWS; i++) {
		if ( j < DISP_COLS ) {
			retval = copy_to_user(buffer, dev->state[i], j);
			buffer += j;
		} else {
			retval = copy_to_user(buffer, dev->state[i], DISP_COLS);
			j -= DISP_COLS;
			buffer += DISP_COLS;
		}
		if (retval < 0)
			break;
	}
	
	mutex_unlock(&dev->io_mutex);
	
	return retval < 0 ? retval : min((size_t)DISP_COLS*DISP_ROWS, count) ;
}

static ssize_t uhcmod_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
{
	struct uhcmod_dev *dev;
	unsigned char i;
	
	PDEBUG_OPERATION(" %s \n",  __func__);
	
	if (!buffer)
		return -EINVAL;
	
	dev = file->private_data;
	
	/* report and clear errors if any */
	if (dev->errors) {
		int res;
		res = dev->errors == -EPIPE ? -EPIPE : -EIO;
		dev->errors = 0;
		return res;
	}
	
	
	/* this will never take long */
	mutex_lock(&dev->io_mutex);
	if (!dev->interface) { /* disconnect() was called */
		mutex_unlock(&dev->io_mutex);
		return -ENODEV;
	}
	
	for(i = 0; i < count; i++ ) {
		PDEBUG_OPERATION(" cdev write: %c \n", buffer[i]);
		input_escape_sequence(dev, buffer[ i ] );
	}
	
	if ( !(file->f_flags&O_NONBLOCK) ) {
		uhcmod_usb_flush_send(dev);
	}
	
	mutex_unlock(&dev->io_mutex);
	
	return count;
}

static const struct file_operations uhcmod_fops = {
	.owner =	THIS_MODULE,
	.read =		uhcmod_read,
	.write =	uhcmod_write,
	.fsync = 	uhcmod_fsync,
	.flush = 	uhcmod_flush,
	.open =		uhcmod_open,
	.release =	uhcmod_release,
};

/* *************************** usb usb_driver functions *********************** */

static char *uhcmod_devnode(struct device *dev, umode_t *mode)
{
        return kasprintf(GFP_KERNEL, DEV_FILE_NAME "%d", uhcmod_number-1);
}

static struct usb_class_driver uhcmod_class = {
	.name =		"uhcmod%d",
	.devnode =	uhcmod_devnode,
	.fops =		&uhcmod_fops,
	.minor_base =	USB_UHCMOD_MINOR_BASE,
};

static int uhcmod_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	struct uhcmod_dev *dev;
	struct usb_endpoint_descriptor *endpoint;
	int retval = -ENOMEM;

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		dev_err(&interface->dev, "Out of memory\n");
		goto error;
	}
	
	kref_init(&dev->kref);
	sema_init(&dev->limit_sem, WRITES_IN_FLIGHT);
	mutex_init(&dev->io_mutex);
	init_usb_anchor(&dev->submitted);
	INIT_DELAYED_WORK(&dev->timer_work, timer_worker);
	uhcmod_number++;
	
	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = interface;
	
	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);
	
	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	
	/* check endpoints number = 2*/
	if ( interface->cur_altsetting->desc.bNumEndpoints != 2 ) {
		dev_err(&interface->dev, "Wring number of endpoints\n");
		goto error;
	}
	
	/* out endpoint */
	endpoint = &interface->cur_altsetting->endpoint[0].desc;
	dev->out_size = endpoint->wMaxPacketSize;
	dev->out_endpointAddr = endpoint->bEndpointAddress;
	dev->out_buffer = kmalloc(dev->out_size, GFP_KERNEL);
	if (!dev->out_buffer) {
		PERROR("Could not allocate out_buffer \n");
		goto error;
	}
	
	endpoint = &interface->cur_altsetting->endpoint[1].desc;
	dev->in_size = endpoint->wMaxPacketSize;
	dev->in_endpointAddr = endpoint->bEndpointAddress;
	dev->in_buffer = kmalloc(dev->in_size, GFP_KERNEL);
	if (!dev->in_buffer) {
		PERROR("Could not allocate bulk_in_buffer \n");
		goto error;
	}
	
	/* get config of our new device */
	get_pic_config(dev);
	
	/* allocate memory for lcds */
	dev->lcd = kcalloc(dev->lcd_num, sizeof(*dev->lcd), GFP_KERNEL);
	if (!dev->lcd) {
		PERROR("Could not allocate memory for dev->lcd \n");
		goto error;
	}
	dev->state = kcalloc(dev->lcd_num*ROWS_PER_CTRL, DISP_COLS, GFP_KERNEL);
	if (!dev->state) {
		PERROR("Could not allocate memory for dev->lcd \n");
		goto error;
	}
	
	/* initialize displays */
	retval = init_displays(dev);
	if (retval) {
		dev_err(&interface->dev, "error init_displays %d \n", retval);
		goto error;
	}
	
	/* we can register the device now, as it is ready */
	retval = usb_register_dev(interface, &uhcmod_class);
	if (retval) {
		/* something prevented us from registering this driver */
		dev_err(&interface->dev,
			"Not able to get a minor for this device.\n");
		usb_set_intfdata(interface, NULL);
		goto error;
	}
	
	retval = uhcmod_proc_init(dev);
	if ( retval ) {
		dev_err(&interface->dev,
			"error creating proc entries.\n");
		PERROR("error creating proc entries ret=%d.", retval);
		/* this error is not fatal */
	}
	
	/* initalize our timer worker */
	if (checktime) {
		schedule_delayed_work(&dev->timer_work, HZ*checktime);
	}
	
	/* let the user know what node this device is now attached to */
	dev_info(&interface->dev,
		"uhcmod version %s - uhc device with %d lcds %dx%d now attached to "DEV_FILE_NAME"%d with minor %d",
		UHCMOD_VERSION, dev->lcd_num, ROWS_PER_CTRL, DISP_COLS,  uhcmod_number-1, interface->minor);
		
	return 0; /* success */

error:
	if (dev) {
		/* this frees allocated memory */
		kref_put(&dev->kref, uhcmod_delete);
	}
	return retval;
}

static void uhcmod_disconnect(struct usb_interface *interface)
{
	struct uhcmod_dev *dev;
	int minor = interface->minor;

	dev = usb_get_intfdata(interface);
	
	uhcmod_proc_exit(dev);
	
	usb_set_intfdata(interface, NULL);
	
	/* give back our minor */
	usb_deregister_dev(interface, &uhcmod_class);
		
	cancel_delayed_work_sync(&dev->timer_work);

	/* prevent more I/O from starting */
	mutex_lock(&dev->io_mutex);
	
	dev->interface = NULL;
	
	mutex_unlock(&dev->io_mutex);

	usb_kill_anchored_urbs(&dev->submitted);

	/* decrement our usage count */
	kref_put(&dev->kref, uhcmod_delete);

	dev_info(&interface->dev, "uhc device with minor %d now disconnected", minor);
}

static void uhcmod_draw_down(struct uhcmod_dev *dev)
{
	int time;
	
	uhcmod_usb_flush_send(dev);
	
	time = usb_wait_anchor_empty_timeout(&dev->submitted, 1000);
	if (!time)
		usb_kill_anchored_urbs(&dev->submitted);
}

static int uhcmod_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct uhcmod_dev *dev;
	
	PDEBUG(" %s \n ", __func__);
	
	dev = usb_get_intfdata(intf);
	if (!dev)
		return 0;
	
	cancel_delayed_work_sync(&dev->timer_work);
	
	uhcmod_draw_down(dev);
	
	return (dev->errors);
}

static int uhcmod_resume(struct usb_interface *intf)
{
	struct uhcmod_dev *dev;
	
	PDEBUG(" %s \n ", __func__);

	dev = usb_get_intfdata(intf);
	if (!dev)
		return 0;
	
	if (checktime)
		schedule_delayed_work(&dev->timer_work, checktime*HZ );
	
	return (dev->errors);
}

static int uhcmod_reset_resume(struct usb_interface *intf)
{
	struct uhcmod_dev *dev;
	
	PDEBUG(" %s \n", __func__);
	
	dev = usb_get_intfdata(intf);
	if (!dev)
		return 0;
	
	schedule_delayed_work(&dev->timer_work, HZ*checktime);
	
	return (dev->errors);
}

static int uhcmod_pre_reset(struct usb_interface *intf)
{
	struct uhcmod_dev *dev;
	
	PDEBUG(" %s \n", __func__);
	
	dev = usb_get_intfdata(intf);
	if (!dev)
		return 0;

	mutex_lock(&dev->io_mutex);
	uhcmod_draw_down(dev);

	return 0;
}

static int uhcmod_post_reset(struct usb_interface *intf)
{
	struct uhcmod_dev *dev;
	
	PDEBUG(" %s \n", __func__);
	
	dev = usb_get_intfdata(intf);
	if (!dev)
		return 0;
	
	init_displays(dev);
	
	mutex_unlock(&dev->io_mutex);

	return 0;
}

static struct usb_driver uhcmod_driver = {
	.name =		"uhcmod",
	.probe =	uhcmod_probe,
	.disconnect =	uhcmod_disconnect,
	.suspend =	uhcmod_suspend,
	.resume =	uhcmod_resume,
	.reset_resume = uhcmod_reset_resume,
	.pre_reset =	uhcmod_pre_reset,
	.post_reset = 	uhcmod_post_reset,
	.id_table =	uhcmod_table,
	.supports_autosuspend = 1,
};

module_usb_driver(uhcmod_driver);

MODULE_AUTHOR("Kamil Cukrowski");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION( "USB driver for programmed pic controlling HD44780 compatible controllers" );
MODULE_VERSION(UHCMOD_VERSION);
