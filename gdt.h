#pragma once
#pragma GCC diagnostic ignored "-Wint-conversion"

struct gdt_entry
{
	unsigned short limit;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr pgdt;

extern void load_gdt();

void set_gdt_entry(const unsigned char entry, const unsigned int base, const unsigned int limit, const unsigned char access, const unsigned char granularity)
{
	gdt[entry].base_low = (base & 0xFFFF);
    gdt[entry].base_middle = (base >> 16) & 0xFF;
    gdt[entry].base_high = (base >> 24) & 0xFF;

    gdt[entry].limit = (limit & 0xFFFF);
    gdt[entry].granularity = (limit >> 16) & 0x0F;

    gdt[entry].granularity |= granularity & 0xF0;
    gdt[entry].access = access;
}

void setup_gdt()
{
	pgdt.limit = sizeof(gdt) - 1;
    pgdt.base = &gdt;

    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    load_gdt(&pgdt);
}