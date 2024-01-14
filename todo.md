# Todo

- Right now, I assemble everything with nasm -f elf64 : it produces a 64 bit elf. Even if I tell the assembler to run in 32 bits,
it seems that C code doesnt work properly (stack frame doesn't seems aligned); fix it : create the gdt/paging/etc
