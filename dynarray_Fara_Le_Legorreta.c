#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct student {
char* name;
int points;
};

struct dynArray {
void** data;
int size;
int capacity;
};



struct dynArray* D;

void add(int);
int get(int);
void set(int, int);
void insert(int, int);
void delete(int);
void init(int);
void cleanup();
void _resize(int);
void test();
void disp();


int main() {
	D = malloc(sizeof(struct dynArray));
	assert(D);
 	init(4);
	test();
	cleanup();
	disp();
	free(D);
	return 0;
}


void init(int c) {
	assert(c);
	D->capacity = c;
	D->size = 0;
	D->data = malloc(D->capacity * sizeof(int));
}


void cleanup() {
	assert(D->data);
	free(D->data);
	D->data = NULL;
	D->size = 0;
	D->capacity = 0;
}


int get(int index) {
	assert(index >= 0);
	assert(index < D->size);
	return D->data[index];
}


void set(int value, int index) {
	assert(index >= 0);
	assert(index < D->size);
	D->data[index] = value;
}


void delete(int index) {
	assert(index >= 0);
	assert(index < D->size);
	int i;
	for (i=index+1; i<D->size; i++) {
		D->data[i-1] = D->data[i];
	}
	D->size--;
}


void add(int value) {
	if (D->size == D->capacity) {
		_resize(D->capacity*2);
	}
	D->data[D->size] = value;
	D->size++;
}


void _resize(int c) {
	int i;
	int* newdata = malloc(c * sizeof(int));
	assert(newdata);
	D->capacity = c;
	for (i=0; i<D->size; i++) {
		newdata[i] = D->data[i];
	}
	free(D->data);
	D->data = newdata;
}


void insert(int value, int index) {
	assert(index >= 0);
	assert(index < D->size);
	int i;
	if (D->size == D->capacity) {
		_resize(D->capacity*2);
	}
	for (i=D->size; i>index; i--) {
		D->data[i] = D->data[i-1];
	}
	D->data[index] = value;
	D->size++;
}


void disp() {
	int i;
	for (i=0; i<D->size; i++) {
		printf("%d\t", D->data[i]);
	}
	printf("\n");
	printf("capacity = %d, size = %d\n", D->capacity, D->size);
}


void test() {
	disp();
	add(10); add(20); add(30); disp();
	add(40); disp();
	add(50); add(60);
	insert(15, 1); disp();
	insert(25, 3); disp();
	insert(35, 5); disp();
	add(70); disp();
	delete(0); disp();
}
