#!/bin/zsh

(trap 'kill 0' SIGINT; qemu-system-x86_64 -cpu qemu64 \
  -drive if=pflash,format=raw,unit=0,file=../edk2/x64/OVMF_CODE.fd,readonly=on \
  -drive if=pflash,format=raw,unit=1,file=../edk2/x64/OVMF_VARS.fd \
  -net none \
  -hda hdimage.bin \
  -boot order=d \
  & vncviewer :5900)

#(trap 'kill 0' SIGINT; sudo qemu-system-x86_64 -cpu qemu64 \
#  -L /usr/share/ovmf/x64 \
#  -pflash /usr/share/ovmf/x64/OVMF.fd \
#  -format raw \
#  -cdrom cdimage.iso & vncviewer :5900)
