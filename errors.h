#pragma once

#include "output.h"
#include "string.h"

void notify(const char* message)
{
    print_colored(message, BACKGROUND_GREEN + TEXT_LIGHT_GRAY);
}

void warn(const char* message)
{
    print_colored(message, BACKGROUND_YELLOW);
}

void error(const char* message)
{
    clear_screen_whole_colored(BACKGROUND_RED);
    print_colored("FATAL ERROR OCCURED:\n\n", BACKGROUND_RED + TEXT_LIGHT_GRAY);
    print_colored(message, BACKGROUND_RED + TEXT_LIGHT_GRAY);
    disable_terminal_cursor();
}

void warn_coded(const char* message, const unsigned int error_code)
{
    print_colored(message, BACKGROUND_YELLOW + TEXT_LIGHT_GRAY);
    print_colored("ERROR CODE: ", TEXT_LIGHT_GRAY);
    print_colored(to_string(error_code), TEXT_LIGHT_GRAY);
    printchar_colored('\n', BACKGROUND_RED + TEXT_LIGHT_GRAY);
}

void error_coded(const char* message, const unsigned int error_code)
{
    clear_screen_whole_colored(BACKGROUND_RED);
    print_colored("FATAL ERROR OCCURED:\n\n", BACKGROUND_RED + TEXT_LIGHT_GRAY);
    print_colored(message, BACKGROUND_RED + TEXT_LIGHT_GRAY);
    print_colored("ERROR CODE: ", BACKGROUND_RED + TEXT_LIGHT_GRAY);
    print_colored(to_string(error_code), BACKGROUND_RED + TEXT_LIGHT_GRAY);
    printchar_colored('\n', BACKGROUND_RED + TEXT_LIGHT_GRAY);
    disable_terminal_cursor();
} 