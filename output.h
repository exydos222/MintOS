#pragma once
#pragma GCC diagnostic ignored "-Wstringop-overflow"

#include "port.h"
#include "string.h"
#include "filesystem.h"
#include "bool.h"
#include "math.h"

#define TEXT_BLACK 0
#define TEXT_BLUE 1
#define TEXT_GREEN 2
#define TEXT_CYAN 3
#define TEXT_RED 4
#define TEXT_MAGENTA 5
#define TEXT_ORANGE 6
#define TEXT_LIGHT_GRAY 7
#define TEXT_GRAY 8
#define TEXT_LIGHT_BLUE 9
#define TEXT_LIGHT_GREEN 10
#define TEXT_LIGHT_CYAN 11
#define TEXT_LIGHT_RED 12
#define TEXT_LIGHT_MAGENTA 13
#define TEXT_YELLOW 14
#define TEXT_WHITE 15
#define BACKGROUND_BLACK 0x00
#define BACKGROUND_BLUE 0x10
#define BACKGROUND_GREEN 0x20
#define BACKGROUND_CYAN 0x30
#define BACKGROUND_RED 0x40
#define BACKGROUND_MAGENTA 0x50
#define BACKGROUND_ORANGE 0x60
#define BACKGROUND_LIGHT_GRAY 0x70
#define BACKGROUND_GRAY 0x80
#define BACKGROUND_LIGHT_BLUE 0x90
#define BACKGROUND_LIGHT_GREEN 0xA0
#define BACKGROUND_LIGHT_CYAN 0xB0
#define BACKGROUND_LIGHT_RED 0xC0
#define BACKGROUND_LIGHT_MAGENTA 0xD0
#define BACKGROUND_YELLOW 0xE0
#define BACKGROUND_WHITE 0xF0

#define VIDEO_MEMORY_ADDRESS ((char*)0xB8000)

#define MAX_INPUT 256

#define toggle_insert_mode() enable_terminal_cursor((insert_mode = !insert_mode))

char* current_terminal_input;
bool insert_mode;
unsigned short TEXT_POS = 0, LINE_POS = 0, USER_POS = 0;
short CURSOR_OFFSET = 0;

void print(const char* message)
{
	while(*message != 0)
        switch (*message) {
            case '\n':
                if (LINE_POS == 3840) {
                    for (unsigned short i = 0; i < 3838; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                    for (unsigned short i = 3840; i < 4000; i+=2) {
                        VIDEO_MEMORY_ADDRESS[i] = 0;
                        VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                    }
                    TEXT_POS = 3840;
                } else
                    TEXT_POS = LINE_POS+=160;
                *message++;
                continue;
            case '\r':
                TEXT_POS = LINE_POS;
                *message++;
                continue;
            case '\t':
                switch (TEXT_POS) {
                    case 3994:
                        TEXT_POS+=6;
                        for (unsigned short i = 0; i < 3998; i++)
                            VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 2];
                        break;
                    case 3996:
                        TEXT_POS+=4;
                        for (unsigned short i = 0; i < 3996; i++)
                            VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 4];
                        break;
                    case 3998:
                        TEXT_POS+=2;
                        for (unsigned short i = 0; i < 3994; i++)
                            VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 6];
                        break;
                    case 4000:
                        for (unsigned short i = 0; i < 3992; i++)
                            VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 8];
                        break;
                    default:
                        TEXT_POS+=8;
                        if (TEXT_POS > LINE_POS + 159)
                            if (LINE_POS == 3840) {
                                for (unsigned short i = 0; i < 3838; i++)
                                    VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                                for (unsigned short i = 3840; i < 4000; i+=2) {
                                    VIDEO_MEMORY_ADDRESS[i] = 0;
                                    VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                                }
                                TEXT_POS = 3840;
                            } else
                                TEXT_POS = LINE_POS+=160;
                }
                *message++;
                continue;
            default:
                if (TEXT_POS == 4000) {
                    for (unsigned short i = 0; i < 3998; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 2];
                    VIDEO_MEMORY_ADDRESS[3998] = *message;
                } else {
                    VIDEO_MEMORY_ADDRESS[TEXT_POS] = *message;
                    TEXT_POS+=2;
                }
                if (TEXT_POS > LINE_POS + 159)
                    if (LINE_POS == 3840) {
                        for (unsigned short i = 0; i < 3838; i++)
                            VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                        for (unsigned short i = 3840; i < 4000; i+=2) {
                            VIDEO_MEMORY_ADDRESS[i] = 0;
                            VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                        }
                        TEXT_POS = 3840;
                    } else
                        TEXT_POS = LINE_POS+=160;
                *message++;
        }

    output_port(0x3D4, 0x0F);
	output_port(0x3D5, (((TEXT_POS / 2) - CURSOR_OFFSET) & 0xFF));
	output_port(0x3D4, 0x0E);
	output_port(0x3D5, ((((TEXT_POS / 2) - CURSOR_OFFSET) >> 8) & 0xFF));
}

