/*
 * Functions to find the Gretest Common Divisor (GCD)
 */
 
.text
.global gcd


/*
 * Determine the gcd of the two numbers
 * gcd(long a, long b)
 * x0 - First number (a)
 * x1 - Second number (b)
 */

gcd:
    gcd:
    // Reserve frame pointer and link register
    stp x29, x30, [sp, #-48]!
    mov x29, sp

    // Save a and b into local variables
    str x0, [x29, #16] // a
    str x1, [x29, #24] // b

gcd_loop:
    // Load a (x0) and check if it is zero
    ldr x0, [x29, #16]
    cbz x0, gcd_done // If a == 0, exit loop

    // Perform b % a using ldiv
    ldr x1, [x29, #24] // Load b into x1
    bl ldiv           // Call ldiv
    str x1, [x29, #32] // Store remainder (b % a)

    // Update b = a and a = remainder
    ldr x1, [x29, #16] // Load a into x1
    str x1, [x29, #24] // Store a into b
    ldr x0, [x29, #32] // Load remainder into a
    str x0, [x29, #16] // Store remainder into a

    // Repeat the loop
    b gcd_loop

gcd_done:
    // Load the result (b) into x0
    ldr x0, [x29, #24]

    // Restore frame pointer and link register
    ldp x29, x30, [sp], #48
    ret