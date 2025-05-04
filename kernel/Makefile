HOST=i686-elf
OS=myos

ROOTDIR?=../sysroot
BOOTDIR=$(ROOTDIR)/boot
GRUBDIR=$(BOOTDIR)/grub
PREFIX=usr
INCLUDEDIR=$(ROOTDIR)/$(PREFIX)/include

ARCH=./arch/i386
KERNEL=./kernel

CC=$(HOST)-gcc --sysroot=$(ROOTDIR) -g
GRUB=grub-mkrescue

BIN=$(OS).bin
ISO=$(OS).iso

GDT_OBJS=\
$(ARCH)/gdt/gdt.o \
$(ARCH)/gdt/gdts.o \

INTERRUPT_OBJS=\
$(ARCH)/interrupt/pic.o \
$(ARCH)/interrupt/isr.o \
$(ARCH)/interrupt/idt.o \
$(ARCH)/interrupt/interrupts.o \

UTIL_OBJS=\
$(ARCH)/util/util.o \

VISUAL_OBJS=\
$(ARCH)/visual/tty.o \

TIMER_OBJS=\
$(ARCH)/timer/timer.o \

ARCH_OBJS=\
$(ARCH)/boot.o \
$(GDT_OBJS) \
$(INTERRUPT_OBJS) \
$(VISUAL_OBJS) \
$(UTIL_OBJS) \
$(TIMER_OBJS) \

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

CFLAGS=-ffreestanding -Wall -Wextra
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