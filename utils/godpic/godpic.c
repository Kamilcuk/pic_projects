
/*
 * godpic module - ver 0.1
 * 
 * godpic.c
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
 */
/* 
 * godpic driver
 * handle godpic compatible programmed pic device usb driver module
 * copyright by (C) Kamil Cukrowski <kamil@dyzio.pl>
 *
 * This driver is based on USB Skeleton driver - 2.0
 *    that is copyrighted 2001-2004 Greg Kroah-Hartman (greg@kroah.com)
 *    and licensed under GPL version 2.
 * This driver is based on LEGO USB Tower driver
 * which is copyrighted by <davidgsf@sourceforge.net>
 * and by Juergen Stuber <starblue@users.sourceforge.net>
 *
 * 
 */
 
#define VERSION "0.0.5a"

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
#include <linux/usb.h>
#include <linux/mutex.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/completion.h>
#include <linux/mutex.h>
#include <asm/uaccess.h>
#include <linux/usb.h>
#include <linux/poll.h>

#define PDEBUG_HD44780(arg, ...) //printk(arg,  ## __VA_ARGS__ );
#define PERROR(arg, ...) //printk(arg,  ## __VA_ARGS__ );
#define PDEBUG_OPERATION(arg, ...) //printk(arg,  ## __VA_ARGS__ );



/* how many urbs can be submitted at one time 
 * does not allows user to alloc all memory */
#define WRITES_IN_FLIGHT 6

/* Define these values to match your devices */
#define USB_PIC_VENDOR_ID	0xffff
#define USB_PIC_PRODUCT_ID	0x0010

#define DEV_FILE_NAME "pic"
#define USB_PIC_MINOR_BASE	241

static int read_timeout = 1000;
static int read_buffer_size = 480;

/* table of devices that work with this driver */
static const struct usb_device_id pic_table[] = {
	{ USB_DEVICE(USB_PIC_VENDOR_ID, USB_PIC_PRODUCT_ID) },
	{ }					/* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, pic_table);


/* Structure to hold all of our device specific stuff */
struct usb_pic {
	struct usb_device	*udev;			/* the usb device for this device */
	struct usb_interface 	*interface;		/* the interface for this device */
	
	struct mutex		io_mutex;		/* synchronize all entries to device */
	struct kref		kref;			/* reference counter */
	struct semaphore	limit_sem;		/* limiting the number of writes in progress */
	struct usb_anchor	submitted;		/* in case we need to retract our submissions */
	
	char*			read_buffer;
	size_t			read_buffer_length; /* this much came in */
	size_t			read_packet_length; /* this much will be returned on read */
	spinlock_t		read_buffer_lock;
	
	char*			interrupt_in_buffer;
	struct usb_endpoint_descriptor* interrupt_in_endpoint;
	struct urb*		interrupt_in_urb;
	int			interrupt_in_interval;
	int			interrupt_in_running;
	int			interrupt_in_done;
	
	unsigned char 		*out_buffer;		/* the buffer for send data */
	size_t			out_filled;		/* number of bytes in the buffer */
	size_t			out_size;		/* the size of the send buffer */
	__u8			out_endpointAddr;	/* the address of the bulk out endpoint */
	
	
	
	int 			errors;			/* errrors */
	
	wait_queue_head_t	read_wait;
};
#define to_pic_dev(d) container_of(d, struct usb_pic, kref)

static struct usb_driver pic_driver;

static unsigned char pic_number = 0; /* number of godpics connected */


/* ------------------------------------------------------------------------ */

static void pic_delete_transfers(struct usb_pic *dev)
{	
	/* shutdown transfer */
	if (dev->interrupt_in_running) {
		dev->interrupt_in_running = 0;
		mb();
		if (dev->udev)
			usb_kill_urb (dev->interrupt_in_urb);
	}
}

static void pic_delete(struct kref *kref)
{
	struct usb_pic *dev = to_pic_dev(kref);
	
	pic_delete_transfers(dev);
	
	pic_number--;
	
	usb_free_urb(dev->interrupt_in_urb);
	kfree (dev->read_buffer);
	kfree (dev->interrupt_in_buffer);
	kfree(dev->out_buffer);
	kfree (dev);
}

/* ----------------------------------------------------------------------- */
/* ********************** usb send and recv and add to buffer functions *********************  */

static void uhcmod_usb_flush_send_callback(struct urb *urb)
{
	struct usb_pic *dev;
	
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
	}
	
	/* free up our allocated buffer */
	usb_free_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
	up(&dev->limit_sem);
}

static void _uhcmod_usb_do_send(struct usb_pic *dev, char *what, size_t writesize)
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

