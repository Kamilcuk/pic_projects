
CFLAGS_gtk=$(shell pkg-config --libs gtk+-3.0) $(shell pkg-config --cflags gtk+-3.0)
CFLAGS_aubio=-ljack -laubio -I/usr/include/aubio/
CFLAGS=-I/usr/include/libusb-1.0 -lusb-1.0  -lm -lrt $(CFLAGS_aubio) $(CFLAGS_gtk)

INSTALL_DIR=/usr/local/
LIBS=
CC=gcc $(LIBS) 
obj=rbgik
rbgik-o=rbgik.o

all: $(obj)

$(obj): $(obj).c
	for i in $($@-o); do make $$i; done
	$(CC) $(CFLAGS) $($@-o) -o $@
	
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

install:
	install $(obj) $(INSTALL_DIR)/bin

uninstall:
	cd $(INSTALL_DIR)/bin && rm -f $(obj)

clean:
	rm -f *.o || true
	rm $(obj) || true
	