void print_colored(const char* message, const unsigned short color_code)
{
	while(*message != 0)
        switch (*message) {
            case '\n':
                if (LINE_POS == 3840) {
                    for (unsigned short i = 0; i < 3840; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                    for (unsigned short i = 3840; i < 4000; i+=2) {
                        VIDEO_MEMORY_ADDRESS[i] = 0;
                        VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                    }
                    TEXT_POS = 3840;
                } else
                    TEXT_POS = LINE_POS+=160;
                *message++;
                continue;
            case '\r':
                TEXT_POS = LINE_POS;
                *message++;
                continue;
            case '\t':
                switch (TEXT_POS) {
                    case 3994:
                        TEXT_POS+=6;
                        for (unsigned short i = 0; i < 3998; i++)
                            VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 2];
                        break;
                    case 3996:
                        TEXT_POS+=4;
                        for (unsigned short i = 0; i < 3996; i++)
                            VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 4];
                        break;
                    case 3998:
                        TEXT_POS+=2;
                        for (unsigned short i = 0; i < 3994; i++)
                            VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 6];
                        break;
                    case 4000:
                        for (unsigned short i = 0; i < 3992; i++)
                            VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 8];
                        break;
                    default:
                        TEXT_POS+=8;
                        if (TEXT_POS > LINE_POS + 159)
                            if (LINE_POS == 3840) {
                                for (unsigned short i = 0; i < 3838; i++)
                                    VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                                for (unsigned short i = 3840; i < 4000; i+=2) {
                                    VIDEO_MEMORY_ADDRESS[i] = 0;
                                    VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                                }
                                TEXT_POS = 3840;
                            } else
                                TEXT_POS = LINE_POS+=160;
                }
                *message++;
                continue;
            default:
                if (TEXT_POS == 4000) {
                    for (unsigned short i = 0; i < 3998; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 2];
                    VIDEO_MEMORY_ADDRESS[3998] = *message;
                    VIDEO_MEMORY_ADDRESS[3999] = color_code;
                } else {
                    VIDEO_MEMORY_ADDRESS[TEXT_POS] = *message;
                    TEXT_POS++;
                    VIDEO_MEMORY_ADDRESS[TEXT_POS] = color_code;
                    TEXT_POS++;
                }
                if (TEXT_POS > LINE_POS + 159)
                    if (LINE_POS == 3840) {
                        for (unsigned short i = 0; i < 3838; i++)
                            VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                        for (unsigned short i = 3840; i < 4000; i+=2) {
                            VIDEO_MEMORY_ADDRESS[i] = 0;
                            VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                        }
                        TEXT_POS = 3840;
                    } else
                        TEXT_POS = LINE_POS+=160;
                *message++;
        }

    output_port(0x3D4, 0x0F);
	output_port(0x3D5, (((TEXT_POS / 2) - CURSOR_OFFSET) & 0xFF));
	output_port(0x3D4, 0x0E);
	output_port(0x3D5, ((((TEXT_POS / 2) - CURSOR_OFFSET) >> 8) & 0xFF));
}

