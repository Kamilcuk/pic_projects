#ifndef _UHCLIB_H_
#define _UHCLIB_H_

#include <linux/usb.h>
#include <linux/kref.h>
#include "config.h"

/* lcdmod_dev->flags */
#define FLAG_WRAP_OFF		1
/* more to come */

#ifdef HD44780_COUNTERS
struct lcd_device {
	unsigned long int write_count;
	unsigned long int read_count;
	unsigned long int bfchecks_count;
};
#endif

/* our big struct */
struct pic_device {
#ifdef HD44780_COUNTERS
	struct lcd_device lcd[NUM_CONTROLLERS];
#endif
	
	unsigned char flags;
};

struct uhcmod_lcd {
	unsigned char 		row : 2; 		/* cursor row - max 4 rows for hd44780 */
	unsigned char 		col : 6; 		/* cursor column - max 40 for hd44780 */
	
	unsigned char 		cgram[8][8];		/* cgram writen on this lcd  */
	
	unsigned int 		errors_count;		/* times error found on this lcd */
};

struct uhcmod_dev {
	struct pic_device 	pic;
	
	unsigned char		lcd_num;		/* number of lcds */
	struct uhcmod_lcd 	*lcd;			/* info about every single lcd */
	unsigned char 		row;			/* cursor position */
	unsigned char 		col;
	unsigned char		(*state)[DISP_COLS];	/* current display state */
	
	struct usb_device 	*udev;			/* the usb device for this device */
	struct usb_interface	*interface;		/* the interface for this device */
	
	struct mutex		io_mutex;		/* synchronize all entries to device */
	struct kref		kref;			/* reference counter */
	struct semaphore	limit_sem;		/* limiting the number of writes in progress */
	struct usb_anchor	submitted;		/* in case we need to retract our submissions */
	
	unsigned char 		*out_buffer;		/* the buffer for send data */
	size_t			out_filled;		/* number of bytes in the buffer */
	size_t			out_size;		/* the size of the send buffer */
	__u8			out_endpointAddr;	/* the address of the bulk out endpoint */
	
	unsigned char 		*in_buffer;		/* the buffer to receive data */
	int			in_filled;		/* number of bytes in the buffer */
	size_t			in_size;		/* the size of the receive buffer */
	__u8			in_endpointAddr;	/* the address of the bulk in endpoint */
	
	int 			errors;			/* errrors */
	
	unsigned long 		flags; 			/* flags */
	
	struct delayed_work	timer_work; 		/* our timed work */
	
	/* counters */
	unsigned long int	write_count;		/* writted to hd44780 */
	unsigned long int 	read_count;		/* readed from hd44780 */
	unsigned long int 	bfchecks_count;		/* times checked busyflag on hd44780 */
	
	unsigned long int 	usb_write_count; 	/* times written to device */
	unsigned long int 	usb_write_bytes_count; 	/* bytes written to device */
	unsigned long int 	usb_read_count; 	/* times readed from device */
	unsigned long int 	usb_read_bytes_count;	/* bytes readed from device */
	
	/* proc entries */
	struct proc_dir_entry 	*procdir, *procfile, *cgram_procfile, *all_procfile, *tryproc;

};

#endif /*  _UHCLIB_H_ */
