#include "memory_area.h"
#include "mmemory.h"
#include "stdio.h"


Node* create_node(MemoryBlock* new_memory_block, Node* previous, Node* next) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->value = new_memory_block;
	new_node->previous = previous;
	new_node->next = next;
	return new_node;
}

void delete_node(LinkedList* linked_list, Node* element) {
	if (element->next != NULL) {
		element->previous->next = element->next;
	}
	if (element->previous != NULL) {
		element->next->previous = element->previous;
	}
	if (element->previous == NULL) {
		linked_list->head = element->next;
	}
	free(element);
}
