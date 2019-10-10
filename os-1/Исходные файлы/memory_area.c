#include "../Файлы заголовков/memory_area.h"
#include "../Файлы заголовков/mmemory.h"
#include "stdio.h"


Node* create_node(MemoryBlock* new_MemoryBlock, Node* prev, Node* next) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->value = new_MemoryBlock;
	new_node->prev = prev;
	new_node->next = next;
	return new_node;
}

void delete_node(LinkedList* linked_list, Node* element) {
	if (element->next != NULL) {
		element->prev->next = element->next;
	}
	if (element->prev != NULL) {
		element->next->prev = element->prev;
	}
	if (element->prev == NULL) {
		linked_list->head = element->next;
	}
	free(element);
}

MemoryBlock* create_memory_block(VA va, size_t size) {
	MemoryBlock* new_memory_block = (MemoryBlock*)malloc(sizeof(MemoryBlock));
	new_memory_block->va = va;
	new_memory_block->size = size;
	new_memory_block->empty = true;
	return new_memory_block;
}

Node* init_node(size_t size) {
	VA va = (VA)malloc(size * sizeof(VA));
	Node* node = create_node(create_memory_block(va, size), NULL, NULL);
	return node;
}

Node* get_node(LinkedList* linked_list, VA va) {
	Node* target_node = linked_list->head;
	while (target_node != NULL) {
		if (target_node->next->value = va) {
			return target_node;
		}
		target_node = target_node->next;
	}
	return NULL;
}

void insert(LinkedList* linked_list, Node* previous_node, Node* next_node, MemoryBlock* new_MemoryBlock) {
	Node* ins = (Node*)malloc(sizeof(Node));
	ins->value = new_MemoryBlock;
	ins->prev = previous_node;
	ins->next = next_node;

	if (previous_node == NULL) {
		linked_list->head = ins;
	}
	else {
		previous_node->next = ins;
		ins->prev = previous_node;
	}

	if (next_node != NULL) {
		next_node->prev = ins;
		ins->next = next_node;
	}
}
