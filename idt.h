#pragma once

struct idt_entry {
   unsigned short offset_1;
   unsigned short selector;
   unsigned char zero;
   unsigned char type_attributes;
   unsigned short offset_2;
} __attribute__((packed));

struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

extern void load_idt();

struct idt_entry idt[256];
struct idt_ptr pidt;

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void set_idt_entry(const unsigned char entry, const unsigned int offset, const unsigned short selector, const unsigned char type_attributes)
{
   idt[entry].offset_1 = offset & 0xFFFF;
   idt[entry].selector = selector;
   idt[entry].zero = 0;
   idt[entry].type_attributes = type_attributes;
   idt[entry].offset_2 = (offset >> 16) & 0xFFFF;
}

void setup_idt()
{
	pidt.limit = sizeof(idt) - 1;
   pidt.base = &idt;

   set_idt_entry(0, (unsigned int)isr0, 0x08, 0x8E);
   set_idt_entry(1, (unsigned int)isr1, 0x08, 0x8E);
   set_idt_entry(2, (unsigned int)isr2, 0x08, 0x8E);
   set_idt_entry(3, (unsigned int)isr3, 0x08, 0x8E);
   set_idt_entry(4, (unsigned int)isr4, 0x08, 0x8E);
   set_idt_entry(5, (unsigned int)isr5, 0x08, 0x8E);
   set_idt_entry(6, (unsigned int)isr6, 0x08, 0x8E);
   set_idt_entry(7, (unsigned int)isr7, 0x08, 0x8E);
   set_idt_entry(8, (unsigned int)isr8, 0x08, 0x8E);
   set_idt_entry(9, (unsigned int)isr9, 0x08, 0x8E);
   set_idt_entry(10, (unsigned int)isr10, 0x08, 0x8E);
   set_idt_entry(11, (unsigned int)isr11, 0x08, 0x8E);
   set_idt_entry(12, (unsigned int)isr12, 0x08, 0x8E);
   set_idt_entry(13, (unsigned int)isr13, 0x08, 0x8E);
   set_idt_entry(14, (unsigned int)isr14, 0x08, 0x8E);
   set_idt_entry(15, (unsigned int)isr15, 0x08, 0x8E);
   set_idt_entry(16, (unsigned int)isr16, 0x08, 0x8E);
   set_idt_entry(17, (unsigned int)isr17, 0x08, 0x8E);
   set_idt_entry(18, (unsigned int)isr18, 0x08, 0x8E);
   set_idt_entry(19, (unsigned int)isr19, 0x08, 0x8E);
   set_idt_entry(20, (unsigned int)isr20, 0x08, 0x8E);
   set_idt_entry(21, (unsigned int)isr21, 0x08, 0x8E);
   set_idt_entry(22, (unsigned int)isr22, 0x08, 0x8E);
   set_idt_entry(23, (unsigned int)isr23, 0x08, 0x8E);
   set_idt_entry(24, (unsigned int)isr24, 0x08, 0x8E);
   set_idt_entry(25, (unsigned int)isr25, 0x08, 0x8E);
   set_idt_entry(26, (unsigned int)isr26, 0x08, 0x8E);
   set_idt_entry(27, (unsigned int)isr27, 0x08, 0x8E);
   set_idt_entry(28, (unsigned int)isr28, 0x08, 0x8E);
   set_idt_entry(29, (unsigned int)isr29, 0x08, 0x8E);
   set_idt_entry(30, (unsigned int)isr30, 0x08, 0x8E);
   set_idt_entry(31, (unsigned int)isr31, 0x08, 0x8E);

   set_idt_entry(32, (unsigned int)irq0, 0x08, 0x8E);
   set_idt_entry(33, (unsigned int)irq1, 0x08, 0x8E);
   set_idt_entry(34, (unsigned int)irq2, 0x08, 0x8E);
   set_idt_entry(35, (unsigned int)irq3, 0x08, 0x8E);
   set_idt_entry(36, (unsigned int)irq4, 0x08, 0x8E);
   set_idt_entry(37, (unsigned int)irq5, 0x08, 0x8E);
   set_idt_entry(38, (unsigned int)irq6, 0x08, 0x8E);
   set_idt_entry(39, (unsigned int)irq7, 0x08, 0x8E);
   set_idt_entry(40, (unsigned int)irq8, 0x08, 0x8E);
   set_idt_entry(41, (unsigned int)irq9, 0x08, 0x8E);
   set_idt_entry(42, (unsigned int)irq10, 0x08, 0x8E);
   set_idt_entry(43, (unsigned int)irq11, 0x08, 0x8E);
   set_idt_entry(44, (unsigned int)irq12, 0x08, 0x8E);
   set_idt_entry(45, (unsigned int)irq13, 0x08, 0x8E);
   set_idt_entry(46, (unsigned int)irq14, 0x08, 0x8E);
   set_idt_entry(47, (unsigned int)irq15, 0x08, 0x8E);

   load_idt(&pidt);
}