static void uhcmod_usb_flush_send(struct usb_pic *dev)
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

static void uhcmod_usb_flush_send_block(struct usb_pic *dev)
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

static void uhcmod_usb_add_send(struct usb_pic *dev, u8 data) 
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

/* ------------------------------------------------------------------------- */

static void pic_interrupt_in_callback (struct urb *urb)
{
	struct usb_pic *dev = urb->context;
	int status = urb->status;
	int retval;

	if (status) {
		if (status == -ENOENT ||
		    status == -ECONNRESET ||
		    status == -ESHUTDOWN) {
			goto exit;
		} else {
			dev_dbg(&dev->udev->dev,
				"%s: nonzero status received: %d\n", __func__,
				status);
			goto resubmit; /* maybe we can recover */
		}
	}

	if (urb->actual_length > 0) {
		spin_lock (&dev->read_buffer_lock);
		if (dev->read_buffer_length + urb->actual_length < read_buffer_size) {
			memcpy (dev->read_buffer + dev->read_buffer_length,
				dev->interrupt_in_buffer,
				urb->actual_length);
			dev->read_buffer_length += urb->actual_length;
		} else {
			pr_warn("read_buffer overflow, %d bytes dropped\n",
				urb->actual_length);
		}
		spin_unlock (&dev->read_buffer_lock);
	}

resubmit:
	/* resubmit if we're still running */
	if (dev->interrupt_in_running && dev->udev) {
		retval = usb_submit_urb (dev->interrupt_in_urb, GFP_ATOMIC);
		if (retval)
			dev_err(&dev->udev->dev,
				"%s: usb_submit_urb failed (%d)\n",
				__func__, retval);
	}

exit:
	dev->interrupt_in_done = 1;
	wake_up_interruptible (&dev->read_wait);
}

/* ------------------------------------------------------------------------ */

static int pic_writeback(struct file *file)
{
	struct usb_pic *dev;
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

static int pic_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
	return pic_writeback(file);
}

static int pic_flush(struct file *file, fl_owner_t id)
{
	return pic_writeback(file);
}

static int pic_open(struct inode *inode, struct file *file)
{
	struct usb_pic *dev;
	struct usb_interface *interface;
	int subminor;
	int retval = 0;
	
	subminor = iminor(inode);

	interface = usb_find_interface(&pic_driver, subminor);
	if (!interface) {
		pr_err("%s - error, can't find device for minor %d\n",
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
	
	/* initialize in direction */
	dev->read_buffer_length = 0;
	dev->read_packet_length = 0;
	usb_fill_int_urb (dev->interrupt_in_urb,
			  dev->udev,
			  usb_rcvintpipe(dev->udev, dev->interrupt_in_endpoint->bEndpointAddress),
			  dev->interrupt_in_buffer,
			  usb_endpoint_maxp(dev->interrupt_in_endpoint),
			  pic_interrupt_in_callback,
			  dev,
			  dev->interrupt_in_interval);

	dev->interrupt_in_running = 1;
	dev->interrupt_in_done = 0;
	mb();

	retval = usb_submit_urb (dev->interrupt_in_urb, GFP_KERNEL);
	if (retval) {
		dev_err(&dev->udev->dev,
			"Couldn't submit interrupt_in_urb %d\n", retval);
		dev->interrupt_in_running = 0;
		goto unlock_exit;
	}


	retval = usb_autopm_get_interface(interface);
	if (retval)
		goto exit;

	/* save our object in the file's private structure */
	file->private_data = dev;
unlock_exit:
	mutex_unlock(&dev->io_mutex);
exit:
	return retval;
}

static int pic_release(struct inode *inode, struct file *file)
{
	struct usb_pic *dev;

	dev = file->private_data;
	if (dev == NULL)
		return -ENODEV;
	
	if (!dev->interface) {		/* disconnect() was called */
		return -ENODEV;
	}

	/* allow the device to be autosuspended */
	mutex_lock(&dev->io_mutex);
	if (dev->interface)
		usb_autopm_put_interface(dev->interface);

	pic_delete_transfers(dev);
	
	mutex_unlock(&dev->io_mutex);
	
	/* decrement the count on our device */
	kref_put(&dev->kref, pic_delete);
	return 0;
}

static void pic_check_for_read_packet (struct usb_pic *dev)
{
	spin_lock_irq (&dev->read_buffer_lock);
	dev->read_packet_length = dev->read_buffer_length;
	dev->interrupt_in_done = 0;
	spin_unlock_irq (&dev->read_buffer_lock);
}

static unsigned int pic_poll (struct file *file, poll_table *wait)
{
	struct usb_pic *dev;
	unsigned int mask = 0;

	dev = file->private_data;

	if (!dev->udev)
		return POLLERR | POLLHUP;

	poll_wait(file, &dev->read_wait, wait);

	pic_check_for_read_packet(dev);
	if (dev->read_packet_length > 0) {
		mask |= POLLIN | POLLRDNORM;
	}

	return mask;
}

static loff_t pic_llseek (struct file *file, loff_t off, int whence)
{
	return -ESPIPE;		/* unseekable */
}

static ssize_t pic_read(struct file *file, char __user *buffer, size_t count, loff_t *ppos)
{
	struct usb_pic *dev;
	size_t bytes_to_read;
	int i;
	int rv;
	
	dev = file->private_data;
	
	/* if we cannot read at all, return EOF */
	if (!count)
		return 0;
		
	if (!dev->interface) {		/* disconnect() was called */
		rv = -ENODEV;
		goto exit;
	}
	
	/* no concurrent readers */
	rv = mutex_lock_interruptible(&dev->io_mutex);
	if (rv < 0)
		goto nounlock_exit;
	
	if (!dev->interface) {		/* disconnect() was called */
		rv = -ENODEV;
		goto exit;
	}
	if ( count == 0 )
		goto exit;
	
	/* wait for data */
	pic_check_for_read_packet (dev);
	if (dev->read_packet_length == 0) {
		if (file->f_flags & O_NONBLOCK) {
			rv = -EAGAIN;
			goto unlock_exit;
		}
		
		rv = wait_event_interruptible_timeout(dev->read_wait, dev->interrupt_in_done, read_timeout);
		if (rv < 0) {
			goto unlock_exit;
		}
		
		pic_check_for_read_packet (dev);
		if (dev->read_packet_length == 0)
			goto unlock_exit;
	}
	
	/* copy the data from read_buffer into userspace */
	bytes_to_read = min(count, dev->read_packet_length);
	if (copy_to_user (buffer, dev->read_buffer, bytes_to_read)) {
		rv = -EFAULT;
		goto exit;
	}
	
	spin_lock_irq (&dev->read_buffer_lock);
	dev->read_buffer_length -= bytes_to_read;
	dev->read_packet_length -= bytes_to_read;
	for (i=0; i<dev->read_buffer_length; i++) {
		dev->read_buffer[i] = dev->read_buffer[i+bytes_to_read];
	}
	spin_unlock_irq (&dev->read_buffer_lock);

	rv = bytes_to_read;
	
unlock_exit:
exit:
	mutex_unlock(&dev->io_mutex);
nounlock_exit:
	return rv;
}

static ssize_t pic_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
{
	struct usb_pic *dev;
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
		uhcmod_usb_add_send(dev, buffer[i]);
	}
	
	if ( !(file->f_flags&O_NONBLOCK) ) {
		uhcmod_usb_flush_send(dev);
	}
	
	mutex_unlock(&dev->io_mutex);
	
	return count;
}

static struct file_operations pic_fops = {
	.owner =	THIS_MODULE,
	.read =		pic_read,
	.write = 	pic_write,
	.open =		pic_open,
	.release =	pic_release,
	.poll =		pic_poll,
	.llseek =	pic_llseek,
	.fsync = 	pic_fsync,
	.flush = 	pic_flush,
};

/* ---------------------------------------------------------------------------------- */

static char *pic_devnode(struct device *dev, umode_t *mode)
{
        return kasprintf(GFP_KERNEL, DEV_FILE_NAME"%d", pic_number-1);
}

/* 
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device registered with devfs and the driver core
 */
static struct usb_class_driver pic_class = {
	.name = "godpic%d",
	.devnode = pic_devnode,
	.fops = &pic_fops,
	.minor_base = USB_PIC_MINOR_BASE,
};

static int pic_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	struct usb_pic *dev = NULL;
	struct device *idev = &interface->dev;
	struct usb_endpoint_descriptor *endpoint;
	int retval = -ENOMEM;

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL) {
		dev_err(idev, "Out of memory\n");
		goto error;
	}
	kref_init(&dev->kref);
	mutex_init(&dev->io_mutex);
	sema_init(&dev->limit_sem, WRITES_IN_FLIGHT);
	init_usb_anchor(&dev->submitted);
	
	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = interface;

	dev->read_buffer = NULL;
	dev->read_buffer_length = 0;
	dev->read_packet_length = 0;
	spin_lock_init (&dev->read_buffer_lock);

	init_waitqueue_head (&dev->read_wait);

	dev->interrupt_in_buffer = NULL;
	dev->interrupt_in_endpoint = NULL;
	dev->interrupt_in_urb = NULL;
	dev->interrupt_in_running = 0;
	dev->interrupt_in_done = 0;
	dev->out_buffer = NULL;
	dev->out_filled = 0;
	dev->out_size = 0;
	dev->out_endpointAddr = 0;
	dev->errors = 0;
	
	pic_number++;
	
	if ( interface->cur_altsetting->desc.bNumEndpoints != 2 ) {
		dev_err(idev, "Wring number of endpoints: %d \n", interface->cur_altsetting->desc.bNumEndpoints);
		goto error;
	}
	
	
	/* EP1 */
	endpoint = &interface->cur_altsetting->endpoint[0].desc;
	if ( !usb_endpoint_is_bulk_out(endpoint) ) {
		dev_err(&interface->dev, "endpoint 0 \n");
		goto error;
	}
	dev->out_endpointAddr = endpoint->bEndpointAddress;
	dev->out_size = endpoint->wMaxPacketSize;
	dev->out_endpointAddr = endpoint->bEndpointAddress;
	dev->out_buffer = kmalloc(dev->out_size, GFP_KERNEL);
	if (!dev->out_buffer) {
		PERROR("Could not allocate out_buffer \n");
		goto error;
	}
	
	endpoint = &interface->cur_altsetting->endpoint[1].desc;
	if ( !usb_endpoint_is_int_in(endpoint) ) {
		dev_err(&interface->dev, "endpoint 1 \n");
		goto error;
	}
	dev->interrupt_in_endpoint = endpoint;
	dev->read_buffer = kmalloc (read_buffer_size, GFP_KERNEL);
	if (!dev->read_buffer) {
		dev_err(idev, "Couldn't allocate read_buffer\n");
		goto error;
	}
	dev->interrupt_in_buffer = kmalloc (usb_endpoint_maxp(dev->interrupt_in_endpoint), GFP_KERNEL);
	if (!dev->interrupt_in_buffer) {
		dev_err(idev, "Couldn't allocate interrupt_in_buffer\n");
		goto error;
	}
	dev->interrupt_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->interrupt_in_urb) {
		dev_err(idev, "Couldn't allocate interrupt_in_urb\n");
		goto error;
	}
	
	dev->interrupt_in_interval = dev->interrupt_in_endpoint->bInterval;
	
	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);
	
	/* we can register the device now, as it is ready */
	retval = usb_register_dev(interface, &pic_class);
	if (retval) {
		/* something prevented us from registering this driver */
		dev_err(idev,
			"Not able to get a minor for this device.\n");
		usb_set_intfdata(interface, NULL);
		goto error;
	}

	
	/* let the user know what node this device is now attached to */
	dev_info(idev,
		"[godpic] version %s - pic now attached to "DEV_FILE_NAME"%d with minor %d",
		VERSION, pic_number-1, interface->minor);
	return 0;

error:
	if (dev)
		kref_put(&dev->kref, pic_delete);
	return retval;
}

static void pic_disconnect(struct usb_interface *interface)
{
	struct usb_pic *dev;
	int minor = interface->minor;
	
	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);
	
	/* give back our minor */
	usb_deregister_dev(interface, &pic_class);
	
	/* prevent more I/O from starting */
	mutex_lock(&dev->io_mutex);
	dev->interface = NULL;
	mutex_unlock(&dev->io_mutex);
	
	usb_kill_anchored_urbs(&dev->submitted);
	
	/* decrement our usage count */
	kref_put(&dev->kref, pic_delete);

	dev_info(&interface->dev, "pic with minor %d now disconnected", minor);
}

static int pic_suspend(struct usb_interface *intf, pm_message_t message)
{
	return 0;
}

static int pic_resume(struct usb_interface *intf)
{
	return 0;
}

static int pic_reset_resume(struct usb_interface *intf)
{
	return 0;
}

static int pic_pre_reset(struct usb_interface *intf)
{
	return 0;
}

static int pic_post_reset(struct usb_interface *intf)
{
	return 0;
}

static struct usb_driver pic_driver = {
	.name = "pic",
	.probe = pic_probe,
	.disconnect = pic_disconnect,
	.suspend =	pic_suspend,
	.resume =	pic_resume,
	.reset_resume = pic_reset_resume,
	.pre_reset =	pic_pre_reset,
	.post_reset = 	pic_post_reset,
	.id_table = pic_table,
	.supports_autosuspend = 1,
};

module_usb_driver(pic_driver);

MODULE_AUTHOR("Kamil Cukrowski");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION( "USB driver for usb pic comunication" );
MODULE_VERSION(VERSION);
