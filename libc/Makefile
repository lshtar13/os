HOST=i686-elf
OS=myos

ROOTDIR?=../sysroot
PREFIX=$(ROOTDIR)/usr
INCLUDEDIR=$(PREFIX)/include
LIBDIR=$(PREFIX)/lib

ARCH=arch/i386

AR=$(HOST)-ar
CC=$(HOST)-gcc --sysroot=$(ROOTDIR)

ARCH_HOSTED_OBJS=\

HOSTED_OBJS=\
$(ARCH_HOSTED_OBJS) \

STDLIB_PREFIX=stdlib
STDLIB_OBJS=\
$(STDLIB_PREFIX)/abort.o \

STDIO_PREFIX=stdio
STDIO_OBJS=\
$(STDIO_PREFIX)/printf.o \
$(STDIO_PREFIX)/putchar.o \
$(STDIO_PREFIX)/puts.o \

STRING_PREFIX=string
STRING_OBJS=\
$(STRING_PREFIX)/memcmp.o \
$(STRING_PREFIX)/memcpy.o \
$(STRING_PREFIX)/memmove.o \
$(STRING_PREFIX)/memset.o \
$(STRING_PREFIX)/strlen.o \


FREE_OBJS=\
$(STDLIB_OBJS) \
$(STDIO_OBJS) \
$(STRING_OBJS) \

OBJS=\
$(ARCH_HOSTED_OBJS) \
$(FREE_OBJS) \

LIBK_OBJS=\
$(OBJS:.o=.libk.o) \

LIBC_OBJS=\
$(OBJS) \

#BINARIES=libk.a libc.a
BINARIES=libk.a
ARFLAGS=rcs
CFLAGS=-ffreestanding -O2 -Wall -Wextra

.PHONY: all clean myos.bin install-kernel create install-kernel install-grub_cfg
.SUFFIXES: .o .libk.o .c .S 

all: $(BINARIES)

libc.a: $(LIBC_OBJS)
	$(AR) $(ARFLAGS) $@ $^

libk.a: $(LIBK_OBJS)
	$(AR) $(ARFLAGS) $@ $^

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu99 $(CFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

.c.libk.o:
	$(CC) -D__is_libk -MD -c $< -o $@ -std=gnu99 $(CFLAGS)

.S.libk.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(BINARIES)
	rm -rf $(ROOTDIR)
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-libs: $(BINARIES)
	mkdir -p $(LIBDIR)
	cp $^ $(LIBDIR)

install-headers:
	mkdir -p $(INCLUDEDIR)
	cp -R include/. $(INCLUDEDIR)/.