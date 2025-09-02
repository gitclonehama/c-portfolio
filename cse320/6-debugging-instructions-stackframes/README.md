# Debugging, Instructions, and Stack Frames

Advanced debugging techniques, instruction analysis, and stack frame understanding through implementation of mathematical algorithms and debugging exercises in ARM assembly language.

## Project Overview

This project focuses on mastering debugging techniques for assembly language programs while implementing sophisticated mathematical algorithms. Students learn to analyze stack frames, trace instruction execution, and debug complex assembly programs using professional development tools.

## Projects

### armstrong - Armstrong Number Detection

**Objective:** Implement Armstrong number detection algorithm in assembly with comprehensive debugging support.

**Armstrong Number Definition:**
An n-digit number equal to the sum of nth powers of its digits.
- 153 = 1³ + 5³ + 3³ = 1 + 125 + 27 = 153 ✓
- 9474 = 9⁴ + 4⁴ + 7⁴ + 4⁴ = 6561 + 256 + 2401 + 256 = 9474 ✓

**Algorithm Implementation:**
```assembly
// armstrong.S - Armstrong number detection
armstrong:
    // Preserve registers on stack
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    stp x19, x20, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    
    mov x19, x0             // Store original number
    mov x20, x0             // Working copy
    mov x21, #0             // Digit count
    mov x22, #0             // Sum accumulator
    
    // Count digits
count_digits:
    cbz x20, digits_counted
    udiv x20, x20, #10      // Divide by 10
    add x21, x21, #1        // Increment count
    b count_digits
    
digits_counted:
    mov x20, x19            // Reset working copy
    
    // Calculate sum of powers
calculate_sum:
    cbz x20, check_armstrong
    
    // Extract digit
    udiv x23, x20, #10      // Quotient
    msub x24, x23, #10, x20 // Remainder (digit)
    
    // Calculate digit^count
    mov x25, x24            // Base
    mov x26, x21            // Exponent
    mov x27, #1             // Result
    
power_loop:
    cbz x26, power_done
    mul x27, x27, x25       // result *= base
    sub x26, x26, #1        // exponent--
    b power_loop
    
power_done:
    add x22, x22, x27       // Add to sum
    mov x20, x23            // Continue with quotient
    b calculate_sum
    
check_armstrong:
    cmp x19, x22            // Compare original with sum
    cset x0, eq             // Set result (1 if equal, 0 if not)
    
    // Restore registers
    ldp x21, x22, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x29, x30, [sp], #16
    ret
```

### digitcounter - Digital Root and Digit Analysis

**Objective:** Implement comprehensive digit analysis functions including digital root calculation and digit frequency analysis.

**Key Functions:**
```assembly
// Count total digits in a number
count_digits:
    mov x1, #0              // Counter
    cbz x0, zero_case       // Handle zero special case
    
count_loop:
    udiv x0, x0, #10        // Divide by 10
    add x1, x1, #1          // Increment count
    cbnz x0, count_loop     // Continue if not zero
    
    mov x0, x1              // Return count
    ret
    
zero_case:
    mov x0, #1              // Zero has 1 digit
    ret

// Calculate digital root (repeated sum until single digit)
digital_root:
    cmp x0, #10             // Single digit?
    blt single_digit
    
    mov x1, #0              // Sum accumulator
sum_digits:
    cbz x0, check_sum       // No more digits
    udiv x2, x0, #10        // Quotient
    msub x3, x2, #10, x0    // Remainder (digit)
    add x1, x1, x3          // Add digit to sum
    mov x0, x2              // Continue with quotient
    b sum_digits
    
check_sum:
    mov x0, x1              // Move sum to x0
    b digital_root          // Recursive call
    
single_digit:
    ret                     // Return single digit
```

### gcd - Greatest Common Divisor

**Objective:** Implement Euclidean algorithm for GCD calculation with optimized assembly implementation.

