#!/bin/bash

#qemu_version=qemu-system-x86_64
qemu_version=qemu-system-i386

$qemu_version -cdrom dist/x86/kernel.iso
