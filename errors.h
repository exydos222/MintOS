#pragma once

#include "output.h"
#include "string.h"
#include "bool.h"

void notify(const char* message)
{
    print_colored(message, BACKGROUND_GREEN);
    simulate_terminal_newline_colored(false, TEXT_LIGHT_GREEN);
}

void warn(const char* message)
{
    print_colored(message, BACKGROUND_YELLOW);
    simulate_terminal_newline_colored(false, TEXT_LIGHT_GREEN);
}

void error(const char* message)
{
    clear_screen_whole_colored(BACKGROUND_RED);
    print_colored("FATAL ERROR OCCURED:\n\n", BACKGROUND_RED);
    print_colored(message, BACKGROUND_RED);
    disable_terminal_cursor();
}

void warn_coded(const char* message, const unsigned int error_code)
{
    print_colored(message, BACKGROUND_YELLOW);
    print_colored("\nERROR CODE: ", BACKGROUND_YELLOW);
    print_colored(to_string(error_code), BACKGROUND_YELLOW);
    printchar_colored('\n', BACKGROUND_RED + BACKGROUND_YELLOW);
    simulate_terminal_newline_colored(false, TEXT_LIGHT_GREEN);
}

void error_coded(const char* message, const unsigned int error_code)
{
    clear_screen_whole_colored(BACKGROUND_RED);
    print_colored("FATAL ERROR OCCURED:\n\n", BACKGROUND_RED);
    print_colored(message, BACKGROUND_RED);
    print_colored("\nERROR CODE: ", BACKGROUND_RED);
    print_colored(to_string(error_code), BACKGROUND_RED);
    printchar_colored('\n', BACKGROUND_RED);
    disable_terminal_cursor();
} 