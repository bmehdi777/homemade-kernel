ENTRY(_start)

SECTIONS {
	. = 2M;

	.text :
	{
		*(.multiboot_header)
		*(.text)
	}

	.rodata : 	
	{
		*(.rodata)
	}

	.data :
	{
		*(.data)
	}

	.bss :
	{
		*(COMMON)
		*(.bss)
	}
}
