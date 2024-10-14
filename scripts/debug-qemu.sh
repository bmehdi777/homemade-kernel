#!/bin/bash

#qemu_version=qemu-system-x86_64
qemu_version=qemu-system-i386

echo "Connect to qemu with gdb :"
echo "(gdb) > target remote localhost:1234"

$qemu_version -cdrom dist/x86/kernel.iso -s -S
