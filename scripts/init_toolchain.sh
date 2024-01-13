#!/bin/bash

toolchain_folder=toolchain/
if [[ -d "$toolchain_folder" ]]; then
	echo "Toolchain folder already exist. Exiting."
	exit
fi

gcc_cross_compiler_url=https://newos.org/toolchains/x86_64-elf-7.5.0-Linux-x86_64.tar.xz
gcc_cross_compiler=x86_64-elf-7.5.0-Linux-x86_64
gcc_cross_compiler_txz=$gcc_cross_compiler.tar.xz

echo "Uncompressing..."
mkdir toolchain/
wget -P toolchain/ $gcc_cross_compiler_url
cd toolchain/
tar xf $gcc_cross_compiler_txz
rm $gcc_cross_compiler_txz
mv $gcc_cross_compiler/* ./
rm -r $gcc_cross_compiler

echo "Finished."
