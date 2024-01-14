global _start
extern kmain

section .text
bits 32
_start:
	mov esp, stack_top

	; set up paging
	; load gdt here before entering in C code
	; set CPU to long mode (PM provided by grub)

		call kmain
	hlt

section .bss
align 4096
stack_bottom:
	resb 4096 * 4
stack_top:
