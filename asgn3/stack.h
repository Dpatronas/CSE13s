# ifndef __STACK_H__
# define __STACK_H__

# include <inttypes.h>
# include <stdbool.h>

//Struct definition for the stack

typedef struct Stack {
	int capacity;	//number of items the stack is holding
	int *items;		//array of what the stack item is holding
	int top;		//where our 'cursor' is
	char name;		//identifier character
}	Stack;

//Constructor to create the Stack s
	//pass capacity: The max number of items that Stack can hold
	//pass name: 	The Stack single char name to identify

	//each peg will be a stack with a capcacity and a name
Stack *stack(int capacity, char name);

//Prototype functions for our stack s
void s_push(Stack *s, int item);	//add item to stack
int s_pop(Stack *s);				//remove item from stack
bool s_empty(Stack *s);			//return status of stack contents (1 = empty)
int s_peek(Stack *s);			//return top value of stack without eliminating values
void s_delete(Stack *s);		//destructor for the stack

# endif