**Euclidean Algorithm:**
```assembly
// gcd.S - Euclidean algorithm implementation
gcd:
    // Handle edge cases
    cbz x1, return_x0       // If b = 0, return a
    cbz x0, return_x1       // If a = 0, return b
    
    // Ensure a >= b for optimization
    cmp x0, x1
    bge euclidean_loop
    
    // Swap a and b
    mov x2, x0
    mov x0, x1
    mov x1, x2
    
euclidean_loop:
    // Classic Euclidean algorithm: gcd(a,b) = gcd(b, a mod b)
    udiv x2, x0, x1         // x2 = a / b
    msub x3, x2, x1, x0     // x3 = a - (a/b)*b = a mod b
    
    mov x0, x1              // a = b
    mov x1, x3              // b = a mod b
    
    cbnz x1, euclidean_loop // Continue if b != 0
    
    ret                     // Return a (which is GCD)
    
return_x0:
    ret
    
return_x1:
    mov x0, x1
    ret
```

### sorthex - Hexadecimal Sorting with Debugging

**Objective:** Implement sorting algorithms for hexadecimal numbers with comprehensive debugging instrumentation.

**Features:**
- **Multiple Sorting Algorithms** - Bubble sort, insertion sort, quicksort
- **Hexadecimal I/O** - Reading and writing hex numbers
- **Debug Breakpoints** - Instrumented code for debugging analysis
- **Performance Monitoring** - Instruction counting and timing

**Sorting Implementation:**
```assembly
// sorthex.S - Hexadecimal sorting with debugging
bubble_sort:
    // Debug breakpoint - see breaks.txt
    .global debug_point_1
debug_point_1:
    nop                     // Breakpoint for debugger
    
    mov x19, x0             // Array pointer
    mov x20, x1             // Array size
    mov x21, #0             // Outer loop counter
    
outer_loop:
    cmp x21, x20            // Check outer loop condition
    bge sort_complete
    
    sub x22, x20, x21       // Inner loop limit
    sub x22, x22, #1
    mov x23, #0             // Inner loop counter
    
inner_loop:
    cmp x23, x22            // Check inner loop condition
    bge outer_increment
    
    // Load two adjacent elements
    ldr x24, [x19, x23, lsl #3]        // arr[j]
    add x25, x23, #1
    ldr x26, [x19, x25, lsl #3]        // arr[j+1]
    
    // Compare and swap if necessary
    cmp x24, x26
    ble no_swap
    
    // Swap elements
    str x26, [x19, x23, lsl #3]        // arr[j] = arr[j+1]
    str x24, [x19, x25, lsl #3]        // arr[j+1] = arr[j]
    
    // Debug point for swap tracking
    .global debug_point_2
debug_point_2:
    nop                     // Breakpoint after swap
    
no_swap:
    add x23, x23, #1        // j++
    b inner_loop
    
outer_increment:
    add x21, x21, #1        // i++
    b outer_loop
    
sort_complete:
    ret
```

## Debugging Techniques

### Stack Frame Analysis

**Understanding Stack Layout:**
```assembly
// Function prologue - setting up stack frame
function_entry:
    stp x29, x30, [sp, #-16]!   // Save frame pointer and link register
    mov x29, sp                  // Set up new frame pointer
    sub sp, sp, #32             // Allocate local variables
    
    // Local variables at sp+0, sp+8, sp+16, sp+24
    // Previous frame pointer at x29
    // Return address at x29+8
    
    // Function body...
    
    // Function epilogue - restoring stack frame
    add sp, sp, #32             // Deallocate local variables
    ldp x29, x30, [sp], #16     // Restore frame pointer and link register
    ret
```

### GDB Debugging Commands

**Essential Debugging Workflow:**
```bash
# Compile with debug symbols
make debug

# Start GDB session
gdb ./armstrong

# Set breakpoints
(gdb) break armstrong.S:15
(gdb) break debug_point_1

# Run with arguments
(gdb) run 153

# Examine registers
(gdb) info registers
(gdb) print $x0
(gdb) print $x1

# Examine stack
(gdb) x/8gx $sp
(gdb) backtrace

# Step through instructions
(gdb) stepi
(gdb) nexti

# Watch memory
(gdb) watch *0x7fff12345678
(gdb) display $x19
```

### Memory Analysis

