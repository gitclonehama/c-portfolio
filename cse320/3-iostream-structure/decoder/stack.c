#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/**
 * Push a value onto the stack.
 * This function allocates memory for the new node and copies the string value into it.
 */
void push(Stack *stack, const char *value) {
    // Allocate memory for the new node
    StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));
    if (!new_node) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Allocate memory for the value and copy the string
    new_node->value = (char *)malloc(strlen(value) + 1); // +1 for null terminator
    if (!new_node->value) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(new_node->value, value);  // Copy the value into the node

    // Set the new node's next pointer to the current head of the stack
    new_node->next = stack->head;

    // Make the new node the head of the stack
    stack->head = new_node;
}

/**
 * Free all memory associated with the stack.
 * This function frees both the nodes and the string values they hold.
 */
void free_stack(Stack *stack) {
    StackNode *current = stack->head;
    while (current != NULL) {
        StackNode *next = current->next;

        // Free the string stored in the current node
        free(current->value);

        // Free the node itself
        free(current);

        // Move to the next node
        current = next;
    }

    // Set the head to NULL after freeing everything
    stack->head = NULL;
}
