global _start
extern kmain

section .text
bits 32
_start:
	mov esp, stack_top
	call kmain
	hlt

section .bss
align 16
stack_bottom:
	resb 4096 * 4
stack_top:
