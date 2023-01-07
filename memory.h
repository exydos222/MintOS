#pragma once

#define MEMORY_BLOCK_DATA_SIZE 4096

struct memory_block {
    void* data_pointer;
    unsigned short used;
};

struct memory_block* current_block;

void setup_allocator() {
    static struct memory_block new_block;
    static char data[MEMORY_BLOCK_DATA_SIZE];
    new_block.data_pointer = &data;
    current_block = &new_block;
}

const void* allocate(const unsigned long size) {
    if (current_block->used + size > MEMORY_BLOCK_DATA_SIZE) {
        static struct memory_block new_block;
        static char data[MEMORY_BLOCK_DATA_SIZE];
        new_block.data_pointer = &data;
        current_block = &new_block;
        current_block->used+=size;
    } else {
        const void* address = &current_block->data_pointer + current_block->used;
        current_block->used+=size;
        return address;
    }
}

void deallocate(const void* address) {

}