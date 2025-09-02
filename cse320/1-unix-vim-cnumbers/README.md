# Unix, Vim, and C Numbers

Introduction to Unix/Linux systems programming, Vim editor, and number system conversions in C.

## Project Overview

This assignment introduces fundamental concepts in systems programming including Unix command-line tools, the Vim text editor, and number system conversions. Projects focus on basic C programming with emphasis on character processing and mathematical algorithms.

## Projects

### bin2oct - Binary to Octal Converter

**Objective:** Convert a custom binary representation to octal using character encoding.

**Key Features:**
- Custom binary encoding using 'Y' (1) and 'N' (0) characters
- Robust input validation and error handling
- Efficient algorithm for base conversion
- Handles unexpected characters gracefully

**Algorithm:**
1. Parse input string character by character
2. Convert Y/N representation to binary value
3. Transform binary to octal representation
4. Return unsigned integer result

**Technical Implementation:**
```c
// Core conversion logic
for ( ; *binary; binary++) {
    if (*binary == 'Y') {
        binary_value = binary_value * 2 + 1;
    }
    else if (*binary == 'N') {
        binary_value = binary_value * 2;
    }
    else if (*binary == ' ') {
        break;	
    }
}
```

**Input Examples:**
- `YYNY` → Binary: 1101 → Decimal: 13 → Octal: 15
- `aYNcY YY` → Processes: YNY → Binary: 101 → Decimal: 5 → Octal: 5

### lunar-lander - Simple Game Logic

**Objective:** Implement basic game mechanics demonstrating control structures and user interaction.

**Key Features:**
- User input processing
- Game state management
- Simple physics simulation
- Victory/failure condition checking

## Learning Outcomes

### Technical Skills
- **C Programming Fundamentals** - Variables, functions, control structures
- **String Processing** - Character-by-character parsing and validation
- **Number Systems** - Binary, decimal, and octal conversions
- **Algorithm Design** - Efficient conversion algorithms
- **Input Validation** - Robust error handling for user input

### Unix/Linux Skills
- **Command Line Proficiency** - Navigation, file operations, process management
- **Vim Editor** - Efficient text editing and code development
- **Build Systems** - Using Make for compilation and project management
- **Development Workflow** - Unix-based software development practices

### Programming Concepts
- Pointer arithmetic and string manipulation
- Mathematical algorithm implementation
- Error handling and edge case management
- Code organization and modular design
- Testing and validation strategies

## Build Instructions

```bash
# Build bin2oct
cd bin2oct/
make
./bin2oct

# Build lunar-lander
cd lunar-lander/
make
./lunar-lander
```

## Usage Examples

### bin2oct Usage
```bash
# Interactive mode
./bin2oct
Enter binary string: YYNNY
Result: 6

# Test cases
YYNY        → 15
NYNYny      → 5 (stops at invalid character)
aYNcY YY    → 5 (ignores invalid chars, stops at space)
```

## File Structure

```
1-unix-vim-cnumbers/
├── bin2oct/
│   ├── bin2oct.c       # Core conversion algorithm
│   ├── bin2oct.h       # Function declarations
│   ├── main.c          # Main program and user interface
│   └── Makefile        # Build configuration
└── lunar-lander/
    ├── lunar-lander.c  # Game implementation
    └── Makefile        # Build configuration
```

## Key Implementation Details

### Error Handling
- Graceful handling of invalid characters
- Proper termination on space characters
- Robust input validation

### Algorithm Efficiency
- Single-pass string processing
- Minimal memory usage
- Optimized mathematical operations

### Code Quality
- Clear variable naming and comments
- Modular function design
- Comprehensive test coverage

## Testing Strategy

### bin2oct Testing
- Valid Y/N sequences
- Mixed valid/invalid characters
- Edge cases (empty string, all invalid chars)
- Boundary conditions (maximum values)

### Validation Approach
- Manual calculation verification
- Automated test cases
- Edge case analysis
- Performance testing with large inputs

## Educational Value

This project provides foundation in:
- **Systems Programming** - Understanding how software interacts with the operating system
- **C Language Mastery** - Core programming concepts and best practices
- **Algorithm Development** - Designing efficient solutions to computational problems
- **Unix Development** - Professional software development workflow
- **Problem Solving** - Breaking down complex problems into manageable components

---

*This assignment establishes the fundamental skills necessary for advanced systems programming and serves as a stepping stone to more complex projects involving memory management, assembly language, and advanced algorithms.*
