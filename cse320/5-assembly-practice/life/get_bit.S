.text
.global get_bit


//
// Get a bit from an array of words.
// x0 - Array of integers
// w1 - Width of the array in bits
// w2 - Desired bit
//
get_bit:
    // Save frame pointer and link register onto the stack
    stp x29, x30, [sp, #-16]!   // Decrement stack pointer and store x29, x30
    mov x29, sp                 // Update frame pointer

    // Validate 'desired' parameter: if desired < 0 or desired >= width, return 0
    cmp w2, #0                  // Compare desired with 0
    blt return_zero             // If desired < 0, branch to return_zero
    cmp w2, w1                  // Compare desired with width
    bge return_zero             // If desired >= width, branch to return_zero

    // Calculate word index and bit index
    lsr w3, w2, #5              // w3 = desired >> 5 (word index)
    and w4, w2, #31             // w4 = desired & 31 (bit index within the word)

    // Load the word containing the desired bit
    ldr w5, [x0, w3, uxtw #2]   // w5 = data[w3], offset calculated as w3 * 4

    // Calculate the shift amount to bring the desired bit to LSB position
    mov w7, #31                 // w7 = 31
    sub w6, w7, w4              // w6 = 31 - w4

    // Shift the word to align the desired bit to the least significant bit
    lsr w5, w5, w6              // w5 = w5 >> (31 - bit index)

    // Extract the desired bit
    and w0, w5, #1              // w0 = w5 & 1 (desired bit value)

    b get_bit_done              // Branch to function epilogue

return_zero:
    mov w0, #0                  // Return 0 if desired is out of range

get_bit_done:
    ldp x29, x30, [sp], #16     // Restore frame pointer and link register
    ret                          // Return to caller