**Stack Frame Inspection:**
```c
// main.c - C test harness with debugging support
void debug_stack_frame() {
    void *frame_pointer = __builtin_frame_address(0);
    void *return_address = __builtin_return_address(0);
    
    printf("Frame pointer: %p\n", frame_pointer);
    printf("Return address: %p\n", return_address);
    
    // Display stack contents
    uint64_t *stack = (uint64_t*)frame_pointer;
    for (int i = -4; i < 4; i++) {
        printf("Stack[%d]: 0x%016lx\n", i, stack[i]);
    }
}
```

## Learning Outcomes

### Debugging Mastery
- **Assembly Debugging** - Proficiency with GDB for assembly programs
- **Stack Analysis** - Understanding stack frames and calling conventions
- **Memory Inspection** - Techniques for examining program memory
- **Breakpoint Usage** - Strategic placement and use of debugging breakpoints

### Instruction-Level Programming
- **Instruction Tracing** - Following program execution at instruction level
- **Register Management** - Efficient use and tracking of processor registers
- **Memory Operations** - Understanding load/store operations and addressing modes
- **Control Flow Analysis** - Tracing branches, loops, and function calls

### Mathematical Algorithm Implementation
- **Number Theory** - Implementation of mathematical concepts in assembly
- **Algorithm Optimization** - Performance tuning at instruction level
- **Numerical Methods** - Efficient algorithms for mathematical computations
- **Error Handling** - Robust handling of edge cases and invalid inputs

## File Structure

```
6-debugging-instructions-stackframes/
├── armstrong/
│   ├── armstrong.S     # Armstrong number detection
│   └── Makefile        # Build with debug symbols
├── digitcounter/
│   ├── digitcounter.S  # Digit analysis functions
│   ├── main.c          # Test harness
│   └── Makefile        # Debug build configuration
├── gcd/
│   ├── gcd.S           # Euclidean algorithm
│   ├── main.c          # Testing framework
│   └── Makefile        # Debug compilation
└── sorthex/
    ├── breaks.txt      # Debugging breakpoint guide
    ├── gethex.S        # Hexadecimal input functions
    ├── main.c          # Main program
    ├── sethex.S        # Hexadecimal output functions
    ├── sorthex.S       # Sorting implementation
    └── Makefile        # Debug build system
```

## Build Instructions

```bash
# Build with debugging symbols
make debug

# Build optimized version
make release

# Build with extra debugging info
make CFLAGS="-g3 -O0 -DDEBUG"
```

## Testing and Validation

### Armstrong Number Testing
```bash
# Test known Armstrong numbers
./armstrong 153    # Should return 1
./armstrong 9474   # Should return 1
./armstrong 123    # Should return 0

# Test edge cases
./armstrong 0      # Single digit case
./armstrong 1      # Single digit case
```

### GCD Testing
```bash
# Test classic cases
./gcd 48 18        # Should return 6
./gcd 17 13        # Should return 1 (coprime)
./gcd 100 50       # Should return 50

# Test edge cases
./gcd 0 5          # Should return 5
./gcd 7 0          # Should return 7
```

### Debugging Exercises
```bash
# Practice debugging workflow
gdb ./sorthex
(gdb) break main
(gdb) run
(gdb) watch array[0]
(gdb) continue
# Observe sorting progress through watchpoints
```

## Educational Value

This project provides essential skills in:
- **Professional Debugging** - Industry-standard debugging techniques and tools
- **Assembly Programming** - Advanced low-level programming concepts
- **Mathematical Computing** - Algorithmic implementation of mathematical concepts
- **Software Analysis** - Understanding program behavior at the lowest level
- **Performance Optimization** - Instruction-level performance tuning

### Career Preparation
- **Systems Programming** - Essential skills for operating system development
- **Embedded Systems** - Debug techniques for resource-constrained environments
- **Game Development** - Performance optimization and low-level debugging
- **Security Research** - Reverse engineering and vulnerability analysis

---

*This debugging-focused project builds essential professional development skills while reinforcing advanced assembly programming concepts, preparing students for careers requiring deep systems-level understanding and debugging expertise.*
