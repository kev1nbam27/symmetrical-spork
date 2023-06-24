#!/bin/zsh

gcc -Ignu-efi-dir/inc -fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -c main.c -o main.o
ld -shared -Bsymbolic -L../gnu-efi/x86_64/lib -L../gnu-efi/x86_64/gnuefi -T../gnu-efi/gnuefi/elf_x86_64_efi.lds ../gnu-efi/x86_64/gnuefi/crt0-efi-x86_64.o main.o -o main.so -lgnuefi -lefi
objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym  -j .rel -j .rela -j .reloc --target efi-app-x86_64 --subsystem=10 main.so main.efi

mv main.efi BOOTX64.EFI

dd if=/dev/zero of=fat.img bs=1k count=1440
mformat -i fat.img -f 1440 ::
mmd -i fat.img ::/EFI
mmd -i fat.img ::/EFI/BOOT
mcopy -i fat.img BOOTX64.EFI ::/EFI/BOOT

mkgpt -o hdimage.bin --image-size 4096 --part fat.img --type system
