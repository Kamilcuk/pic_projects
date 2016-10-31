INCLUDE= -I.
DEFINES=
EXTRA_CFLAGS= -Wall -O2 -I$(KERNEL_SRC_DIR)/include 
#		-pipe -ffixed-8 -DMODULE -DMODVERSIONS -finline-functions -fverbose-asm


obj-m += voltpic.o #test1.o #test2.o #test3.o test4.o test5.o test6.o test7.o
#lcdmod-objs += hd44780-operations.o lcdmod-core.o

ALL:    module

install:
	gzip -9 -c $(obj-m:.o=.ko) > $(obj-m:.o=.ko.gz) 
	test -d /lib/modules/$(shell uname -r)/misc/ || mkdir /lib/modules/$(shell uname -r)/misc/
	cp $(obj-m:.o=.ko.gz) /lib/modules/$(shell uname -r)/misc/
	depmod -a

uninstall:
	rm /lib/modules/$(shell uname -r)/misc/$(obj-m:.o=.ko.gz)
	depmod -a

module:
	make -C  /lib/modules/$(shell uname -r)/build M=$(PWD) modules


clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

clean.end:
	cp $(obj-m:.o=.ko) /tmp/ifoayguiurew
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	mv /tmp/ifoayguiurew $(obj-m:.o=.ko)

distclean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


