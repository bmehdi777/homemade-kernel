# Homemade kernel (32bit, for now)

This is a recreational project.

## Install toolchain

Execute `./scripts/init_toolchain.sh` at the root of the project : it will download the cross-compiler in the folder toolchain/.

> You must do that or modify the Makefile to build the project.

## Build

You only need to run :

```sh
make build-x86
```

## Debug

To debug, first launch :

```sh
make build-debug
```

Then execute : 

```sh
./scripts/debug-qemu.sh
```

It will create a gdb session on localhost:1234.
To connect to the qemu session with gdb : 

```sh
gdb -x ./gdb/debug_commands.txt
```

> The __breakpoint__ set in this file is arbitrary : it the the address of _kmain_. To know the address of a particular function, use `readelf --syms dist/x86/kernel.bin` and get the address of the function.

In gdb : 

```gdb
layout src
set directories src/
symbol-file dist/x86/kernel.debug
n
```
