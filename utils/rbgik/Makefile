INSTALL_DIR=/usr/local/
LIBS=
CFLAGS=$(shell pkg-config --libs gtk+-3.0) $(shell pkg-config --cflags gtk+-3.0) -I/usr/include/libusb-1.0 -lusb-1.0 -ljack -laubio -I/usr/include/aubio/ -lm -lrt
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

distclean: clean
	rm $(obj) || true
	
