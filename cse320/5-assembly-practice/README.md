# Assembly Programming Practice

Introduction to ARM assembly language programming through implementation of basic algorithms and bit manipulation operations.

## Project Overview

This project provides practice with ARM assembly language by implementing fundamental programming concepts including bit operations, command-line argument processing, and basic algorithm structures.

## Projects

### Conway's Game of Life (`life/`)

**Objective:** Implement basic bit manipulation operations for cellular automaton simulation.

**Current Implementation:**
- **`life.S`** - Bit copying and manipulation operations
- **`get_bit.S`** - Extract individual bit values from bit arrays
- **`set_bit.S`** - Set individual bit values in bit arrays
- **`main.c`** - C test harness for assembly functions
- **`tests.c`** - Basic functionality testing

**Key Features:**
- Bit-level data manipulation using ARM assembly
- Function calling between C and assembly code
- Memory allocation and management
- Basic loop structures and conditional operations

**Core Operations:**
```assembly
// Bit extraction function
get_bit:
    // Input: x0=array, w1=total_bits, w2=bit_index
    // Output: w0=bit_value (0 or 1)
    // Calculate which word contains the bit
    // Extract the specific bit from that word
    ret
```

```assembly
// Bit setting function
set_bit:
    // Input: x0=array, w1=total_bits, w2=bit_index
    // Set the specified bit to 1
    // Calculate word offset and bit position
    // Use OR operation to set the bit
    ret
```

### Sieve of Eratosthenes (`sieve/`)

**Objective:** Implement command-line argument processing and input validation for numerical algorithms.

**Current Implementation:**
- **`sieve.S`** - Command-line argument parsing and validation
- Basic input validation for sieve size parameter
- Error handling for invalid arguments

**Key Features:**
- Command-line argument processing in assembly
- Input validation and error reporting
- String conversion from ASCII to integer
- Proper program exit codes

**Command-Line Processing:**
```assembly
main:
    // Check argument count
    cmp w0, #2          // argc should be 2
    blt show_usage      // Show usage if too few args
    
    // Convert string to integer
    ldr x0, [x1,#8]     // Get argv[1]
    bl atoi             // Convert to integer
    
    // Validate minimum size
    cmp w0, #2
    blt show_error      // Size must be >= 2
    
    // Continue with algorithm...
```

## Technical Skills Demonstrated

### Assembly Programming
- **ARM Assembly Syntax** - Basic instruction usage and formatting
- **Register Management** - Proper use of ARM64 registers
- **Function Calls** - Assembly function implementation
- **Stack Operations** - Prologue/epilogue for function calls

### Bit Manipulation
- **Bit Extraction** - Reading individual bits from memory
- **Bit Setting** - Modifying individual bits in memory
- **Word Calculation** - Converting bit indices to memory addresses
- **Masking Operations** - Using AND/OR for bit manipulation

### System Programming
- **Command-Line Arguments** - Processing program arguments
- **Input Validation** - Checking argument validity
- **Error Handling** - Proper error reporting and exit codes
- **String Processing** - Basic ASCII string handling

## Build and Usage

```bash
# Conway's Game of Life bit operations
cd life/
make
./life

# Sieve command-line processing
cd sieve/
make
./sieve 100    # Process sieve of size 100
./sieve        # Show usage error
./sieve 1      # Show minimum size error
```

## Learning Outcomes

### Low-Level Programming
- **Assembly Language Basics** - Fundamental ARM assembly concepts
- **Bit-Level Operations** - Direct manipulation of binary data
- **Memory Addressing** - Calculating memory locations for data access
- **Register Usage** - Efficient use of processor registers

### Algorithm Implementation
- **Bit Array Operations** - Working with compact data representations
- **Input Processing** - Handling command-line arguments
- **Validation Logic** - Checking input parameters for correctness
- **Error Reporting** - Providing meaningful error messages

### System Integration
- **C-Assembly Interface** - Calling assembly functions from C
- **Build Systems** - Compiling mixed C and assembly projects
- **Debugging** - Basic debugging of assembly code

## File Structure

```
5-assembly-practice/
├── life/
│   ├── life.S          # Bit manipulation operations
│   ├── get_bit.S       # Bit extraction function
│   ├── set_bit.S       # Bit setting function
│   ├── main.c          # C test harness
│   ├── tests.c         # Basic tests
│   └── Makefile        # Build configuration
└── sieve/
    ├── sieve.S         # Command-line processing
    └── Makefile        # Build configuration
```

## Implementation Details

### Bit Operations in `life/`
- **Array Representation** - Bits stored in integer arrays
- **Index Calculation** - Converting bit positions to word/bit offsets
- **Memory Access** - Loading and storing words containing target bits
- **Bit Manipulation** - Using shifts and masks for bit operations

### Command Processing in `sieve/`
- **Argument Count** - Checking number of command-line arguments
- **String Conversion** - Converting ASCII numbers to integers
- **Bounds Checking** - Validating input ranges
- **Error Messages** - Providing clear error feedback

## Testing Approach

### Bit Operation Tests
- **Boundary Conditions** - First and last bits in arrays
- **Edge Cases** - Empty arrays, single-bit arrays
- **Bit Patterns** - Various combinations of set/clear bits
- **Memory Alignment** - Different word boundaries

### Command-Line Tests
- **Valid Arguments** - Correct number and format of arguments
- **Invalid Arguments** - Wrong count, non-numeric values
- **Boundary Values** - Minimum and maximum valid sizes
- **Error Handling** - Proper error codes and messages

## Educational Value

This project teaches:
- **Assembly Fundamentals** - Basic ARM assembly programming
- **Bit Manipulation** - Low-level binary data operations
- **System Programming** - Command-line interface design
- **Mixed-Language Programming** - Integration of C and assembly
- **Algorithm Translation** - Converting concepts to assembly code

---

*This project provides foundational experience with assembly language programming and bit-level operations essential for systems programming and embedded development.*
