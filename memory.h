#pragma once

#define MEMORY_BLOCK_DATA_SIZE 4096

struct memory_block {
    void* data_pointer;
    unsigned short used, offset;
    struct memory_block* next;
};

struct memory_block* current_block;
struct memory_block* first_block;

void setup_allocator() {
    static struct memory_block new_block;
    static char data[MEMORY_BLOCK_DATA_SIZE];
    new_block.data_pointer = &data;
    current_block = &new_block;
    first_block = current_block;
}

const void* allocate(const unsigned long size) {
    if (size > MEMORY_BLOCK_DATA_SIZE)
        return 0;
    if (current_block->used + size > MEMORY_BLOCK_DATA_SIZE) {
        static struct memory_block new_block;
        static char data[MEMORY_BLOCK_DATA_SIZE];
        new_block.data_pointer = &data;
        current_block->next = &new_block;
        current_block = &new_block;
        const void* address = &((char*)current_block->data_pointer)[current_block->used - current_block->offset];
        current_block->used+=size;
        for (unsigned int i = 0; i < current_block->used; i++)
                    ((char*)current_block->data_pointer)[i + new_size - old_size] = ((char*)address)[i];
        return address;
    } else {
        const void* address = &((char*)current_block->data_pointer)[current_block->used - current_block->offset];
        current_block->used+=size;
        return address;
    }
    return 0;
}

const void* reallocate(const void* address, const unsigned long old_size, const unsigned long new_size) {
    if (old_size >= new_size)
        return address;
    for (struct memory_block* block = first_block; block; block = block->next)
        if ((unsigned int)address >= (unsigned int)block->data_pointer && (unsigned int)address <= (unsigned int)block->data_pointer + MEMORY_BLOCK_DATA_SIZE)
            if (new_size - old_size + block->used > MEMORY_BLOCK_DATA_SIZE) {
                block->used = MEMORY_BLOCK_DATA_SIZE - old_size;
                block->offset = MEMORY_BLOCK_DATA_SIZE - ((unsigned int)address - (unsigned int)block->data_pointer);
                static struct memory_block new_block;
                static char data[MEMORY_BLOCK_DATA_SIZE];
                new_block.data_pointer = &data;
                current_block->next = &new_block;
                current_block = &new_block;
                const void* address = &((char*)current_block->data_pointer)[current_block->used];
                current_block->used+=new_size;
                return address;
            } else {
                for (unsigned int i = (unsigned int)address - (unsigned int)block->data_pointer + old_size; i < block->used; i++) {
                    ((char*)block->data_pointer)[i + new_size - old_size] = ((char*)block->data_pointer)[i];
                    ((char*)block->data_pointer)[i] = '\0';
                }
                block->used+=new_size - old_size;
                return address;
            }
    return 0;
}
