#include <stdbool.h>
#include "mmemory.h"


typedef struct Memory_block {
	VA va;
	size_t size;
	bool isEmpty;
} Memory_block;

typedef struct Node {
	Memory_block* value;
	struct Node* next;
	struct Node* previous;
} Node;

typedef struct Linked_list {
	size_t size;
	Node* head;
} Linked_list;




