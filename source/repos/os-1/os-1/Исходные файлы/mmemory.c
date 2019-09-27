//#include "pch.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "mmemory.h"
#include "memory_area.h"


LinkedList *memory_storage;


int _malloc(VA *ptr, size_t szBlock) {
	if (ptr == NULL) return -1;
	Node *iter_node = memory_storage->head;
	while (iter_node != NULL) {
		if (iter_node->value->empty) {
			if (iter_node->value->size == szBlock) {
				*ptr = iter_node->value->va;
				iter_node->value->empty = false;
				return 0;
			}
			if (iter_node->value->size > szBlock) {
				*ptr = iter_node->value->va;
				iter_node->value->size -= szBlock;
				MemoryBlock *block;
				block->size = szBlock;
				block->empty = false;
				// find new va
				Node *node = create_node(block);  // choose plase for new node
				return 0;
			}
		}
		if (iter_node->next == NULL) return -2;
		iter_node = iter_node->next;
	}
	return 1;
}

int _free(VA ptr) {
	if (ptr == NULL) return -1;
	Node *iter_node = memory_storage->head;
	while (iter_node != NULL) {
		if ((iter_node->value->va == ptr) && (!iter_node->value->empty)) {
			// ifs and deleting
			return 0;
		}
		if (iter_node->next == NULL) return 1;
		iter_node = iter_node->next;
	}
	return 1;
}
