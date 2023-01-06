#pragma once

unsigned char input_port(const unsigned int port)
{
   unsigned char ret;
   asm volatile("inb %%dx,%%al" : "=a" (ret):"d" (port));
   return ret;
}

void output_port(const unsigned int port, const unsigned char value)
{
    asm volatile("outb %%al,%%dx" : : "d" (port), "a" (value));
}