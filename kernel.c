#include "output.h"
#include "input.h"
#include "pic.h"
#include "gdt.h"
#include "idt.h"

void kernel_main()
{
	setup_allocator();
	current_terminal_input = (char*)allocate(1);
	current_directory = (char*)allocate(1);
	current_directory[0] = '\0';
	setup_gdt();
	setup_idt();
	remap_pic();
	setup_keyboard();
	
	clear_screen_whole();
	print_colored("MintOS Kernel Terminal\n\n>", TEXT_LIGHT_GREEN);
	USER_POS = TEXT_POS;
}