void printchar(const char message)
{
    switch (message) {
        case '\n':
            if (LINE_POS == 3840) {
                for (unsigned short i = 0; i < 3838; i++)
                    VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                for (unsigned short i = 3840; i < 4000; i+=2) {
                    VIDEO_MEMORY_ADDRESS[i] = 0;
                    VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                }
                TEXT_POS = 3840;
            } else
                TEXT_POS = LINE_POS+=160;
            break;
        case '\r':
            TEXT_POS = LINE_POS;
            break;
        case '\t':
            switch (TEXT_POS) {
                case 3994:
                    TEXT_POS+=6;
                    for (unsigned short i = 0; i < 3998; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 2];
                    break;
                case 3996:
                    TEXT_POS+=4;
                    for (unsigned short i = 0; i < 3996; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 4];
                    break;
                case 3998:
                    TEXT_POS+=2;
                    for (unsigned short i = 0; i < 3994; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 6];
                    break;
                case 4000:
                    for (unsigned short i = 0; i < 3992; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 8];
                    break;
                default:
                    TEXT_POS+=8;
                    if (TEXT_POS > LINE_POS + 159)
                        if (LINE_POS == 3840) {
                            for (unsigned short i = 0; i < 3838; i++)
                                VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                            for (unsigned short i = 3840; i < 4000; i+=2) {
                                VIDEO_MEMORY_ADDRESS[i] = 0;
                                VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                            }
                            TEXT_POS = 3840;
                        } else
                            TEXT_POS = LINE_POS+=160;
            }
            break;
        default:
            if (TEXT_POS == 4000) {
                for (unsigned short i = 0; i < 3998; i++)
                    VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 2];
                VIDEO_MEMORY_ADDRESS[3998] = message;
            } else {
                VIDEO_MEMORY_ADDRESS[TEXT_POS] = message;
                TEXT_POS+=2;
            }
            if (TEXT_POS > LINE_POS + 159)
                if (LINE_POS == 3840) {
                    for (unsigned short i = 0; i < 3838; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                    for (unsigned short i = 3840; i < 4000; i+=2) {
                        VIDEO_MEMORY_ADDRESS[i] = 0;
                        VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                    }
                    TEXT_POS = 3840;
                } else
                    TEXT_POS = LINE_POS+=160;
    }

    output_port(0x3D4, 0x0F);
	output_port(0x3D5, (((TEXT_POS / 2) - CURSOR_OFFSET) & 0xFF));
	output_port(0x3D4, 0x0E);
	output_port(0x3D5, ((((TEXT_POS / 2) - CURSOR_OFFSET) >> 8) & 0xFF));
}

void printchar_colored(const char message, const unsigned short color_code)
{
    switch (message) {
        case '\n':
            if (LINE_POS == 3840) {
                for (unsigned short i = 0; i < 3840; i++)
                    VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                for (unsigned short i = 3840; i < 4000; i+=2) {
                    VIDEO_MEMORY_ADDRESS[i] = 0;
                    VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                }
                TEXT_POS = 3840;
            } else
                TEXT_POS = LINE_POS+=160;
            break;
        case '\r':
            TEXT_POS = LINE_POS;
            break;
        case '\t':
            switch (TEXT_POS) {
                case 3994:
                    TEXT_POS+=6;
                    for (unsigned short i = 0; i < 3998; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 2];
                    break;
                case 3996:
                    TEXT_POS+=4;
                    for (unsigned short i = 0; i < 3996; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 4];
                    break;
                case 3998:
                    TEXT_POS+=2;
                    for (unsigned short i = 0; i < 3994; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 6];
                    break;
                case 4000:
                    for (unsigned short i = 0; i < 3992; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 8];
                    break;
                default:
                    TEXT_POS+=8;
                    if (TEXT_POS > LINE_POS + 159)
                        if (LINE_POS == 3840) {
                            for (unsigned short i = 0; i < 3838; i++)
                                VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                            for (unsigned short i = 3840; i < 4000; i+=2) {
                                VIDEO_MEMORY_ADDRESS[i] = 0;
                                VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                            }
                            TEXT_POS = 3840;
                        } else
                            TEXT_POS = LINE_POS+=160;
            }
            break;
        default:
            if (TEXT_POS == 4000) {
                for (unsigned short i = 0; i < 3998; i++)
                    VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 2];
                VIDEO_MEMORY_ADDRESS[3998] = message;
                VIDEO_MEMORY_ADDRESS[3999] = color_code;
            } else {
                VIDEO_MEMORY_ADDRESS[TEXT_POS] = message;
                TEXT_POS++;
                VIDEO_MEMORY_ADDRESS[TEXT_POS] = color_code;
                TEXT_POS++;
            }
            if (TEXT_POS > LINE_POS + 159)
                if (LINE_POS == 3840) {
                    for (unsigned short i = 0; i < 3838; i++)
                        VIDEO_MEMORY_ADDRESS[i] = VIDEO_MEMORY_ADDRESS[i + 160];
                    for (unsigned short i = 3840; i < 4000; i+=2) {
                        VIDEO_MEMORY_ADDRESS[i] = 0;
                        VIDEO_MEMORY_ADDRESS[i + 1] = 7;
                    }
                    TEXT_POS = 3840;
                } else
                    TEXT_POS = LINE_POS+=160;
    }

    output_port(0x3D4, 0x0F);
	output_port(0x3D5, (((TEXT_POS / 2) - CURSOR_OFFSET) & 0xFF));
	output_port(0x3D4, 0x0E);
	output_port(0x3D5, ((((TEXT_POS / 2) - CURSOR_OFFSET) >> 8) & 0xFF));
}

