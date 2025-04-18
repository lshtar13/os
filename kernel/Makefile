HOST=i686-elf
OS=myos

ROOTDIR?=../sysroot
BOOTDIR=$(ROOTDIR)/boot
GRUBDIR=$(BOOTDIR)/grub
PREFIX=usr
INCLUDEDIR=$(ROOTDIR)/$(PREFIX)/include

ARCH=./arch/i386
KERNEL=./kernel

CC=$(HOST)-gcc --sysroot=$(ROOTDIR)
GRUB=grub-mkrescue

BIN=$(OS).bin
ISO=$(OS).iso

ARCH_OBJS=\
$(ARCH)/boot.o \
$(ARCH)/tty.o \

KERNEL_OBJS=\
$(KERNEL)/kernel.o \

OBJS=\
$(ARCH)/crti.o \
$(ARCH)/crtbegin.o \
$(ARCH_OBJS) \
$(KERNEL_OBJS) \
$(ARCH)/crtend.o \
$(ARCH)/crtn.o \

LSCRIPT=$(ARCH)/linker.ld

#LIBS= -nostdlib -lk -lgcc
LIBS= -lk 

LINKS=\
$(OBJS) \
$(LIBS) \

CFLAGS=-ffreestanding -O2 -Wall -Wextra
GRUBCFG=\
menuentry "$(OS)" {\
	multiboot /boot/$(BIN)\
}\

.PHONY: all clean myos.bin install-kernel create install-kernel install-grub_cfg
.SUFFIXES: .o .c .S .iso .cfg

all: $(BIN)

$(BIN): $(OBJS) $(LSCRIPT)
	$(CC) -T $(LSCRIPT) -o $@ $(CFLAGS) -nostdlib -lgcc $(LINKS)
	grub-file --is-x86-multiboot $@

$(ARCH)/crtbegin.o $(ARCH)/crtend.o:
	POS=`$(CC) --print-file-name=$(@F)` && cp "$$POS" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu99 $(CFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(ISO)
	rm -rf $(ROOTDIR)
	rm -f $(BIN)
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: $(ISO)

$(ISO): install-headers install-kernel install-grub_cfg
	$(GRUB) -o $@ $(ROOTDIR)

install-headers:
	mkdir -p $(INCLUDEDIR)
	cp -R include/. $(INCLUDEDIR)/.

install-kernel: $(BIN)
	mkdir -p $(BOOTDIR)
	cp $< $(BOOTDIR)

install-grub_cfg: 
	mkdir -p $(GRUBDIR)
	echo $(GRUBCFG) > $(GRUBDIR)/grub.cfg