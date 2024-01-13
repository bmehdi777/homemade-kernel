kernel_source_files := $(shell find src/kernel/ -name *.c)
kernel_object_files := $(patsubst src/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_asm_source_files := $(shell find src/arch/x86/ -name *.s)
x86_asm_object_files := $(patsubst src/arch/x86/%.s, build/x86/%.o, $(x86_asm_source_files))

x86_object_files := $(kernel_object_files) $(x86_asm_object_files)

$(kernel_object_files): build/kernel/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	./toolchain/bin/x86_64-elf-gcc -c -I src/ -ffreestanding $(patsubst build/kernel/%.o, src/kernel/%.c, $@) -o $@

$(x86_asm_object_files): build/x86/%.o : src/arch/x86/%.s
	mkdir -p $(dir $@) && \
		./toolchain/bin/x86_64-elf-as $(patsubst build/x86/%.o, src/arch/x86/%.s, $@) -o $@

.PHONY: build-x86 clean
build-x86: $(kernel_object_files) $(x86_object_files)
	mkdir -p dist/x86 && \
		./toolchain/bin/x86_64-elf-gcc -T targets/x86/linker.ld -o dist/x86/kernel.bin -ffreestanding -O2 -nostdlib $(x86_object_files) -lgcc && \
		cp dist/x86/kernel.bin targets/x86/iso/boot/kernel.bin && \
		grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86/kernel.iso targets/x86/iso


clean:
	rm -rf build/ dist/
