nasm -f elf32 bootloader.asm -o "build\bootloader.asm.o"
gcc -m32 -c kernel.c -o "build\kernel.c.o" -ffreestanding -nostdlib -nostdinc -O2 -fno-stack-check -fno-stack-protector -mno-stack-arg-probe
ld -m i386pe -T link.ld -o "build\kernel" "build\bootloader.asm.o" "build\kernel.c.o" -build-id=none
objcopy -O elf32-i386 "build\kernel" "build\kernel.elf"