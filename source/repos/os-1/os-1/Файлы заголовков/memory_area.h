#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "mmemory.h"


typedef struct MemoryBlock {
	VA va;
	size_t size;
	bool empty;
} MemoryBlock;

typedef struct Node {
	MemoryBlock* value;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct LinkedList {
	size_t size;
	Node* head;
} LinkedList;

MemoryBlock* create_memory_block(VA va, size_t size);
Node* init_node(size_t size);
Node* create_node(MemoryBlock* new_memory_block, Node* previous, Node* next);
void insert(LinkedList* linked_list, Node* previous_node, Node* next_node, MemoryBlock* new_memory_block);
void delete_node(LinkedList* linked_list, Node* element);
Node* get_node(LinkedList* linked_list, VA va);

