#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Файлы заголовков/memory_area.h"
#include "../Файлы заголовков/mmemory.h"


LinkedList *memory_storage;


char* wrapper(int code) {
	if (code) return "wrong parameters";
	if (!code) return "success";
	if (code == -1) return "unknown error";
	if (code == -2) return "memory leak";
}


int _init(int n, int szPage) {
	if (n < 0 || szPage < 0) return -1;
	memory_storage = (LinkedList*)malloc(sizeof(LinkedList));
	if (memory_storage == NULL) return 1;
	int capacity = n * szPage;
	Node* head_node = init_node(capacity);
	memory_storage->size = capacity;
	memory_storage->head = head_node;
	return 0;
}

int _malloc(VA *ptr, size_t szBlock) {
	if (memory_storage == NULL) return 1;
	if (ptr == NULL) return -1;
	Node *iter_node = memory_storage->head;
	int i = 0;
	while (iter_node != NULL) {
		printf("\niteration %d", i);
		if (iter_node->value->empty) {
			if (iter_node->value->size == szBlock) {
				*ptr = iter_node->value->va;
				iter_node->value->empty = false;
				return 0;
			}
			if (iter_node->value->size > szBlock) {
				*ptr = iter_node->value->va;
				iter_node->value->size -= szBlock;
				MemoryBlock *block = create_memory_block(iter_node->value->va+szBlock, szBlock);
				insert(memory_storage, iter_node, iter_node->next, block);
				return 0;
			}
		}
		if (iter_node->next == NULL) return -2;
		i++;
		iter_node = iter_node->next;
	}
	return 1;
}

int _free(VA ptr) {
	if (memory_storage == NULL) return 1;
	if (ptr == NULL) return -1;
	Node *iter_node = memory_storage->head;
	while (iter_node != NULL) {
		if (iter_node->value->va == ptr) {
			if ((iter_node->prev != NULL) && (iter_node->prev->value->empty)) {
				iter_node->prev->value->size += iter_node->value->size;
				iter_node = iter_node->prev;
				delete_node(memory_storage, iter_node);
				free(ptr);
				return 0;
			}
			if ((iter_node->next != NULL)&&(iter_node->next->value->empty)) {
				iter_node->value->size += iter_node->next->value->size;
				delete_node(memory_storage, iter_node->next);
				free(ptr);
				return 0;
			}
			if (!iter_node->value->empty) {
				iter_node->value->empty = true;
				free(ptr);
				return 0;
			}
		}
		if (iter_node->next == NULL) return 1;
		iter_node = iter_node->next;
	}
}


int _read(VA ptr, void* pBuffer, size_t szBuffer) {
	if (memory_storage == NULL) return 1;
	if (ptr == NULL) return -1;
	Node *iter_node = memory_storage->head;
	while (iter_node != NULL) {
		if ((iter_node->value->va == ptr) && (!iter_node->value->empty)) {
			memcpy(pBuffer, ptr, szBuffer);
			return 0;
		}
		if (iter_node->next == NULL) return 1;
		iter_node = iter_node->next;
	}
	return 1;
}


int _write(VA ptr, void* pBuffer, size_t szBuffer) {
	if (memory_storage == NULL) return 1;
	if (ptr == NULL) return -1;
	Node* iter_node = memory_storage->head;
	while (iter_node != NULL) {
		if ((iter_node->value->va == ptr) && (!iter_node->value->empty)) {
			memcpy(ptr, pBuffer, szBuffer);
			return 0;
		}
		if (iter_node->next == NULL) return 1;
		iter_node = iter_node->next;
	}
	return 1;
}
