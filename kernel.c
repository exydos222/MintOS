#include "output.h"
#include "input.h"
#include "pic.h"
#include "gdt.h"
#include "idt.h"
#include "memory.h"

void kernel_main()
{
	setup_allocator();
	setup_keyboard();
	current_directory = (char*)allocate(1);
	current_terminal_input = (char*)allocate(1);
	setup_gdt();
	setup_idt();
	remap_pic();
	
	clear_screen_whole();
	print_colored("MintOS Kernel Terminal\n\n>", TEXT_LIGHT_GREEN);
	USER_POS = TEXT_POS;
}