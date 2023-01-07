#pragma once

#define BLOCK_SIZE 0x100000

struct block {
	struct block *next;
	unsigned int top;
	unsigned int max;
	unsigned int size;
};

struct heap {
	struct block *first_block;
	unsigned int block_size;
};

struct heap heap;

void setup_heap() {
	heap.first_block = 0;
	heap.block_size = BLOCK_SIZE;
}

int add_block(struct heap *heap, unsigned int address, unsigned int size) {
	struct block *block;
	
	block = (struct block*)address;
	block->next = heap->first_block;
	heap->first_block = block;
	
	block->size = size;
	
	size = size - sizeof(struct block);
	
	block->max = size / (heap->block_size);
	
	const unsigned int stack = block->max * 4;
	const unsigned int slot = (stack / heap->block_size) * heap->block_size < stack ? (stack / heap->block_size) + 1 : stack / heap->block_size;
	
	block->top = slot;
	
	unsigned int* stack_pointer = (unsigned int*)&block[1];
	for (unsigned int x = slot; x < block->max; x++)
		stack_pointer[x] = x * heap->block_size;
		
	return 1;
}

void* allocate(unsigned int size) {
	struct block *block;
	
	if (size > heap.block_size)
		return 0;

    unsigned int pointer;
	unsigned int* stack_pointer;
	for (block = heap.first_block; block; block = block->next)
		if (block->top != block->max) {
			stack_pointer = (unsigned int*)&block[1];
			pointer = stack_pointer[block->top++];
			pointer = (unsigned int)&block[1] + pointer;
			return (void*)pointer;
		}

    return 0;
}

void deallocate(void* address) {
	struct block* block;
	
	for (block = heap.first_block; block; block = block->next)
		if (((unsigned int)address) > (unsigned int)block && ((unsigned int)address) < ((unsigned int)block + block->size))
			break;
	
	unsigned int* stack_pointer = (unsigned int*)&block[1];
	stack_pointer[block--->top] = ((unsigned int)address) - (unsigned int)&block[1];
	return;
}