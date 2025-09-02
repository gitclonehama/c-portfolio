# Floating-Point Programming

Introduction to floating-point arithmetic and mathematical computations in ARM assembly language, demonstrating basic IEEE 754 floating-point operations and simple mathematical algorithms.

## Project Overview

This project introduces floating-point programming concepts through implementation of basic mathematical functions and simple fractal calculations using ARM floating-point instructions.

## Projects

### bezier - Quadratic Bézier Curve Calculation

**Objective:** Implement a single term of quadratic Bézier curve mathematics using floating-point assembly operations.

**Mathematical Formula:**
The implementation calculates: `3 × (1-t)² × t`

This represents the weight for the middle control point in a quadratic Bézier curve.

**Assembly Implementation:**
```assembly
// bezier.S - Single quadratic Bézier term calculation
.text
.global bezier

bezier:
    stp x29, x30, [sp, #-16]!
    
    fmov d1, d0         // d1 = t (save parameter)
    
    ldr x0, =one
    ldr d2, [x0]        // d2 = 1.0
    
    fsub d2, d2, d1     // d2 = 1-t
    fmul d2, d2, d2     // d2 = (1-t)²
    
    fmul d2, d2, d1     // d2 = (1-t)² × t
    
    ldr x0, =three
    ldr d0, [x0]        // d0 = 3.0
    
    fmul d0, d0, d2     // d0 = 3 × (1-t)² × t
    
    ldp x29, x30, [sp], #16
    ret
```

**Key Features:**
- Basic floating-point arithmetic operations
- Parameter passing via floating-point registers
- Simple mathematical computation
- Proper stack frame management

### ship - Mandelbrot Set Calculation

**Objective:** Implement basic Mandelbrot set computation using floating-point arithmetic for fractal generation.

**Algorithm:**
The ship function computes iterations of: `z = z² + c` where z starts at (0,0) and c is the input point (xn0, yn0).

**Key Features:**
- Iterative floating-point calculations
- Conditional branching based on floating-point comparisons
- Loop control with iteration limits
- Basic fractal mathematics

**Implementation:**
```assembly
// ship.S - Mandelbrot set iteration calculation
.text
.global ship

ship:
    stp x29, x30, [sp, #-16]!
    
    // Initialize: x = 0.0, y = 0.0, i = 0
    ldr x1, =zero
    ldr d6, [x1]         // d6 = 0.0
    fmov d1, d6          // d1 = x = 0.0
    fmov d2, d6          // d2 = y = 0.0
    mov w0, #0           // w0 = iteration count
    
ship_loop:
    // Compute x² + y²
    fmul d3, d1, d1      // d3 = x²
    fmul d4, d2, d2      // d4 = y²
    fadd d5, d3, d4      // d5 = x² + y²
    
    // Check if |z|² >= 4.0 (escape condition)
    ldr x2, =four
    ldr d8, [x2]         // d8 = 4.0
    fcmp d5, d8
    bge ship_done        // Exit if escaped
    
    // Check iteration limit
    cmp w0, #255
    bge ship_done        // Exit if max iterations reached
    
    // Compute next iteration: z = z² + c
    // First compute z²
    fmul d3, d1, d1      // x²
    fmul d4, d2, d2      // y²
    fmul d5, d1, d2      // xy
    fadd d5, d5, d5      // 2xy
    
    fsub d1, d3, d4      // x' = x² - y²
    fadd d1, d1, d0      // x' = x² - y² + xn0
    
    fadd d2, d5, d7      // y' = 2xy + yn0
    
    add w0, w0, #1       // increment iteration count
    b ship_loop
    
ship_done:
    ldp x29, x30, [sp], #16
    ret                  // Return iteration count
```

## Learning Outcomes

### Floating-Point Programming Basics
- **ARM Floating-Point Instructions** - Basic FPU operations and register usage
- **IEEE 754 Fundamentals** - Understanding floating-point representation
- **Floating-Point Arithmetic** - Addition, subtraction, multiplication operations
- **Precision Considerations** - Basic awareness of floating-point limitations

### Assembly Language Skills
- **Floating-Point Registers** - Usage of d/s registers for floating-point data
- **Conditional Operations** - Floating-point comparisons and branching
- **Memory Access** - Loading floating-point constants from memory
- **Function Structure** - Proper prologue/epilogue for floating-point functions

### Mathematical Computing
- **Iterative Algorithms** - Basic implementation of iterative mathematical processes
- **Convergence Testing** - Simple escape condition checking
- **Parameter Handling** - Passing floating-point parameters between functions

## File Structure

```
7-floating-point/
├── bezier/
│   ├── bezier.S        # Quadratic Bézier curve calculation
│   ├── main.c          # Test harness
│   └── Makefile        # Build configuration
└── ship/
    ├── ship.S          # Mandelbrot set calculation
    ├── main.c          # Test application
    └── Makefile        # Build configuration
```

## Build Instructions

```bash
# Build Bézier curve calculator
cd bezier/
make
./bezier

# Build Mandelbrot calculator
cd ship/
make
./ship
```

## Usage Examples

### Bézier Curve Calculation
```bash
# Calculate Bézier weight for t = 0.5
./bezier 0.5
# Output: 0.75 (3 × (0.5)² × 0.5 = 3 × 0.25 × 0.5 = 0.75)
```

### Mandelbrot Set Testing
```bash
# Test point (0, 0) - should converge quickly
./ship 0.0 0.0

# Test point (0.5, 0.5) - should escape quickly
./ship 0.5 0.5
```

## Technical Skills Demonstrated

- **Floating-Point Assembly** - Basic ARM floating-point instruction usage
- **Mathematical Computation** - Simple iterative and polynomial calculations
- **Conditional Logic** - Floating-point comparisons and branching
- **Function Implementation** - Parameter passing and return values

---

*This project introduces fundamental floating-point programming concepts and basic mathematical computations in ARM assembly language.*
