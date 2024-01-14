ENTRY(_start)

SECTIONS {
	. = 2M;

	.boot :
	{
		KEEP(*(.multiboot_header))
	}

	.text :
	{
		*(.text)
	}
}
