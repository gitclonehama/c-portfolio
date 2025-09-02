# Assembly Language Introduction

Introduction to ARM assembly language programming, covering fundamental concepts of low-level programming, processor architecture, and assembly language syntax.

## Project Overview

This project introduces ARM assembly language programming through implementation of basic mathematical functions and algorithms. Students learn processor architecture, instruction sets, register usage, and calling conventions while implementing practical functions in assembly.

## firstasm - Basic Assembly Functions

**Objective:** Implement fundamental arithmetic operations and algorithms in ARM assembly language.

### Implemented Functions

#### `first` - Triple Value Function
**Purpose:** Multiply input value by 3 using addition operations

**Algorithm:**
```assembly
first:
    mov x1, x0      // Copy input to x1
    add x0, x0, x1  // x0 = x0 + x1 (2 * input)
    add x0, x0, x1  // x0 = x0 + x1 (3 * input)
    ret             // Return result in x0
```

**Key Concepts:**
- Register allocation and management
- Arithmetic operations in assembly
- Function calling conventions
- Return value handling

#### `second` - Subtraction Function
**Purpose:** Subtract second parameter from first parameter

**Algorithm:**
```assembly
second:
    sub x0, x0, x1  // x0 = x0 - x1
    ret             // Return result in x0
```

**Key Concepts:**
- Parameter passing in registers
- Subtraction operations
- Simple function structure

#### `min` - Minimum Value Function
**Purpose:** Determine minimum of two input values using conditional branching

**Algorithm:**
```assembly
min:
    subs x2, x0, x1     // x2 = x0 - x1, set flags
    bge b_is_minimum    // Branch if x0 >= x1
    
    // x0 is minimum (already in x0)
    mov x0, x0          // Keep x0 unchanged
    b after_block       // Jump to end
    
b_is_minimum:
    // x1 is minimum
    mov x0, x1          // Move x1 to x0 (return register)
    b after_block       // Jump to end
    
after_block:
    ret                 // Return minimum value in x0
```

**Key Concepts:**
- Conditional execution and branching
- Flag setting with SUBS instruction
- Branch prediction and control flow
- Structured programming in assembly

## Learning Outcomes

### ARM Assembly Language Mastery
- **Instruction Set Architecture** - Understanding ARM64 instructions and encoding
- **Register Usage** - Efficient allocation and management of processor registers
- **Calling Conventions** - Parameter passing and return value handling
- **Control Flow** - Branching, loops, and conditional execution
- **Memory Operations** - Load and store instructions for data access

### Low-Level Programming Concepts
- **Processor Architecture** - CPU registers, ALU operations, and instruction pipeline
- **Machine Code Translation** - Understanding how high-level code becomes machine instructions
- **Performance Optimization** - Writing efficient assembly for maximum performance
- **Debugging Assembly** - Using debuggers and understanding assembly execution
- **System Interface** - How assembly interacts with operating system and hardware

### Programming Fundamentals
- **Algorithm Implementation** - Translating algorithms to low-level instructions
- **Function Design** - Creating reusable assembly functions with proper interfaces
- **Error Handling** - Managing edge cases and invalid inputs at assembly level
- **Code Organization** - Structuring assembly programs for maintainability

## Build Instructions

```bash
cd firstasm/
make
./firstasm
```

### Makefile Configuration
```makefile
# Example Makefile structure
CC = gcc
CFLAGS = -g -Wall
ASFLAGS = -g

firstasm: main.o first.o
    $(CC) -o firstasm main.o first.o

main.o: main.c
    $(CC) $(CFLAGS) -c main.c

first.o: first.S
    $(CC) $(ASFLAGS) -c first.S

clean:
    rm -f *.o firstasm
```

## Testing and Validation

### Test Cases for `first` Function
```c
// Test tripling functionality
assert(first(5) == 15);   // 5 * 3 = 15
assert(first(0) == 0);    // 0 * 3 = 0
assert(first(-3) == -9);  // -3 * 3 = -9
```

### Test Cases for `min` Function
```c
// Test minimum selection
assert(min(5, 3) == 3);   // min(5,3) = 3
assert(min(1, 1) == 1);   // min(1,1) = 1
assert(min(-2, 4) == -2); // min(-2,4) = -2
```

## File Structure

```
4-assembly-intro/
└── firstasm/
    ├── first.S         # Assembly function implementations
    ├── main.c          # C test harness and function calls
    └── Makefile        # Build configuration
```

## Assembly Programming Concepts

### Register Usage Conventions
- **x0, x1** - First two parameters and return value
- **x2-x7** - Additional parameters and temporary values
- **x8-x18** - Temporary registers (caller-saved)
- **x19-x28** - Callee-saved registers
- **x29** - Frame pointer
- **x30** - Link register (return address)

### Instruction Categories
- **Data Processing** - ADD, SUB, MOV operations
- **Comparison** - SUBS with flag setting
- **Branch** - B, BGE conditional and unconditional jumps
- **Function Control** - RET for function returns

### Assembly Best Practices
- **Clear Comments** - Document purpose and register usage
- **Proper Labels** - Meaningful names for branch targets
- **Consistent Style** - Uniform indentation and formatting
- **Error Handling** - Consider edge cases and invalid inputs

## Performance Considerations

### Optimization Techniques
- **Register Allocation** - Minimize memory access by keeping values in registers
- **Instruction Selection** - Choose most efficient instructions for operations
- **Branch Prediction** - Structure conditional code for optimal prediction
- **Pipeline Efficiency** - Avoid data hazards and instruction dependencies

### Benchmarking Results
- **Cycle Count** - Analysis of instruction execution cycles
- **Memory Access** - Minimizing load/store operations
- **Code Size** - Compact implementation without sacrificing readability

## Educational Value

This project establishes foundation in:
- **Computer Architecture** - Deep understanding of processor design and operation
- **Systems Programming** - Knowledge of how software interfaces with hardware
- **Performance Engineering** - Skills in writing efficient, optimized code
- **Low-Level Debugging** - Ability to debug and analyze assembly code
- **Cross-Language Programming** - Integration of assembly with higher-level languages

### Real-World Applications
- **Embedded Systems** - Direct hardware control and optimization
- **Operating Systems** - Kernel-level programming and system calls
- **High-Performance Computing** - Critical path optimization in computational algorithms
- **Reverse Engineering** - Understanding and analyzing compiled code

---

*This introduction to assembly language programming provides essential skills for systems programming, embedded development, and performance-critical applications while building a deep understanding of computer architecture.*
