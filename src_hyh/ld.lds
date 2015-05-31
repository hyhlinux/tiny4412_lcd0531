OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm",
	      "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(main)
SECTIONS
{
	. = 0x50008000;

	.text : {
		start.o 
		*(.text)
	}
	. = ALIGN(4);

	start_shell_cmd_add = .;
	.shell_cmd_ : {
		*(.shell_cmd_)
	}
	end_shell_cmd_add = .;
	. = ALIGN(4);

	.data : {
		*(.data)
	}
	. = ALIGN(4);

	
	_start_bss_add	= .;
	.bss : {
	*(.bss)
	}
	_end_bss_add = .;
	. = ALIGN(4);
}
