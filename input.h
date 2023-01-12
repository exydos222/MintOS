#pragma once

#include "interrupts.h"
#include "port.h"
#include "string.h"
#include "bool.h"
#include "pic.h"

#define setup_keyboard() register_keyboard_hook(internal_keyboard_manager)

#define register_keyboard_hook(hook) register_interrupt_hook(IRQ1, hook);

bool ctrl_down, left_shift_down, right_shift_down;

struct key_info {
    unsigned char scancode;
    bool pressed_down;
};

struct key_info get_key_info()
{
    const unsigned char scancode = input_port(0x60);
    return (scancode > 128 ? ((struct key_info){scancode - 128, 0}) : ((struct key_info){scancode, 1}));
}

void internal_keyboard_manager()
{
	const struct key_info info = get_key_info();
	if (info.pressed_down)
		switch (info.scancode) {
            case 2:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('!');
                else
                    simulate_terminal_keystroke('1');
                break;
            case 3:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('@');
                else
                    simulate_terminal_keystroke('2');
                break;
            case 4:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('#');
                else
                    simulate_terminal_keystroke('3');
                break;
            case 5:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('$');
                else
                    simulate_terminal_keystroke('4');
                break;
            case 6:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('%');
                else
                    simulate_terminal_keystroke('5');
                break;
            case 7:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('^');
                else
                    simulate_terminal_keystroke('6');
                break;
            case 8:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('&');
                else
                    simulate_terminal_keystroke('7');
                break;
            case 9:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('*');
                else
                    simulate_terminal_keystroke('8');
                break;
            case 10:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('(');
                else
                    simulate_terminal_keystroke('9');
                break;
            case 11:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke(')');
                else
                    simulate_terminal_keystroke('0');
                break;
            case 12:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('_');
                else
                    simulate_terminal_keystroke('-');
                break;
            case 13:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('+');
                else
                    simulate_terminal_keystroke('=');
                break;
            case 14:
                simulate_terminal_backspace();
                break;
            case 15:
                simulate_terminal_autocomplete();
                break;
            case 16:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('Q');
                else
                    simulate_terminal_keystroke('q');
                break;
            case 17:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('W');
                else
                    simulate_terminal_keystroke('w');
                break;
            case 18:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('E');
                else
                    simulate_terminal_keystroke('e');
                break;
            case 19:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('R');
                else
                    simulate_terminal_keystroke('r');
                break;
            case 20:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('T');
                else
                    simulate_terminal_keystroke('t');
                break;
            case 21:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('Y');
                else
                    simulate_terminal_keystroke('y');
                break;
            case 22:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('U');
                else
                    simulate_terminal_keystroke('u');
                break;
            case 23:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('I');
                else
                    simulate_terminal_keystroke('i');
                break;
            case 24:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('O');
                else
                    simulate_terminal_keystroke('o');
                break;
            case 25:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('P');
                else
                    simulate_terminal_keystroke('p');
                break;
            case 26:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('{');
                else
                    simulate_terminal_keystroke('[');
                break;
            case 27:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('}');
                else
                    simulate_terminal_keystroke(']');
                break;
            case 28:
                simulate_terminal_newline_colored(true, TEXT_LIGHT_GREEN);
                break;
			case 29:
				ctrl_down = true;
				break;
            case 30:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('A');
                else
                    simulate_terminal_keystroke('a');
                break;
            case 31:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('S');
                else
                    simulate_terminal_keystroke('s');
                break;
            case 32:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('D');
                else
                    simulate_terminal_keystroke('d');
                break;
            case 33:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('F');
                else
                    simulate_terminal_keystroke('f');
                break;
            case 34:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('G');
                else
                    simulate_terminal_keystroke('g');
                break;
            case 35:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('H');
                else
                    simulate_terminal_keystroke('h');
                break;
            case 36:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('J');
                else
                    simulate_terminal_keystroke('j');
                break;
            case 37:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('K');
                else
                    simulate_terminal_keystroke('k');
                break;
            case 38:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('L');
                else
                    simulate_terminal_keystroke('l');
                break;
            case 39:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke(':');
                else
                    simulate_terminal_keystroke(';');
                break;
            case 40:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('\"');
                else
                    simulate_terminal_keystroke('\'');
                break;
            case 41:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('~');
                else
                    simulate_terminal_keystroke('`');
                break;
			case 42:
				left_shift_down = true;
				break;
            case 44:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('Z');
                else
                    simulate_terminal_keystroke('z');
                break;
            case 45:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('X');
                else
                    simulate_terminal_keystroke('x');
                break;
            case 46:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('C');
                else
                    simulate_terminal_keystroke('c');
                break;
            case 47:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('V');
                else
                    simulate_terminal_keystroke('v');
                break;
            case 48:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('B');
                else
                    simulate_terminal_keystroke('b');
                break;
            case 49:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('N');
                else
                    simulate_terminal_keystroke('n');
                break;
            case 50:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('M');
                else
                    simulate_terminal_keystroke('m');
                break;
            case 51:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('<');
                else
                    simulate_terminal_keystroke(',');
                break;
            case 52:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('>');
                else
                    simulate_terminal_keystroke('.');
                break;
            case 53:
                if (left_shift_down == true || right_shift_down == true)
                    simulate_terminal_keystroke('?');
                else
                    simulate_terminal_keystroke('/');
                break;
			case 54:
				right_shift_down = true;
				break;
            case 57:
                simulate_terminal_keystroke(' ');
                break;
            case 75:
                simulate_terminal_cursor_move_left(ctrl_down);
                break;
            case 77:
                simulate_terminal_cursor_move_right(ctrl_down);
                break;
            case 82:
                toggle_insert_mode();
                break;
		}
	else
		switch (info.scancode) {
			case 29:
				ctrl_down = false;
				break;
			case 42:
				left_shift_down = false;
				break;
			case 54:
				right_shift_down = false;
				break;
		}
}