void clear_screen()
{
    for (unsigned short i = 0; i < TEXT_POS; i+=2) {
        VIDEO_MEMORY_ADDRESS[i] = 0;
        VIDEO_MEMORY_ADDRESS[i + 1] = 7;
    }
    TEXT_POS = 0;
    printchar('>');
    USER_POS = 1;
}

void clear_screen_whole()
{
    for (unsigned short i = 0; i < 4000; i+=2) {
        VIDEO_MEMORY_ADDRESS[i] = 0;
        VIDEO_MEMORY_ADDRESS[i + 1] = 7;
    }
    TEXT_POS = 0;
}

void clear_screen_colored(const unsigned short color_code)
{
    for (unsigned short i = 0; i < TEXT_POS; i+=2) {
        VIDEO_MEMORY_ADDRESS[i] = 0;
        VIDEO_MEMORY_ADDRESS[i + 1] = color_code;
    }
    TEXT_POS = 0;
    printchar('>');
    USER_POS = 1;
}

void clear_screen_whole_colored(const unsigned short color_code)
{
    for (unsigned short i = 0; i < 4000; i+=2) {
        VIDEO_MEMORY_ADDRESS[i] = 0;
        VIDEO_MEMORY_ADDRESS[i + 1] = color_code;
    }
    TEXT_POS = 0;
}

void enable_terminal_cursor(bool insert_mode)
{
	output_port(0x3D4, 0x0A);
	output_port(0x3D5, (input_port(0x3D5) & 0xC0) | (insert_mode == true ? 0 : 13));

	output_port(0x3D4, 0x0B);
	output_port(0x3D5, (input_port(0x3D5) & 0xE0) | 15);
}

void disable_terminal_cursor()
{
    output_port(0x3D4, 0x0A);
	output_port(0x3D5, 0x20);
}

unsigned short get_cursor_position()
{
    unsigned short pos;
    output_port(0x3D4, 0x0F);
    pos |= input_port(0x3D5);
    output_port(0x3D4, 0x0E);
    return pos |= ((unsigned short)input_port(0x3D5)) << 8;
}

void simulate_terminal_keystroke(const char key) {
    const unsigned short pos = get_cursor_position() * 2;
    if ((pos - USER_POS) / 2 == MAX_INPUT - 1)
        return;
    if (insert_mode == true && CURSOR_OFFSET != 0) {
        current_terminal_input[(pos - USER_POS) / 2] = key;
        VIDEO_MEMORY_ADDRESS[pos] = key;
        VIDEO_MEMORY_ADDRESS[pos + 1] = 7;
    } else {
        string_push(current_terminal_input, key, (pos - USER_POS) / 2);
        TEXT_POS-=CURSOR_OFFSET * 2;
        char update[MAX_INPUT];
        copy_string(update, current_terminal_input);
        substring_one(update, (pos - USER_POS) / 2);
        print(update);
    }
}

void simulate_terminal_keystroke_colored(const char key, const unsigned short color_code) {
    const unsigned short pos = get_cursor_position() * 2;
    if ((pos - USER_POS) / 2 == MAX_INPUT - 1)
        return;
    if (insert_mode == true && CURSOR_OFFSET != 0) {
        current_terminal_input[(pos - USER_POS) / 2] = key;
        VIDEO_MEMORY_ADDRESS[pos] = key;
        VIDEO_MEMORY_ADDRESS[pos + 1] = color_code;
    } else {
        string_push(current_terminal_input, key, (pos - USER_POS) / 2);
        TEXT_POS-=CURSOR_OFFSET * 2;
        char update[MAX_INPUT];
        copy_string(update, current_terminal_input);
        substring_one(update, (pos - USER_POS) / 2);
        print_colored(update, color_code);
    }
}

