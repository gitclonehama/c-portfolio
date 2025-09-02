// life.S for lifers
.global life
.extern calloc
.extern free
.extern memcpy
.extern get_bit
.extern set_bit

// Function prototype:
// void life(int *cells, int width, int height);

life:
    // Prologue
    stp     x29, x30, [sp, #-16]!      // Save frame pointer and link register
    mov     x29, sp
    stp     x19, x20, [sp, #-16]!      // Save callee-saved registers x19 and x20
    stp     x21, x22, [sp, #-16]!      // Save x21 and x22
    stp     x23, x24, [sp, #-16]!      // Save x23 and x24
    stp     x25, x26, [sp, #-16]!      // Save x25 and x26
    stp     x27, x28, [sp, #-16]!      // Save x27 and x28

    // Save input parameters
    mov     x19, x0             // x19 = cells pointer
    mov     w25, w1             // w25 = width (32-bit)
    mov     w26, w2             // w26 = height (32-bit)

    // Calculate size = width * height (number of integers)
    mul     w27, w25, w26       // w27 = size (number of ints)
    mov     w28, w27            // w28 = size (copy for later use)

    // Calculate total_bits = size * 32
    lsl     w21, w27, #5        // w21 = total_bits = size * 32

    // Check if total_bits is zero (nothing to do)
    cbz     w21, function_end

    // Allocate memory for cells2
    // Since size is in ints, allocate size * sizeof(int)
    uxtw    x3, w27             // x3 = nmemb (number of elements)
    mov     x1, #4              // x1 = size of each element in bytes

    bl      calloc              // x0 = pointer to allocated memory (cells2)
    cbz     x0, allocation_failed  // If calloc failed, handle error
    mov     x20, x0             // x20 = cells2 pointer

    // Initialize loop index
    mov     w22, #0             // w22 = i (32-bit index)

    // Main loop over bits
main_loop:
    cmp     w22, w21            // Compare i with total_bits
    bge     end_main_loop       // Exit loop if i >= total_bits

    // Get bit i from cells
    mov     x0, x19             // x0 = cells pointer
    mov     w1, w21             // w1 = total_bits
    mov     w2, w22             // w2 = i

    bl      get_bit             // w0 = bit value at i in cells

    cmp     w0, #0
    beq     increment_i         // If bit is 0, continue to next bit

    // Bit is 1
    // Set saved = 1
    mov     w23, #1             // w23 = saved = 1

    // Optionally set bit i in cells2 to 0 (cells2 is already zero-initialized)

    // While loop: while saved == 1
while_saved:
    add     w22, w22, #1        // i++
    cmp     w22, w21            // Check if i < total_bits
    bge     set_saved_zero      // If i >= total_bits, set saved = 0 and exit loop

    // Get bit i from cells
    mov     x0, x19             // x0 = cells pointer
    mov     w1, w21             // w1 = total_bits
    mov     w2, w22             // w2 = i

    bl      get_bit             // w0 = bit value at i in cells
    mov     w23, w0             // saved = bit value

    // Set bit i in cells2 to 1
    mov     x0, x20             // x0 = cells2 pointer
    mov     w1, w21             // w1 = total_bits
    mov     w2, w22             // w2 = i

    bl      set_bit             // Set bit i in cells2

    cmp     w23, #1
    beq     while_saved         // Continue while saved == 1

set_saved_zero:
    // Do not increment i here; it has already been incremented in the while loop
    b       main_loop

increment_i:
    add     w22, w22, #1        // i++
    b       main_loop

end_main_loop:
    // Copy cells2 back to cells
    // Calculate total_size_bytes = size * sizeof(int)
    lsl     x4, x28, #2         // x4 = total_size_bytes (size in bytes)

    mov     x0, x19             // x0 = destination (cells)
    mov     x1, x20             // x1 = source (cells2)
    mov     x2, x4              // x2 = total_size_bytes

    bl      memcpy              // Copy cells2 to cells

    // Free cells2
    mov     x0, x20             // x0 = pointer to free (cells2)
    bl      free                // Free the allocated memory

function_end:
    // Epilogue
    ldp     x27, x28, [sp], #16     // Restore callee-saved registers
    ldp     x25, x26, [sp], #16
    ldp     x23, x24, [sp], #16
    ldp     x21, x22, [sp], #16
    ldp     x19, x20, [sp], #16
    ldp     x29, x30, [sp], #16     // Restore frame pointer and link register
    ret

allocation_failed:
    // For now, just return
    b       function_end
