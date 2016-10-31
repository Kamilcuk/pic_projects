
/*
 * voltpic module - ver 0.1
 * 
 * voltpic.c
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
 * voltpic driver
 * handle voltpic compatible programmed pic device usb driver module
 *
 * This driver is based on USB Skeleton driver - 2.0
 *    that is copyrighted 2001-2004 Greg Kroah-Hartman (greg@kroah.com)
 *    and licensed under GPL version 2.
 * 
 * USB Skeleton driver - 2.0 is based on the 2.6.3 version of drivers/usb/usb-voltpiceton.c 
 * but has been rewritten to be easy to read and use.
 *
 */
 
#define VOLTPIC_VERSION "0.0.6"

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
#include <linux/usb.h>
#include <linux/mutex.h>

/* Define these values to match your devices */
#define USB_VOLTPIC_VENDOR_ID	0xffff
#define USB_VOLTPIC_PRODUCT_ID	0x0002

#define DEV_FILE_NAME "voltpic"
#define USB_VOLTPIC_MINOR_BASE	241

/* reference maximal voltage in volt */
#define VOLTAGE_REFERENCE_MAX 5
/* count of bytes readed */
#define METER_CNT 10

/* table of devices that work with this driver */
static const struct usb_device_id voltpic_table[] = {
	{ USB_DEVICE(USB_VOLTPIC_VENDOR_ID, USB_VOLTPIC_PRODUCT_ID) },
	{ }					/* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, voltpic_table);


/* Structure to hold all of our device specific stuff */
struct usb_voltpic {
	struct usb_device	*udev;			/* the usb device for this device */
	struct usb_interface 	*interface;		/* the interface for this device */
	unsigned char 		*bulk_in_buffer;		/* the buffer to receive data */
	size_t			bulk_in_size;		/* the size of the receive buffer */
	__u8			bulk_in_endpointAddr;	/* the address of the bulk in endpoint */
	struct kref		kref;
	struct mutex		io_mutex;		/* synchronize I/O with disconnect */
};
#define to_voltpic_dev(d) container_of(d, struct usb_voltpic, kref)

static struct usb_driver voltpic_driver;

static unsigned char voltpic_number = 0; /* number of voltpics connected */

static int meter[METER_CNT]; /* what voltometer shows */


#define PDEBUG(...) /* place holding */
static int voltometer_read(struct usb_voltpic *dev)
{
	int retval;
	int actual_size;
	unsigned char i;
	
	/* do a blocking bulk read to get data from the device */
	retval = usb_bulk_msg(dev->udev,
				usb_rcvbulkpipe(dev->udev, dev->bulk_in_endpointAddr),
				dev->bulk_in_buffer,
				dev->bulk_in_size,
				&actual_size,
				HZ*10);
	
	if (retval) {
		dev_err(&dev->interface->dev,
			"%s - failed  failed usb_bulk_msg, error %d\n",
			__func__, retval);
		return retval;
	}
	
	PDEBUG(" readed %d bytes: ", actual_size);
	for (i=0; i<METER_CNT; i++) {
		/* convert big endian to little endian */
		meter[i] = (dev->bulk_in_buffer[i*2]) | (dev->bulk_in_buffer[i*2+1]<<8);
		/* v contins 10 bits, is left justified, need to convert it to right justified */
		meter[i] = meter[i]>>6;
		
		PDEBUG(" i: %04x", meter[i]);
	}
	PDEBUG(" END\n");
	
	
	return actual_size;
}

static void voltpic_delete(struct kref *kref)
{
	struct usb_voltpic *dev = to_voltpic_dev(kref);
	
	voltpic_number--;
	
	usb_put_dev(dev->udev);
	kfree (dev->bulk_in_buffer);
	kfree (dev);
}

static int voltpic_open(struct inode *inode, struct file *file)
{
	struct usb_voltpic *dev;
	struct usb_interface *interface;
	int subminor;
	int retval = 0;

	subminor = iminor(inode);

	interface = usb_find_interface(&voltpic_driver, subminor);
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

	retval = usb_autopm_get_interface(interface);
	if (retval)
		goto exit;

	/* save our object in the file's private structure */
	file->private_data = dev;
	mutex_unlock(&dev->io_mutex);

exit:
	return retval;
}

static int voltpic_release(struct inode *inode, struct file *file)
{
	struct usb_voltpic *dev;

	dev = file->private_data;
	if (dev == NULL)
		return -ENODEV;

	/* allow the device to be autosuspended */
	mutex_lock(&dev->io_mutex);
	if (dev->interface)
		usb_autopm_put_interface(dev->interface);
	mutex_unlock(&dev->io_mutex);
	
	/* decrement the count on our device */
	kref_put(&dev->kref, voltpic_delete);
	return 0;
}

static ssize_t voltpic_read(struct file *file, char __user *buffer, size_t count, loff_t *ppos)
{
	struct usb_voltpic *dev;
	int rv;
	
	dev = file->private_data;
	
	/* if we cannot read at all, return EOF */
	if (!count)
		return 0;
	
	/* no concurrent readers */
	rv = mutex_lock_interruptible(&dev->io_mutex);
	if (rv < 0)
		goto exit;

	if (!dev->interface) {		/* disconnect() was called */
		rv = -ENODEV;
		goto exit;
	}
	
	rv = voltometer_read(dev);
	if (rv < 0 ) {
		goto exit;
	}
	
	/*copy the data to userspace */
	if ( copy_to_user(buffer, meter, min( (size_t)sizeof(meter), count)) )
		rv = -EFAULT;
	else
		rv = count;
	
exit:
	mutex_unlock(&dev->io_mutex);
	return rv;
}

static struct file_operations voltpic_fops = {
	.owner =	THIS_MODULE,
	.read =		voltpic_read,
	.open =		voltpic_open,
	.release =	voltpic_release,
};

static char *voltpic_devnode(struct device *dev, umode_t *mode)
{
        return kasprintf(GFP_KERNEL, DEV_FILE_NAME"%d", voltpic_number-1);
}

/* 
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device registered with devfs and the driver core
 */
static struct usb_class_driver voltpic_class = {
	.name = "voltpic%d",
	.devnode = voltpic_devnode,
	.fops = &voltpic_fops,
	.minor_base = USB_VOLTPIC_MINOR_BASE,
};

static int voltpic_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	struct usb_voltpic *dev = NULL;
	struct usb_endpoint_descriptor *endpoint;
	int retval = -ENOMEM;

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL) {
		dev_err(&interface->dev, "Out of memory\n");
		goto error;
	}
	kref_init(&dev->kref);
	mutex_init(&dev->io_mutex);
	voltpic_number++;
	

	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = interface;
	
	if ( interface->cur_altsetting->desc.bNumEndpoints != 1 ) {
		dev_err(&interface->dev, "Wring number of endpoints\n");
		goto error;
	}
	
	
	/* save endpoint address and information */
	endpoint = &interface->cur_altsetting->endpoint[0].desc;
	dev->bulk_in_size = endpoint->wMaxPacketSize;
	dev->bulk_in_endpointAddr = endpoint->bEndpointAddress;
	dev->bulk_in_buffer = kmalloc(dev->bulk_in_size, GFP_KERNEL);
	if (!dev->bulk_in_buffer) {
		dev_err(&interface->dev, "Out of memory\n");
		goto error;
	}
	
	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);
	
	/* we can register the device now, as it is ready */
	retval = usb_register_dev(interface, &voltpic_class);
	if (retval) {
		/* something prevented us from registering this driver */
		dev_err(&interface->dev,
			"Not able to get a minor for this device.\n");
		usb_set_intfdata(interface, NULL);
		goto error;
	}

	
	/* let the user know what node this device is now attached to */
	dev_info(&interface->dev,
		"voltpic version %s - pic voltometer now attached to "DEV_FILE_NAME"%d with minor %d",
		VOLTPIC_VERSION, voltpic_number-1, interface->minor);
	return 0;

