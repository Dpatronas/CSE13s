#include <stdlib.h>
#include "stack.h"

//constructor creates a new stack of type Stack
Stack *stack ( int size, char character) {
	//instantiate
	Stack *s = (Stack *)malloc(sizeof(Stack));
	//if insantiation was unsuccessful
	if(!s) {
		return 0;
	}
	//start at 1
	if (size < 1) {
		size = 1;
	}
	//set fields based on inputed function parameters
	s->capacity = size;
	s->name = character;

	//allocate space on the heap
	s-> items = (int *) malloc(sizeof(int) * size);
	//if items failed to create
	if (!s->items) {
		return exit(0);
	}
	return s;
}

//pushes an item onto the stack
void s_push(Stack *s, int item) {
	//check if the stack in question exists
	if (!s) {
		return;
	}
	//check if said stack is full
	//if the top of the existing stack is the capacity
	//double the stck size as needed
	if (s->top == s->capacity - 1) {
		s->capacity *= 2;
		//new *items = casted void pointer reallocating memory for new array double the size
		s->items = (int *)realloc(s->items, s->capacity * sizeof(int));
	}
	//if we have successful
	if(s->items) {
		//put the new item on top
		s->items[s->top] = item;
		//adjust the top
		s->top ++;
	}
	return;
}

int s_pop(Stack *s) {
	if (!s) {
		return - 1;
	}
	//as long as there is something in the stack
	if ( s->top > 0 ) {
		//decremenet the top of stack element
		s->top --;
		//return the item at the top of the stack
		return s->items[s->top];
	}
	//otherwise stack is empty and cannot be popped
	else {
		return -1;
	}
}

bool s_empty(Stack *s) {
	//if empty returns true
	return s->top == 0;
}

int s_peek(Stack *s) {
	//can error check for empty possibly
	if ( !s ) {
		return -1;
	}
	else {   //return items[element top - 1 ] because top starts at 1 and elements start at 0
		return s->items[s->top-1];
	}
}

void s_delete(Stack *s) {
	//remove the pointer to items
	free(s->items);
	//remove the stack itself
	free(s);
	return;
}
