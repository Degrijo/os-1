#include <stdio.h>
#include <assert.h>
#include "../Файлы заголовков/mmemory.h"


void wrapper(int code, int waiting_code) {
	if (code == 0) puts("- Success work");
	else if (code == 1) puts("- Unknown error");
	else if (code == -1) puts("- Wrong parameters");
	else if (code == -2) puts("- Memory leak");
	assert(code == waiting_code);
}


void init_case0() {
	int page_number = 3;
	size_t page_size = 10;
	puts("Success initialization");
	wrapper(_init(page_number, page_size), 0);
}

void init_case_1() {
	int page_number = -3;
	size_t page_size = -10;
	puts("Initialization with wrong parameters");
	wrapper(_init(page_number, page_size), -1);
}

void malloc_case0() {
	int page_number = 3;
	size_t page_size = 10;
	VA ptr;
	size_t bfsize = 5;
	puts("Success malloc");
	_init(page_number, page_size);
	wrapper(_malloc(&ptr, bfsize), 0);
}

void malloc_case_1() {
	int page_number = 3;
	size_t page_size = 10;
	VA ptr = NULL;
	size_t bfsize = 5;
	puts("Malloc with wrong parameters");
	_init(page_number, page_size);
	wrapper(_malloc(&ptr, bfsize), -1);
}

void malloc_case_2() {
	int page_number = 3;
	size_t page_size = 10;
	VA ptr;
	size_t bfsize = 31;
	puts("Malloc with memory leak");
	_init(page_number, page_size);
	wrapper(_malloc(&ptr, bfsize), -2);
}

void read_case0() {
	int page_number = 3;
	size_t page_size = 10;
	VA ptr;
	char* buf_ptr_write = "aysd";
	char* buf_ptr_read = (char*)malloc(sizeof(buf_ptr_write));
	size_t bfsize = 5;
	puts("Success read");
	_init(page_number, page_size);
	_malloc(&ptr, bfsize);
	_write(ptr + bfsize, buf_ptr_write, sizeof(buf_ptr_write));
	wrapper(_read(ptr + bfsize, buf_ptr_read, sizeof(buf_ptr_read)), 0);
}

void read_case_1() {
	int page_number = 3;
	size_t page_size = 10;
	VA ptr = NULL;
	char* buf_ptr_write = "aysd";
	char* buf_ptr_read = (char*)malloc(sizeof(buf_ptr_write));
	size_t bfsize = 5;
	puts("Read with wrong parameters");
	_init(page_number, page_size);
	_malloc(&ptr, bfsize);
	_write(ptr + sizeof(buf_ptr_write), buf_ptr_write, sizeof(buf_ptr_write));
	wrapper(_read(ptr, buf_ptr_read, sizeof(buf_ptr_write)), -1);
}

void read_case_2() {
	int page_number = 3;
	size_t page_size = 10;
	VA ptr;
	char* buf_ptr_write = "aysd";
	char* buf_ptr_read = (char*)malloc(sizeof(buf_ptr_write));
	size_t bfsize = 5;
	puts("Read with memory exit");
	_init(page_number, page_size);
	_malloc(&ptr, bfsize);
	_write(ptr + sizeof(buf_ptr_write), buf_ptr_write, sizeof(buf_ptr_write));
	wrapper(_read(ptr, buf_ptr_read, sizeof(buf_ptr_write)), -2);
}

void write_case0() {
	int page_number = 3;
	size_t page_size = 10;
	VA ptr;
	char* buf_ptr_write = "aysd";
	size_t bfsize = 5;
	puts("Success write");
	_init(page_number, page_size);
	_malloc(&ptr, bfsize);
	wrapper(_write(ptr + bfsize, buf_ptr_write, sizeof(buf_ptr_write)), 0);
}

void write_case_1() {
	int page_number = 3;
	size_t page_size = 10;
	VA ptr = NULL;
	char* buf_ptr_write = "aysd";
	size_t bfsize = 5;
	puts("Write with wrong parameters");
	_init(page_number, page_size);
	_malloc(&ptr, bfsize);
	wrapper(_write(ptr, buf_ptr_write, sizeof(buf_ptr_write)), -1);
}

void write_case_2() {
	int page_number = 3;
	size_t page_size = 10;
	VA ptr;
	char* buf_ptr_write = "aysd";
	size_t bfsize = 5;
	puts("Write with memory exit");
	_init(page_number, page_size);
	_malloc(&ptr, bfsize);
	wrapper(_write(ptr, buf_ptr_write, sizeof(buf_ptr_write)), -2);
}

void free_case0() {
	int page_number = 3;
	size_t page_size = 10;
	VA ptr1, ptr2, ptr3;
	size_t bfsize = 5;
	puts("Success free");
	_init(page_number, page_size);
	_malloc(&ptr1, bfsize);
	_malloc(&ptr2, bfsize);
	_malloc(&ptr3, bfsize);
	wrapper(_free(ptr1 + bfsize), 0);
}

void free_case_1() {
	int page_number = 3;
	size_t page_size = 10;
	VA ptr = NULL;
	size_t bfsize = 5;
	puts("Free with wrong parameters");
	_init(page_number, page_size);
	_malloc(&ptr, bfsize);
	wrapper(_free(ptr + bfsize), -1);
}

int main() {
	init_case0();
	init_case_1();
	malloc_case0();
	malloc_case_1();
	malloc_case_2();
	write_case0();
	write_case_1();
	write_case_2();
	//read_case0();
	read_case_1();
	read_case_2();
	free_case0();
	free_case_1();
	puts("\nPress any key to quit:");
	getchar();
	return 0;
}