kernel_source_files := $(shell find src/kernel/ -name *.c)
kernel_object_files := $(patsubst src/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_asm_source_files := $(shell find src/arch/x86/ -name *.asm)
x86_asm_object_files := $(patsubst src/arch/x86/%.asm, build/x86/%.o, $(x86_asm_source_files))

object_files := $(kernel_object_files) $(x86_asm_object_files)

$(kernel_object_files): build/kernel/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	./toolchain/bin/x86_64-elf-gcc -c -I src/ -ffreestanding $(patsubst build/kernel/%.o, src/kernel/%.c, $@) -o $@

$(x86_asm_object_files): build/x86/%.o : src/arch/x86/%.asm
	mkdir -p $(dir $@) && \
		nasm -f elf64 $(patsubst build/x86/%.o, src/arch/x86/%.asm, $@) -o $@

.PHONY: build-x86 clean
build-x86: $(object_files)
	mkdir -p dist/x86 && \
		./toolchain/bin/x86_64-elf-ld -n -o dist/x86/kernel.bin -T targets/x86/linker.ld $(object_files)
		cp dist/x86/kernel.bin targets/x86/iso/boot/kernel.bin && \
		grub-mkrescue -o dist/x86/kernel.iso targets/x86/iso

clean:
	rm -rf build/ dist/
