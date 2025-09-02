.text
.global set_bit


//
// Get a bit from an array of words.
// x0 - Array of integers
// w1 - Width of the array in bits
// w2 - Desired bit
// w3 - 1 if bit is to be set
//
set_bit:
    // Function prologue: Save frame pointer and link register
    stp x29, x30, [sp, #-16]!    // Decrement stack pointer and store x29, x30
    mov x29, sp                  // Update frame pointer

    // Validate 'desired' parameter: if desired < 0 or desired >= width, do nothing
    cmp w2, #0                   // Compare desired with 0
    blt set_bit_done             // If desired < 0, branch to function epilogue
    cmp w2, w1                   // Compare desired with width
    bge set_bit_done             // If desired >= width, branch to function epilogue

    // Calculate word index and bit index
    lsr w4, w2, #5               // w4 = desired >> 5 (word index, divides by 32)
    and w5, w2, #31              // w5 = desired & 31 (bit index within the word)

    // Load the word containing the desired bit
    ldr w6, [x0, w4, uxtw #2]    // w6 = data[w4]; offset = w4 * 4 bytes

    // Calculate the shift amount to align the desired bit
    mov w7, #31                  // w7 = 31
    sub w7, w7, w5               // w7 = 31 - w5 (shift amount)

    // Create the bit mask
    mov w8, #1                   // w8 = 1
    lsl w8, w8, w7               // w8 = 1 << (31 - bit index)

    // Decide whether to set or clear the bit based on 'setto'
    cbz w3, set_bit_clear        // If setto == 0, branch to clear the bit

    // Set the bit
    orr w6, w6, w8               // w6 = w6 | w8 (set the desired bit)
    b set_bit_store              // Branch to store the updated word

set_bit_clear:
    // Clear the bit
    bic w6, w6, w8               // w6 = w6 & (~w8) (clear the desired bit)

set_bit_store:
    // Store the updated word back to data array
    str w6, [x0, w4, uxtw #2]    // data[w4] = w6

set_bit_done:
    // Function epilogue: Restore frame pointer and link register, and return
    ldp x29, x30, [sp], #16      // Restore x29, x30 and increment stack pointer
    ret                          // Return to caller

