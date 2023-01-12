#pragma once

#define memory_block_SIZE 4096
#define memory_block_DATA_TYPE unsigned short

struct memory_block {
    void* data_pointer;
    memory_block_DATA_TYPE used;
    struct memory_block* next;
};

struct memory_block* first_memory_block;

void setup_allocator() {
    static char data[memory_block_SIZE];
    static struct memory_block new_memory_block;
    new_memory_block.data_pointer = &data;
    first_memory_block = &new_memory_block;
}

const void* allocate(const memory_block_DATA_TYPE size) {
    if (size > memory_block_SIZE)
        return 0;
    for (struct memory_block* memory_block = first_memory_block; memory_block; memory_block = memory_block->next)
        if (memory_block->used + size > memory_block_SIZE) {
            if (memory_block->next)
                continue;
            static char data[memory_block_SIZE];
            static struct memory_block new_memory_block;
            new_memory_block.data_pointer = &data;
            memory_block->next = &new_memory_block;
            memory_block->next->used+=size;
            return memory_block->next->data_pointer;
        } else {
            const void* address = &((char*)memory_block->data_pointer)[memory_block->used];
            memory_block->used+=size;
            return address;
        }
    return 0;
}

void deallocate(const void* address, const memory_block_DATA_TYPE size) {
    for (struct memory_block* memory_block = first_memory_block; memory_block; memory_block = memory_block->next)
        if ((unsigned int)address >= (unsigned int)memory_block->data_pointer && (unsigned int)address <= (unsigned int)memory_block->data_pointer + memory_block_SIZE) {
            for (memory_block_DATA_TYPE i = (unsigned int)address - (unsigned int)memory_block->data_pointer + size; i < memory_block->used; i++)
                ((char*)memory_block->data_pointer)[i - size] = ((char*)memory_block->data_pointer)[i];
            for (memory_block_DATA_TYPE i = 0; i < size; i++)
                ((char*)memory_block->data_pointer)[memory_block->used - i - 1] = 0;
            memory_block->used -= size;
        }
}

const void* reallocate(const void* address, const memory_block_DATA_TYPE old_size, const memory_block_DATA_TYPE new_size) {
    if (new_size > memory_block_SIZE)
        return 0;
    for (struct memory_block* memory_block = first_memory_block; memory_block; memory_block = memory_block->next)
        if ((unsigned int)address >= (unsigned int)memory_block->data_pointer && (unsigned int)address <= (unsigned int)memory_block->data_pointer + memory_block_SIZE)
            if (old_size >= new_size) {
                for (memory_block_DATA_TYPE i = (unsigned int)address - (unsigned int)memory_block->data_pointer + old_size; i < memory_block->used; i++)
                    ((char*)memory_block->data_pointer)[i - old_size + new_size] = ((char*)memory_block->data_pointer)[i];
                for (memory_block_DATA_TYPE i = 0; i < old_size - new_size; i++)
                    ((char*)memory_block->data_pointer)[memory_block->used - i - 1] = 0;
                memory_block->used-=old_size - new_size;
                return address;
            } else {
                if (memory_block->used - old_size + new_size > memory_block_SIZE) {
                    address = allocate(new_size);
                    const memory_block_DATA_TYPE old_end = (unsigned int)address - (unsigned int)memory_block->data_pointer + old_size;
                    for (memory_block_DATA_TYPE i = old_end; i < memory_block->used; i++) {
                        ((char*)address)[i - old_end] = ((char*)memory_block->data_pointer)[i - old_size];
                        ((char*)memory_block->data_pointer)[i - old_size] = ((char*)memory_block->data_pointer)[i];
                    }
                    for (memory_block_DATA_TYPE i = 0; i < old_size; i++)
                        ((char*)memory_block->data_pointer)[memory_block->used - i - 1] = 0;
                    memory_block->used -= old_size;
                    return address;
                } else {
                    const memory_block_DATA_TYPE old_end = (unsigned int)address - (unsigned int)memory_block->data_pointer + old_size;
                    for (memory_block_DATA_TYPE i = old_end; i < memory_block->used; i++)
                        ((char*)memory_block->data_pointer)[i + new_size - old_size] = ((char*)memory_block->data_pointer)[i];
                    for (memory_block_DATA_TYPE i = 0; i < new_size - old_size; i++)
                        ((char*)memory_block->data_pointer)[old_end + i] = 0;
                    memory_block->used += new_size - old_size;
                    return address;
                }
            }
}