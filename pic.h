#pragma once

#include "port.h"

#define io_wait() output_port(0x80, 0);
#define pic_end_master() output_port(PIC1_COMMAND, PIC_EOI)
#define pic_end_slave() output_port(PIC2_COMMAND, PIC_EOI); output_port(PIC1_COMMAND, PIC_EOI)

#define ICW1_ICW4 0x1
#define ICW1_INIT 0x10
#define ICW4_8086 0x1
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

void remap_pic()
{
	unsigned char a1 = input_port(PIC1_DATA);
    io_wait();
    unsigned char a2 = input_port(PIC2_DATA);
    io_wait();

    output_port(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    output_port(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    output_port(PIC1_DATA, 0x20);
    io_wait();
    output_port(PIC1_DATA, 0x28);
    io_wait();

    output_port(PIC1_DATA, 4);
    io_wait();
    output_port(PIC2_DATA, 2);
    io_wait();

    output_port(PIC1_DATA, ICW4_8086);
    io_wait();
    output_port(PIC2_DATA, ICW4_8086);
    io_wait();

    output_port(PIC1_DATA, a1);
    io_wait();
    output_port(PIC2_DATA, a2);
    io_wait();

    output_port(PIC1_DATA, 0b11111101);
    output_port(PIC2_DATA, 0b11111111);

    asm volatile("sti");
}