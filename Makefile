GPPPARAMS = -m32 -fno-use-cxa-atexit -fleading-underscore -fno-exceptions -fno-builtin -nostdlib -fno-rtti -fno-pie # The makefile variables
ASPARAMS = --32
# LDPARAMS = -melf_i386

#objects = loader.o kernel.o gdt.o driver.o port.o interrupts.o interruptstubs.o keyboard.o biology.o sence.o # static pattern.
objects = obj/loader.o \
	obj/kernel.o \
	obj/gdt.o \
	obj/driver.o \
	obj/port.o \
	obj/interrupts.o \
	obj/interruptstubs.o \
	obj/keyboard.o \
	obj/biology.o \
	obj/sence.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ ${GPPPARAMS} -o $@ -c $< # $@ target file; $< Frist dependency file.

obj/%.o: src/%.s
	as ${ASPARAMS} -o $@ $<

# ld: GNU linker. 
# options: -m: Emulates the specified linker.

mykernel.bin: linker.ld ${objects}
	ld -m elf_i386 -no-pie -T $< -o $@ ${objects} 

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

# Grub: The multi-operating system launcher for the GUN project.
# grub-mkrescue: create rescue mode mirroring
mykernel.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "os" {' >> iso/boot/grub/grub.cfg
	echo ' multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo ' boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso
