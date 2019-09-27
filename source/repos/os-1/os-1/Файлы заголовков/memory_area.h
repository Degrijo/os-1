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
