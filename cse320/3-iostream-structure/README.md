# I/O Streams and Data Structures

Introduction to file I/O operations and basic data structure implementation in C, focusing on encrypted file processing and stack operations.

## Project Overview

This project introduces file input/output operations and implements a basic stack data structure. Students learn to read encrypted files, perform string manipulation operations, and manage dynamic memory in a linked list structure.

## decoder - Encrypted File Processor

**Objective:** Read encrypted files, decode their contents using XOR and rotation operations, and display the results using a stack data structure.

### Key Features

- **File Reading** - Process encrypted text files with key-based decoding
- **String Operations** - XOR encryption and left rotation of character strings
- **Stack Storage** - Store decoded lines in a linked list stack
- **Memory Management** - Dynamic allocation and cleanup of string data

### File Format

Encrypted files contain:
- **First line:** Encryption key (string)
- **Subsequent lines:** Encrypted data to be decoded

### Processing Algorithm

```c
// Main decoding process
int main(int argc, char *argv[]) {
    // Read key from first line of file
    char *key = read_key_from_file(argv[1]);
    
    // Initialize stack
    Stack stack = {NULL};
    
    // Process each data line
    int line_number = 0;
    while (read_next_line(file, line)) {
        // XOR line with key
        char *xored = xor_strings(line, key, key_length);
        
        // Rotate left by line number
        rotate_left(xored, line_number, key_length);
        
        // Push to stack
        push(&stack, xored);
        
        line_number++;
    }
    
    // Display results (stack contents)
    print_stack(&stack);
    
    // Cleanup
    free_stack(&stack);
}
```

### String Operations

#### XOR Operation
```c
void xor_strings(char *result, const char *str1, const char *str2, size_t len) {
    for (size_t i = 0; i < len; i++) {
        result[i] = (str1[i] == str2[i]) ? '0' : '1';
    }
}
```

#### Left Rotation
```c
void rotate_left(char *str, int n, size_t len) {
    n = n % len;  // Handle rotations larger than string length
    if (n == 0) return;
    
    // Create temporary buffer for rotation
    char *temp = malloc(len + 1);
    strncpy(temp, str + n, len - n);      // Copy from rotation point to end
    strncpy(temp + len - n, str, n);      // Copy beginning to end
    strcpy(str, temp);
    free(temp);
}
```

## stack - Linked List Stack Implementation

**Objective:** Implement a basic stack data structure using a singly-linked list for storing decoded strings.

### Stack Structure

```c
typedef struct StackNode {
    char *value;           // String data stored in node
    struct StackNode *next; // Pointer to next node
} StackNode;

typedef struct {
    StackNode *head;       // Top of stack (most recently pushed)
} Stack;
```

### Stack Operations

#### Push Operation
```c
void push(Stack *stack, const char *value) {
    // Allocate new node
    StackNode *new_node = malloc(sizeof(StackNode));
    
    // Copy string value
    new_node->value = malloc(strlen(value) + 1);
    strcpy(new_node->value, value);
    
    // Link to existing stack
    new_node->next = stack->head;
    stack->head = new_node;
}
```

#### Memory Cleanup
```c
void free_stack(Stack *stack) {
    StackNode *current = stack->head;
    while (current != NULL) {
        StackNode *next = current->next;
        free(current->value);  // Free string data
        free(current);         // Free node
        current = next;
    }
    stack->head = NULL;
}
```

### Stack Properties

- **LIFO Structure** - Last In, First Out ordering
- **Dynamic Sizing** - Grows as needed (no fixed capacity)
- **String Storage** - Each node contains a dynamically allocated string
- **Memory Management** - Manual allocation and deallocation required

## Learning Outcomes

### File I/O Operations
- **File Opening/Closing** - Proper file handle management
- **Line Reading** - Using getline() for dynamic line reading
- **Error Handling** - Checking file operations for success/failure
- **Resource Cleanup** - Proper file closure and memory deallocation

### String Manipulation
- **XOR Operations** - Bitwise string comparison and encryption
- **Rotation Algorithms** - Circular shifting of character arrays
- **Memory Allocation** - Dynamic string buffer management
- **Null Termination** - Proper string handling and termination

### Data Structures
- **Linked Lists** - Implementation of singly-linked list structure
- **Stack Operations** - Push and memory cleanup operations
- **Pointer Management** - Handling pointers to dynamically allocated memory
- **Memory Safety** - Preventing leaks and access violations

### C Programming Techniques
- **Dynamic Memory** - malloc/free for variable-sized data
- **String Functions** - strcpy, strlen, and related operations
- **Struct Usage** - Defining and using custom data structures
- **Function Organization** - Separating concerns into logical functions

## File Structure

```
3-iostream-structure/
└── decoder/
    ├── apple.enc           # Sample encrypted file
    ├── bird.enc           # Sample encrypted file
    ├── cat.enc            # Sample encrypted file
    ├── secret1.enc        # Encrypted mystery file
    ├── secret2.enc        # Encrypted mystery file
    ├── secret3.enc        # Encrypted mystery file
    ├── secret4.enc        # Encrypted mystery file
    ├── secret5.enc        # Encrypted mystery file
    ├── main.c             # Main program with file processing
    ├── stack.c            # Stack implementation
    ├── stack.h            # Stack declarations
    └── Makefile           # Build configuration
```

## Build and Usage

### Compilation
```bash
cd decoder/
make
./decoder <encrypted_file>
```

### Example Usage
```bash
# Process an encrypted file
./decoder apple.enc

# The program will:
# 1. Read the encryption key from first line
# 2. Decode each subsequent line using XOR + rotation
# 3. Store decoded lines on stack
# 4. Display results as ASCII art (X characters)
```

### Sample Output
```
# Decoded content displayed as:
# X   X
#  X X
#   X
#  X X
# X   X
```

## Implementation Details

### File Processing Flow
1. **Open File** - Check file exists and can be opened
2. **Read Key** - Extract encryption key from first line
3. **Process Lines** - For each data line:
   - XOR with key
   - Rotate left by line number
   - Push result to stack
4. **Display Results** - Print stack contents (LIFO order)
5. **Cleanup** - Free all allocated memory

### Memory Management
- **Dynamic Allocation** - Strings and nodes allocated as needed
- **Proper Cleanup** - All memory freed to prevent leaks
- **Error Handling** - Allocation failure detection and recovery
- **Resource Tracking** - Careful management of file handles and pointers

## Testing Approach

### File Processing Tests
- **Valid Files** - Properly formatted encrypted files
- **Invalid Files** - Missing files, permission errors
- **Empty Files** - Files with no data lines
- **Malformed Data** - Incorrect line formats

### Stack Operation Tests
- **Push Operations** - Adding multiple strings to stack
- **Memory Cleanup** - Verifying no memory leaks
- **Large Datasets** - Processing many lines efficiently
- **Edge Cases** - Empty strings, very long strings

## Educational Value

This project teaches:
- **File I/O Programming** - Reading and processing text files
- **String Algorithms** - Basic encryption and manipulation techniques
- **Data Structure Implementation** - Building linked list structures
- **Memory Management** - Dynamic allocation and cleanup patterns
- **Program Organization** - Structuring code into logical components

---

*This project provides hands-on experience with fundamental programming concepts including file operations, string processing, and basic data structure implementation.*
