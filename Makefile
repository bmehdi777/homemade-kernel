kernel_source_files := $(shell find src/kernel/ -name *.c)
kernel_object_files := $(patsubst src/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_asm_source_files := $(shell find src/arch/x86/ -name *.asm)
x86_asm_object_files := $(patsubst src/arch/x86/%.asm, build/x86/%.o, $(x86_asm_source_files))

lib_source_files := $(shell find src/lib/ -name *.c)
lib_object_files := $(patsubst src/lib/%.c, build/lib/%.o, $(lib_source_files))

object_files := $(x86_asm_object_files) $(kernel_object_files) $(lib_object_files)

$(kernel_object_files): build/kernel/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	./toolchain/bin/x86_64-elf-gcc -m32 -c -Isrc/ -ffreestanding $(patsubst build/kernel/%.o, src/kernel/%.c, $@) -o $@ -g -DDEBUG -Wall -Wextra

$(lib_object_files): build/lib/%.o : src/lib/%.c
	mkdir -p $(dir $@) && \
		./toolchain/bin/x86_64-elf-gcc -m32 -c -Isrc/ -ffreestanding $(patsubst build/lib/%.o, src/lib/%.c, $@) -o $@ -g -DDEBUG -Wall -Wextra

$(x86_asm_object_files): build/x86/%.o : src/arch/x86/%.asm
	mkdir -p $(dir $@) && \
		nasm -f elf32 $(patsubst build/x86/%.o, src/arch/x86/%.asm, $@) -o $@

.PHONY: build-x86 build-debug clean
build-x86: $(object_files)
	mkdir -p dist/x86 && \
		./toolchain/bin/x86_64-elf-ld -m elf_i386 -n -o dist/x86/kernel.bin -T targets/x86/linker.ld -nostdlib $(object_files)
		cp dist/x86/kernel.bin targets/x86/iso/boot/kernel.bin && \
		grub2-mkrescue -o dist/x86/kernel.iso targets/x86/iso

build-debug: build-x86
	./toolchain/bin/x86_64-elf-objcopy --only-keep-debug dist/x86/kernel.bin dist/x86/kernel.debug && \
		./toolchain/bin/x86_64-elf-objcopy --strip-debug dist/x86/kernel.bin && \
		grub2-mkrescue -o dist/x86/kernel.iso targets/x86/iso

clean:
	rm -rf build/ dist/
