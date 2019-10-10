#include <stdio.h>
#include "../Файлы заголовков/mmemory.h"


int main() {
	VA ptr1, ptr2, ptr3;
	void* bf = NULL;
	size_t bfsize = 5;
	int page_number = 3;
	size_t page_size = 4;
	_malloc(&ptr1, bfsize);
	_malloc(&ptr2, bfsize);
	_malloc(&ptr3, bfsize);
	_write(ptr1, bf, bfsize);
	_read(ptr1, bf, bfsize);
	_free(&ptr2);
	puts("\nPress any key to quit:");
	getchar();
	return 0;
}