#pragma once

/**
* Actual nodes in the stack
*/
typedef struct StackNode {
	char *value;
	struct StackNode *next;
} StackNode;

/**
* Structure representing the stack
*/
typedef struct {
	StackNode *head;  // Points to the top of the stack
} Stack;

/**
* Function declarations
*/
void push(Stack *stack, const char *value);  // Pushes a value onto the stack
void free_stack(Stack *stack);               // Frees all memory associated with the stack