#pragma once

#define MEMORY_BLOCK_SIZE 4096
#define MEMORY_BLOCK_DATA_SIZE_TYPE unsigned short

struct memory_block {
    void* data_pointer;
    MEMORY_BLOCK_DATA_SIZE_TYPE used, offset;
    struct memory_block* next;
};

struct memory_block* current_block;
struct memory_block* first_block;

void setup_allocator() {
    static struct memory_block new_block;
    static char data[MEMORY_BLOCK_SIZE];
    new_block.data_pointer = &data;
    new_block.offset = 0;
    new_block.used = 0;
    current_block = &new_block;
    first_block = current_block;
}

const void* allocate(const unsigned long size) {
    if (size > MEMORY_BLOCK_SIZE)
        return 0;
    if (current_block->used + size > MEMORY_BLOCK_SIZE) {
        static struct memory_block new_block;
        static char data[MEMORY_BLOCK_SIZE];
        new_block.data_pointer = &data;
        current_block->next = &new_block;
        current_block = &new_block;
        const void* address = &((char*)current_block->data_pointer)[current_block->used - current_block->offset];
        current_block->used+=size;
        return address;
    } else {
        const void* address = &((char*)current_block->data_pointer)[current_block->used - current_block->offset];
        current_block->used+=size;
        return address;
    }
    return 0;
}

const void* reallocate(const void* address, const unsigned long old_size, const unsigned long new_size) {
    if (new_size > MEMORY_BLOCK_SIZE)
        return 0;
    else if (old_size >= new_size)
        return address;
    for (struct memory_block* block = first_block; block; block = block->next)
        if ((unsigned int)address >= (unsigned int)block->data_pointer && (unsigned int)address <= (unsigned int)block->data_pointer + MEMORY_BLOCK_SIZE)
            if (new_size - old_size + block->used > MEMORY_BLOCK_SIZE) {
                block->used = MEMORY_BLOCK_SIZE - old_size;
                block->offset = MEMORY_BLOCK_SIZE - ((unsigned int)address - (unsigned int)block->data_pointer);
                static struct memory_block new_block;
                static char data[MEMORY_BLOCK_SIZE];
                new_block.data_pointer = &data;
                new_block.offset = 0;
                new_block.used = 0;
                current_block->next = &new_block;
                current_block = &new_block;
                const void* address = &((char*)current_block->data_pointer)[current_block->used];
                current_block->used+=new_size;
                for (MEMORY_BLOCK_DATA_SIZE_TYPE i = 0; i < current_block->used; i++)
                    ((char*)current_block->data_pointer)[i + new_size - old_size] = ((char*)address)[i];
                return address;
            } else {
                const MEMORY_BLOCK_DATA_SIZE_TYPE amount = block->used - ((unsigned int)address - (unsigned int)block->data_pointer);
                for (MEMORY_BLOCK_DATA_SIZE_TYPE i = 0; i < amount; i++)
                    ((char*)address)[i + new_size] = ((char*)address)[i + old_size];
                for (MEMORY_BLOCK_DATA_SIZE_TYPE i = 0; i < new_size - old_size; i++)
                    ((char*)address)[i + old_size] = '\0';
                block->used+=new_size - old_size;
                return address;
            }
    return 0;
}
