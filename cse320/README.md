# CSE 320 - Computer Systems Programming

This directory contains projects from CSE 320, focusing on systems programming, Unix/Linux development, memory management, and low-level programming concepts in C and assembly language.

## Course Overview

CSE 320 introduces fundamental concepts in systems programming including:
- Unix/Linux system programming
- Memory management and pointer manipulation
- String processing and data encoding
- Assembly language programming (ARM)
- Debugging techniques and tools
- I/O operations and file handling
- Data structures implementation
- Graphics and image processing

## Project Directory

### [1. Unix, Vim, and C Numbers](./1-unix-vim-cnumbers/)
**Skills:** Unix fundamentals, number systems, basic C programming

Projects introducing Unix command line, Vim editor, and number system conversions.

- **bin2oct** - Binary to octal converter with custom Y/N encoding
- **lunar-lander** - Simple game demonstrating control structures

### [2. Memory and String Processing](./2-memory-string/)
**Skills:** Memory management, string manipulation, algorithm implementation

Advanced string processing and memory manipulation techniques.

- **decoder** - Sophisticated bit manipulation for decoding encrypted data streams

### [3. I/O Streams and Data Structures](./3-iostream-structure/)
**Skills:** File I/O, stack implementation, data structure design

Implementation of fundamental data structures and file processing.

- **decoder** - Enhanced decoder with file I/O capabilities
- **stack** - Custom stack implementation for data processing

### [4. Assembly Language Introduction](./4-assembly-intro/)
**Skills:** ARM assembly, low-level programming, function calls

Introduction to ARM assembly language programming.

- **firstasm** - Basic assembly functions and arithmetic operations

### [5. Assembly Programming Practice](./5-assembly-practice/)
**Skills:** Advanced assembly, algorithms, optimization

Complex algorithm implementation in assembly language.

- **life** - Conway's Game of Life implementation
- **sieve** - Sieve of Eratosthenes algorithm

### [6. Debugging, Instructions, and Stack Frames](./6-debugging-instructions-stackframes/)
**Skills:** Debugging techniques, stack analysis, program tracing

Advanced debugging concepts and stack frame analysis.

- **armstrong** - Armstrong number detection
- **digitcounter** - Digit counting algorithms
- **gcd** - Greatest common divisor implementation
- **sorthex** - Hexadecimal sorting with debugging features

### [7. Floating-Point Programming](./7-floating-point/)
**Skills:** Floating-point arithmetic, graphics programming, mathematical algorithms

Graphics and mathematical programming with floating-point operations.

- **bezier** - Bézier curve calculations
- **ship** - Graphics rendering and image manipulation

### [8. Arrays and Structures](./8-arrays-structures/)
**Skills:** Complex data structures, image processing, algorithm optimization

Advanced data structure implementations and image processing algorithms.

- **blocky** - Image processing and pixel manipulation
- **tictac** - Tic-tac-toe game with complex game state management

## Key Learning Outcomes

### Technical Skills Developed
- **Memory Management** - Manual memory allocation, pointer arithmetic, memory safety
- **Assembly Programming** - ARM instruction set, registers, stack operations
- **System Programming** - Unix system calls, file operations, process management
- **Data Structures** - Implementation of stacks, arrays, and custom structures
- **Algorithm Implementation** - Translation of high-level algorithms to low-level code
- **Debugging Proficiency** - Use of GDB, understanding stack traces, memory debugging

### Programming Concepts Mastered
- Pointer manipulation and memory addressing
- Bit-level operations and data encoding
- Function calling conventions and stack frames
- I/O operations and file handling
- Graphics programming and image processing
- Game logic and state management
- Mathematical algorithm implementation

## Development Environment

- **Language:** C, ARM Assembly
- **Compiler:** GCC with various optimization flags
- **Debugger:** GDB for debugging and analysis
- **Build System:** Make with custom Makefiles
- **Platform:** Linux/Unix systems
- **Editor:** Vim with system programming configurations

## Project Structure

Each project follows a consistent structure:
```
project-name/
├── Makefile          # Build configuration
├── main.c            # Main program entry point
├── [module].c        # Implementation files
├── [module].h        # Header files
├── [module].S        # Assembly source files (where applicable)
├── test-files/       # Test inputs and expected outputs
└── README.md         # Project-specific documentation
```

## Getting Started

To build and run any project:

```bash
cd [project-directory]
make clean && make
./<executable-name>
```

For debugging:
```bash
make debug
gdb ./<executable-name>
```

## Notable Implementation Details

- **Custom Memory Management** - All projects implement careful memory allocation and deallocation
- **Error Handling** - Robust error checking and graceful failure handling
- **Performance Optimization** - Assembly code optimized for performance and memory usage
- **Code Documentation** - Comprehensive comments explaining algorithms and design decisions
- **Testing Framework** - Each project includes test cases and validation

---

*These projects demonstrate progression from basic C programming to advanced systems programming and assembly language implementation.*
