// ISSUES : POINTER INVALIDATION ON REALLOCATE

#pragma once

#define MEMORY_BLOCK_SIZE 4096
#define MEMORY_BLOCK_DATA_SIZE_TYPE unsigned short

struct memory_block {
    void* data_pointer;
    MEMORY_BLOCK_DATA_SIZE_TYPE used;
    struct memory_block* next;
};

struct memory_block* first_block;

void setup_allocator() {
    static char data[MEMORY_BLOCK_SIZE];
    static struct memory_block new_block;
    new_block.data_pointer = &data;
    first_block = &new_block;
}

const void* allocate(const MEMORY_BLOCK_DATA_SIZE_TYPE size) {
    if (size > MEMORY_BLOCK_SIZE)
        return 0;
    for (struct memory_block* block = first_block; block; block = block->next)
        if (block->used + size > MEMORY_BLOCK_SIZE) {
            if (block->next)
                continue;
            static char data[MEMORY_BLOCK_SIZE];
            static struct memory_block new_block;
            new_block.data_pointer = &data;
            block->next = &new_block;
            block->next->used+=size;
            return block->next->data_pointer;
        } else {
            const void* address = &((char*)block->data_pointer)[block->used];
            block->used+=size;
            return address;
        }
    return 0;
}

void deallocate(const void* address, const MEMORY_BLOCK_DATA_SIZE_TYPE size) {
    for (struct memory_block* block = first_block; block; block = block->next)
        if ((unsigned int)address >= (unsigned int)block->data_pointer && (unsigned int)address <= (unsigned int)block->data_pointer + MEMORY_BLOCK_SIZE) {
            for (MEMORY_BLOCK_DATA_SIZE_TYPE i = (unsigned int)address - (unsigned int)block->data_pointer + size; i < block->used; i++)
                ((char*)block->data_pointer)[i - size] = ((char*)block->data_pointer)[i];
            for (MEMORY_BLOCK_DATA_SIZE_TYPE i = 0; i < size; i++)
                ((char*)block->data_pointer)[block->used - i - 1] = 0;
            block->used -= size;
        }
}

const void* reallocate(const void* address, const MEMORY_BLOCK_DATA_SIZE_TYPE old_size, const MEMORY_BLOCK_DATA_SIZE_TYPE new_size) {
    if (new_size > MEMORY_BLOCK_SIZE)
        return 0;
    if (old_size >= new_size) {
        return address;
    } else
        for (struct memory_block* block = first_block; block; block = block->next)
            if ((unsigned int)address >= (unsigned int)block->data_pointer && (unsigned int)address <= (unsigned int)block->data_pointer + MEMORY_BLOCK_SIZE)
                if (block->used - old_size + new_size > MEMORY_BLOCK_SIZE) {
                    address = allocate(new_size);
                    const MEMORY_BLOCK_DATA_SIZE_TYPE old_end = (unsigned int)address - (unsigned int)block->data_pointer + old_size;
                    for (MEMORY_BLOCK_DATA_SIZE_TYPE i = old_end; i < block->used; i++) {
                        ((char*)address)[i - old_end] = ((char*)block->data_pointer)[i - old_size];
                        ((char*)block->data_pointer)[i - old_size] = ((char*)block->data_pointer)[i];
                    }
                    for (MEMORY_BLOCK_DATA_SIZE_TYPE i = 0; i < old_size; i++)
                        ((char*)block->data_pointer)[block->used - i - 1] = 0;
                    block->used -= old_size;
                    return address;
                } else {
                    const MEMORY_BLOCK_DATA_SIZE_TYPE old_end = (unsigned int)address - (unsigned int)block->data_pointer + old_size;
                    for (MEMORY_BLOCK_DATA_SIZE_TYPE i = old_end; i < block->used; i++)
                        ((char*)block->data_pointer)[i + new_size - old_size] = ((char*)block->data_pointer)[i];
                    for (MEMORY_BLOCK_DATA_SIZE_TYPE i = 0; i < new_size - old_size; i++)
                        ((char*)block->data_pointer)[old_end + i] = 0;
                    block->used += new_size - old_size;
                    return address;
                }
}