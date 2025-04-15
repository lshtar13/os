HOST=i686-elf
OS=myos

CC=$(HOST)-gcc
GRUB=grub-mkrescue

BIN=$(OS).bin
ISO=$(OS).iso

OBJS=\
boot.o \
kernel.o \

LSCRIPT=linker.ld

LINKS=\
crti.o \
crtbegin.o \
$(OBJS) \
crtend.o \
crtn.o \

CFLAGS=-ffreestanding -O2 -Wall -Wextra
GRUBCFG=\
menuentry "$(OS)" {\
	multiboot /boot/$(BIN)\
}\

ROOTDIR=sysroot
BOOTDIR=$(ROOTDIR)/boot
GRUBDIR=$(BOOTDIR)/grub

.PHONY: all clean myos.bin install-kernel create install-kernel install-grub_cfg
.SUFFIXES: .o .c .S .iso .cfg

all: $(BIN)

$(BIN): $(LINKS) $(LSCRIPT)
	$(CC) -T $(LSCRIPT) -o $@ $(CFLAGS) -nostdlib -lgcc $(LINKS)
	grub-file --is-x86-multiboot $@

crtbegin.o crtend.o:
	POS=`$(CC) --print-file-name=$@` && cp "$$POS" $@

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

create: $(ISO)

$(ISO): install-kernel install-grub_cfg
	$(GRUB) -o $@ $(ROOTDIR)

install-kernel: $(BIN)
	mkdir -p $(BOOTDIR)
	cp $< $(BOOTDIR)

install-grub_cfg: 
	mkdir -p $(GRUBDIR)
	echo $(GRUBCFG) > $(GRUBDIR)/grub.cfg