kernel_source_files := $(shell find src/kernel/ -name *.c)
kernel_object_files := $(patsubst src/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_asm_source_files := $(shell find src/arch/x86/ -name *.s)
x86_asm_object_files := $(patsubst find src/arch/x86/%.s, build/arch/x86/%.o, $(x86_asm_source_files))

x86_object_files := $(kernel_object_files) $(x86_asm_object_files)

$(kernel_object_files): build/kernel%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	./toolchain/bin/x86_64-elf-gcc -c -I src/ --ffreestanding $(patsubst build/kernel/%.o, src/kernel/%.c, $@) -o $@

$(x86_asm_object_files): build/arch/x86/%.o : src/arch/x86
