.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp

	/* set up Paging 
	 load GDT here before entering in C code
	 set CPU to long mode (PM is already set by grub) */
	call kmain

	cli
	hlt
.size _start, . - _start

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:


