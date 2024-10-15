global gdt_flush

gdt_flush:
	; load gdt (take adress from param and load it from eax)
	mov eax, [esp+4]
	lgdt [eax]

	; reload segment registers
	mov eax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush ; code segment
.flush:
	ret

global tss_flush
tss_flush:
	mov ax, 0x2B  
	ltr ax        
	ret