error:
	if (dev)
		kref_put(&dev->kref, voltpic_delete);
	return retval;
}

static void voltpic_disconnect(struct usb_interface *interface)
{
	struct usb_voltpic *dev;
	int minor = interface->minor;
	
	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);
	
	/* give back our minor */
	usb_deregister_dev(interface, &voltpic_class);
	
	/* prevent more I/O from starting */
	mutex_lock(&dev->io_mutex);
	dev->interface = NULL;
	mutex_unlock(&dev->io_mutex);
	
	/* decrement our usage count */
	kref_put(&dev->kref, voltpic_delete);

	dev_info(&interface->dev, "pic voltometer with minor %d now disconnected", minor);
}

static int voltpic_suspend(struct usb_interface *intf, pm_message_t message)
{
	return 0;
}

static int voltpic_resume(struct usb_interface *intf)
{
	return 0;
}

static int voltpic_reset_resume(struct usb_interface *intf)
{
	return 0;
}

static int voltpic_pre_reset(struct usb_interface *intf)
{
	return 0;
}

static int voltpic_post_reset(struct usb_interface *intf)
{
	return 0;
}

static struct usb_driver voltpic_driver = {
	.name = "voltpic",
	.probe = voltpic_probe,
	.disconnect = voltpic_disconnect,
	.suspend =	voltpic_suspend,
	.resume =	voltpic_resume,
	.reset_resume = voltpic_reset_resume,
	.pre_reset =	voltpic_pre_reset,
	.post_reset = 	voltpic_post_reset,
	.id_table = voltpic_table,
	.supports_autosuspend = 1,
};

module_usb_driver(voltpic_driver);

MODULE_AUTHOR("Kamil Cukrowski");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION( "USB driver for programmed as voltometer pic" );
MODULE_VERSION(VOLTPIC_VERSION);
