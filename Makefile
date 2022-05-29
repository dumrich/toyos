CC = i686-elf-gcc
INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc -std=gnu99 

FILES = ./build/boot.o ./build/kernel.o ./build/idt/idt.o ./build/text/text.o ./build/memory/memory.o

all: $(FILES) iso

iso: $(FILES)
	$(CC) -T linker.ld -o ./bin/isodir/boot/toyos.bin -ffreestanding -O0 -nostdlib $(FILES) -lgcc
	grub-mkrescue -o toyos.iso ./bin/isodir 

# Files
./build/boot.o: ./src/boot/boot.s
	i686-elf-as $^ -o $@

./build/kernel.o: ./src/kernel.c
	$(CC) $(INCLUDES) $(FLAGS) -c $^ -o $@

./build/text/text.o: ./src/text/text.c
	$(CC) $(INCLUDES) -I./src/text $(FLAGS) -c $^ -o $@

./build/memory/memory.o: ./src/memory/memory.c
	$(CC) $(INCLUDES) -I./src/memory $(FLAGS) -c $^ -o $@

./build/idt/idt.o: ./src/idt/idt.c
	$(CC) $(INCLUDES) -I./src/idt $(FLAGS) -c $^ -o $@

run: iso
	qemu-system-i386 -hda ./toyos.iso

run-debug: iso
	qemu-system-i386 -hda ./toyos.iso -d int -no-reboot -no-shutdown

clean:
	rm -rf ./bin/toyos.bin ./build/kernel.o ./build/boot.o $(FILES)
