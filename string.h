#pragma once

#define string_empty(string) (string[0] == '\0')

const char* to_string(unsigned int value)
{
    static char buffer[10];
    char temp[10];
    unsigned char i = 0;

    if (value < 0) {
        buffer[i++] = '-';
        value = -value;
    }

    while (value > 0) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }

    unsigned char j = 0;
    while (i > 0)
        buffer[j++] = temp[--i];

    buffer[j] = '\0';

    return buffer;
}

const unsigned long string_length(const char* string) {
    const char* temp = string;
    unsigned long length = 0;
    while (*temp != '\0') {
        length++;
        *temp++;
    }
    return length;
}

const char* concatenate_string_to_string(char* destination, const char* source)
{
    const unsigned long destination_length = string_length(destination), source_length = string_length(source);
    for (unsigned long i = 0; i < source_length; i++)
        destination[destination_length + i] = source[i];
    destination[destination_length + source_length + 1] = '\0';
    return destination;
}

const char* concatenate_char_to_string(char* destination, const char source)
{
    const unsigned long length = string_length(destination);
    destination[length] = source;
    destination[length + 1] = '\0';
    return destination;
}

const char* string_pop(char* string, const unsigned long pos) {
    const unsigned long length = string_length(string);
    for (unsigned long i = pos; i < length; i++)
        string[i] = string[i + 1];
    string[length - 1] = '\0';
}

const char* string_push(char* string, const char source, const unsigned long pos) {
    const unsigned long length = string_length(string);
    for (unsigned long i = length - 1; i > pos - 1; i--)
        string[i + 1] = string[i];
    string[pos] = source;
    string[length + 1] = '\0';
    return string;
}

const char* copy_string(char* destination, const char* source) {
    const unsigned long length = string_length(source);
    for (unsigned long i = 0; i < length; i++)
        destination[i] = source[i];
    destination[length] = '\0';
    return destination;
}

const char* substring_one(char* string, const unsigned long a) {
    const unsigned long length = string_length(string);
    for (unsigned int i = 0; i < length - a; i++)
        string[i] = string[a + i];
    string[length - a] = '\0';
    return string;
}

const char* substring(char* string, const unsigned long a, const unsigned long b) {
    for (unsigned int i = 0; i < b - a; i++)
        string[i] = string[a + i];
    string[b - a] = '\0';
    return string;
}
