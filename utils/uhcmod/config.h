#ifndef _UHCMOD_CONFIG_H_
#define _UHCMOD_CONFIG_H_

/* file created in /dev , used in usb_class_driver */
#define DEV_FILE_NAME "uhc"
#define USB_UHCMOD_MINOR_BASE 240

/* Define these values to match your devices */
#define UHCMOD_USB_VENDOR_ID 0xffff
#define UHCMOD_USB_PRODUCT_ID 0x0003


#define ROWS_PER_CTRL 2 /* number of rows every hd44780 has */
#define DISP_COLS 40  /* number of columns every hd44780 has */

#define DISP_ROWS ((ROWS_PER_CTRL * dev->lcd_num))  /* number of rows // HELL OF A BAD THING! */
#define ONE_CTRL_DISP_SIZE ((DISP_COLS*ROWS_PER_CTRL)) /* number of cells in one controller */
#define DISP_SIZE ((DISP_COLS*DISP_ROWS)) /* size of a whole display */

#define TABSTOP   3 /* Length of tabs */


/* how many urbs can be submitted at one time 
 * does not allows user to alloc all memory */
#define WRITES_IN_FLIGHT 6

/* load default cgram? */
#define LOAD_CGRAM 1
#include "cgram_default.h"


#define PINFO(fmt, ...) pr_info("[uhcmod] " fmt, ##__VA_ARGS__)
#define PWARN(fmt, ...) pr_warn("[uhcmod] warn " fmt, ##__VA_ARGS__)
#define PERROR(fmt, ...) pr_err("[uhcmod] err " fmt, ##__VA_ARGS__)


/* error found */
#define PDEBUG_CHECKER_ERROR(fmt, ...)
//#define PDEBUG_CHECKER_ERROR(fmt, ...) printk("[uhcmod]erorr on display:" fmt, ##__VA_ARGS__)


#define PDEBUG(fmt, ...)
#define PDEBUG_OPERATION(fmt, ...) 
#define PDEBUG_HD44780(fmt, ...)
#define PDEBUG_TIMER(fmt, ...)
#define PDEBUG_CHECKER(fmt, ...)
//#define PDEBUG(fmt, ...) printk("[uhcmod]debug:" fmt, ##__VA_ARGS__)
//#define PDEBUG_OPERATION(fmt, ...) printk("[uhcmod]operation:" fmt, ##__VA_ARGS__)
//#define PDEBUG_HD44780(fmt, ...) printk("[uhcmod]HD44780:" fmt, ##__VA_ARGS__)
//#define PDEBUG_TIMER(fmt, ...) printk("[uhcmod]timer:" fmt, ##__VA_ARGS__)
//#define PDEBUG_CHECKER(fmt, ...) printk("[uhcmod]checker:" fmt, ##__VA_ARGS__)


#define RS_DATA     (0x02)
#define RS_INST     (0x00)
#define RW_READ     (0x01)
#define RW_WRITE    (0x00)


#define CAKE_RW_BIT       0b00000001
#define CAKE_RS_BIT       0b00000010
#define CAKE_CTRL_NR_BITS 0b00011100
#define CAKE_FILLING_BITS 0b11100000
#define CAKE_FLAG_BITS    ((CAKE_RS_BIT | CAKE_RW_BIT))


// packet modes 
#define CAKE_FILLING_RAW 		0<<5
#define CAKE_FILLING_ALL_RAW 		1<<5
#define CAKE_FILLING_NUM_READ 		2<<5
#define CAKE_FILLING_SET_READ 		3<<5
#define CAKE_FILLING_GET_CONFIG 	4<<5
#define CAKE_FILLING_GET_INFO	 	5<<5


#endif /* _UHCMOD_CONFIG_H_ */

