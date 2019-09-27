#include "memory_area.h"
#include "mmemory.h"
#include "stdio.h"


Node* create_node(MemoryBlock* new_memory_block, Node* prev, Node* next) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->value = new_memory_block;
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
