#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


void xor_strings(char *result, const char *str1, const char *str2, size_t len);
void rotate_left(char *str, int n, size_t len);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: decoder file\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Unable to open input file\n");
        return 1;
    }

    // Read the key (first line)
    char *key = NULL;
    size_t key_length = 0;
    ssize_t read_len = getline(&key, &key_length, fp);  // Read the key line dynamically
    if (read_len == -1) {
        printf("Failed to read key line\n");
        fclose(fp);
        return 1;
    }
    key[strcspn(key, "\r\n")] = 0;  // Remove newline
    key_length = strlen(key);  // Update key length after removing newlines

    // Initialize the stack directly
    Stack stack = {NULL};

    // Process each line
    char *line = NULL;
    size_t line_length = 0;
    int line_number = 0;

    while (getline(&line, &line_length, fp) != -1) {
        line[strcspn(line, "\r\n")] = 0;  // Remove newline

        // Allocate memory for the decoded line
        char *decoded_line = malloc(key_length + 1);
        if (!decoded_line) {
            printf("Memory allocation failed\n");
            fclose(fp);
            free_stack(&stack);
            free(key);
            return 1;
        }

        // XOR the line with the key and rotate left
        xor_strings(decoded_line, line, key, key_length);
        rotate_left(decoded_line, line_number, key_length);

        // Push the decoded line onto the stack
        push(&stack, decoded_line);

        // Free the decoded line
        free(decoded_line);

        line_number++;
    }

    // Close the file and free the line memory
    fclose(fp);
    free(line);

    // Print the decoded stack (top of the stack first)
    StackNode *node = stack.head;
    while (node != NULL) {
        for (char *p = node->value; *p; p++) {
            putchar((*p == '1') ? 'X' : ' ');
        }
        putchar('\n');
        node = node->next;
    }

    // Free the stack and key
    free_stack(&stack);
    free(key);

    return 0;
}

// XOR two strings and store the result in `result`
void xor_strings(char *result, const char *str1, const char *str2, size_t len) {
    for (size_t i = 0; i < len; i++) {
        result[i] = (str1[i] == str2[i]) ? '0' : '1';
    }
    result[len] = '\0';
}

// Rotate a string left by `n` positions
void rotate_left(char *str, int n, size_t len) {
    n = n % len;  // Ensure `n` is within bounds
    if (n == 0) return;

    char *temp = malloc(len + 1);
    strncpy(temp, str + n, len - n);    // Copy substring from n to the end
    strncpy(temp + len - n, str, n);    // Copy the first n characters to the end
    temp[len] = '\0';

    strcpy(str, temp);
    free(temp); // Freeing the memmory after we are fully done with it
}