void simulate_terminal_backspace() {
    const unsigned short length = string_length(current_terminal_input), pos = get_cursor_position() * 2;
    if (insert_mode == true && CURSOR_OFFSET != 0) {
        VIDEO_MEMORY_ADDRESS[pos] = 0;
        VIDEO_MEMORY_ADDRESS[pos + 1] = 7;
        string_pop(current_terminal_input, (pos - USER_POS) / 2);
        VIDEO_MEMORY_ADDRESS[TEXT_POS - 2] = 0;
        VIDEO_MEMORY_ADDRESS[TEXT_POS - 1] = 7;
        TEXT_POS-=CURSOR_OFFSET * 2;
        char update[MAX_INPUT];
        copy_string(update, current_terminal_input);
        substring_one(update, (pos - USER_POS) / 2);
        print(update);
    } else if (TEXT_POS - (CURSOR_OFFSET * 2) > USER_POS) {
        VIDEO_MEMORY_ADDRESS[pos - 2] = 0;
        VIDEO_MEMORY_ADDRESS[pos - 1] = 7;
        string_pop(current_terminal_input, (pos - USER_POS) / 2 - 1);
        VIDEO_MEMORY_ADDRESS[TEXT_POS - 2] = 0;
        VIDEO_MEMORY_ADDRESS[TEXT_POS - 1] = 7;
        TEXT_POS-=(CURSOR_OFFSET + 1) * 2;
        char update[MAX_INPUT];
        copy_string(update, current_terminal_input);
        substring_one(update, (pos - USER_POS) / 2 - 1);
        print(update);
    }
}

void simulate_terminal_cursor_move_left(bool ctrl_down) {
    if (ctrl_down == true)
        CURSOR_OFFSET = (TEXT_POS - USER_POS) / 2;
    else
        CURSOR_OFFSET = min((TEXT_POS - USER_POS) / 2, CURSOR_OFFSET + 1);
    output_port(0x3D4, 0x0F);
    output_port(0x3D5, (((TEXT_POS / 2) - CURSOR_OFFSET) & 0xFF));
    output_port(0x3D4, 0x0E);
    output_port(0x3D5, ((((TEXT_POS / 2) - CURSOR_OFFSET) >> 8) & 0xFF));
}

void simulate_terminal_cursor_move_right(bool ctrl_down) {
    if (ctrl_down == true)
        CURSOR_OFFSET = 0;
    else
        CURSOR_OFFSET = max(0, CURSOR_OFFSET - 1);
    output_port(0x3D4, 0x0F);
    output_port(0x3D5, (((TEXT_POS / 2) - CURSOR_OFFSET) & 0xFF));
    output_port(0x3D4, 0x0E);
    output_port(0x3D5, ((((TEXT_POS / 2) - CURSOR_OFFSET) >> 8) & 0xFF));
}

bool simulate_terminal_command(const char* command) {
    if (string_empty(command)) {
        printchar('\n');
        return true;
    }
    else if (file_exists(command)) {
        execute_file(command);
        return false;
    }
    char path[MAX_PATH + MAX_INPUT + 1];
    copy_string(path, current_directory);
    concatenate_char_to_string(path, '/');
    concatenate_string_to_string(path, command);
    if (file_exists(path)) {
        execute_file(path);
        return false;
    }

    print_colored("\nUnknown command \'", TEXT_LIGHT_GREEN);
    print_colored(command, TEXT_LIGHT_GREEN);
    print_colored("\'\n", TEXT_LIGHT_GREEN);
    return true;
}

void simulate_terminal_newline(bool simulate_command) {
    if (simulate_command == true) {
        if (simulate_terminal_command(current_terminal_input) == false)
            return;
    } else
        printchar('\n');
    current_terminal_input[0] = '\0';
    CURSOR_OFFSET = 0;
    print(current_directory);
    printchar('>');
    USER_POS = TEXT_POS;
}

void simulate_terminal_newline_colored(bool simulate_command, const unsigned short color_code) {
    if (simulate_command == true) {
        if (simulate_terminal_command(current_terminal_input) == false)
            return;
    } else
        printchar('\n');
    current_terminal_input[0] = '\0';
    CURSOR_OFFSET = 0;
    print_colored(current_directory, color_code);
    printchar_colored('>', color_code);
    USER_POS = TEXT_POS;
}

void simulate_terminal_autocomplete() {

}

void simulate_terminal_autocomplete_colored(unsigned short color_code) {
    
}
