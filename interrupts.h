#pragma once

#include "pic.h"
#include "errors.h"

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

#define DIVISION_BY_ZERO 0
#define DEBUG 1
#define NON_MASKABLE_INTERRUPT 2
#define BREAKPOINT 3
#define INTO_DETECTED_OVERFLOW 4
#define OUT_OF_BOUNDS 5
#define INVALID_OPCODE 6
#define NO_COPROCESSOR 7
#define DOUBLE_FAULT 8
#define COPROCESSOR_SEGMENT_OVERRUN 9
#define INVALID_TSS 10
#define SEGMENT_NOT_PRESENT 11
#define STACK_FAULT 12
#define GENERAL_PROTECTION_FAULT 13
#define PAGE_FAULT 14
#define FLOATING_POINT 16
#define ALIGNMENT_CHECK 17
#define MACHINE_CHECK 18
#define SIMD_FLOATING_POINT 19
#define VIRTUALIZATION 20
#define CONTROL_PROTECTION 21
#define HYPERVISOR 28
#define COMMUNICATION 29
#define SECURITY 30

struct registers
{
    unsigned int ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int interrupt_id, error_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

typedef void (*hook_function)(struct registers);
struct interrupt_handler {
    unsigned char count;
    hook_function hooks[256];
};
struct interrupt_handler interrupt_handlers[256];

void register_interrupt_hook(const unsigned char interrupt, const hook_function hook)
{
    interrupt_handlers[interrupt].hooks[interrupt_handlers[interrupt].count] = hook;
    interrupt_handlers[interrupt].count++;
}

void isr_handler(const struct registers registers)
{
    for (unsigned char i = 0; i < interrupt_handlers[registers.interrupt_id].count; i++)
        if (interrupt_handlers[registers.interrupt_id].hooks)
            interrupt_handlers[registers.interrupt_id].hooks[i](registers);

    switch (registers.interrupt_id) {
        case DIVISION_BY_ZERO:
            warn("DIVISION BY ZERO EXCEPTION\n");
            break;
        case DEBUG:
            notify("DEBUG EXCEPTION\n");
            break;
        case BREAKPOINT:
            notify("BREAKPOINT EXCEPTION\n");
            break;
        case INTO_DETECTED_OVERFLOW:
            notify("INFO DETECTED OVERFLOW EXCEPTION\n");
            break;
        case OUT_OF_BOUNDS:
            warn("OUT OF BOUNDS EXCEPTION\n");
            break;
        case INVALID_OPCODE:
            warn("INVALID OPCODE EXCEPTION\n");
            break;
        case NO_COPROCESSOR:
            warn("NO COPROCESSOR EXCEPTION\n");
            break;
        case DOUBLE_FAULT:
            error_coded("DOUBLE FAULT EXCEPTION\n", registers.error_code);
            break;
        case COPROCESSOR_SEGMENT_OVERRUN:
            warn("COPROCESSOR SEGMENT OVERRUN EXCEPTION\n");
            break;
        case INVALID_TSS:
            warn_coded("INVALID TSS EXCEPTION\n", registers.error_code);
            break;
        case SEGMENT_NOT_PRESENT:
            warn_coded("SEGMENT NOT PRESENT EXCEPTION\n", registers.error_code);
            break;
        case STACK_FAULT:
            warn_coded("STACK FAULT EXCEPTION\n", registers.error_code);
            break;
        case GENERAL_PROTECTION_FAULT:
            warn_coded("GENERAL PROTECTION FAULT EXCEPTION\n", registers.error_code);
            break;
        case PAGE_FAULT:
            warn_coded("PAGE FAULT EXCEPTION\n", registers.error_code);
            break;
        case FLOATING_POINT:
            warn("FLOATING POINT EXCEPTION\n");
            break;
        case ALIGNMENT_CHECK:
            warn_coded("ALIGNMENT CHECK EXCEPTION\n", registers.error_code);
            break;
        case MACHINE_CHECK:
            error("MACHINE CHECK EXCEPTION\n");
            break;
        case SIMD_FLOATING_POINT:
            warn("SIMD FLOATING POINT EXCEPTION\n");
            break;
        case VIRTUALIZATION:
            warn("VIRTUALIZATION EXCEPTION\n");
            break;
        case CONTROL_PROTECTION:
            warn_coded("CONTROL PROTECTION EXCEPTION\n", registers.error_code);
            break;
        case HYPERVISOR:
            warn("HYPERVISOR EXCEPTION\n");
            break;
        case COMMUNICATION:
            warn_coded("COMMUNICATION EXCEPTION\n", registers.error_code);
            break;
        case SECURITY:
            warn_coded("SECURITY EXCEPTION\n", registers.error_code);
            break;
        default:
            warn("UNDOCUMENTED EXCEPTION OCCURED\n");
            break;
    }
}

void irq_handler(const struct registers registers)
{
    for (unsigned char i = 0; i < interrupt_handlers[registers.interrupt_id].count; i++)
        if (interrupt_handlers[registers.interrupt_id].hooks)
            interrupt_handlers[registers.interrupt_id].hooks[i](registers);

    pic_end_master();
}