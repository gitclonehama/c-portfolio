//
// Data section
//
.data

msg1:
    .asciz "All Armstrong numbers between 1 and 10000\n\n\n"

msg2:
    .asciz "%ld is an Armstrong number\n"

//
// Text section
//
.text
.global main
/**
 * main(argc, argv)
 * w0: The number of arguments
 * x1: Pointer to an array of string pointers
 */
main:
    // Register aliases
    fp .req x29
    lr .req x30

    // Stack frame offsets
    .equ numbers,   16  // long
    .equ num,       24  // long
    .equ numDigit,  32  // long
    .equ sum,       40  // long
    .equ digit,     48  // long
    .equ size,      64  // Stack frame size (must be multiple of 16)

    // Prologue
    stp fp, lr, [sp, #-size]!     // Adjust sp by -size bytes, store fp and lr
    mov fp, sp                    // Set frame pointer

    // printf("All Armstrong numbers between 1 and 10000\n\n\n");
    ldr x0, =msg1
    bl printf

    // numbers = 1
    mov x0, #1
    str x0, [fp, #numbers]

loop_numbers:
    // Load numbers
    ldr x0, [fp, #numbers]        // x0 = numbers

    // Load 10000 into x1
    movz x1, #10000               // x1 = 10000

    cmp x0, x1
    bgt end_loop_numbers

    // num = numbers
    str x0, [fp, #num]            // num = numbers

    // Call digitcounter(numbers)
    mov x0, x0                     // x0 = numbers
    bl digitcounter
    // Result in w0
    sxtw x0, w0                    // Sign-extend w0 to x0 if necessary
    str x0, [fp, #numDigit]        // numDigit = x0

    // sum = 0
    mov x0, #0
    str x0, [fp, #sum]

sum_loop:
    // Load num
    ldr x0, [fp, #num]            // x0 = num
    cmp x0, #0
    beq sum_loop_end

    // Prepare for ldiv: dividend in x0, divisor in x1
    mov x1, #10
    bl ldiv                        // Calls ldiv(x0, x1), returns quotient in x0, remainder in x1

    // x0 = quotient (new num)
    // x1 = remainder (digit)
    str x0, [fp, #num]            // num = quotient
    str x1, [fp, #digit]          // digit = x1

    // Call pow_long(digit, numDigit)
    ldr x0, [fp, #digit]          // x0 = digit
    ldr x1, [fp, #numDigit]       // x1 = numDigit
    bl pow_long
    // Result in x0

    // sum += result
    ldr x2, [fp, #sum]            // x2 = sum
    add x2, x2, x0                // sum += result
    str x2, [fp, #sum]

    b sum_loop

sum_loop_end:
    // if(numbers == sum)
    ldr x0, [fp, #numbers]        // x0 = numbers
    ldr x1, [fp, #sum]            // x1 = sum
    cmp x0, x1
    bne next_number

    // printf("%ld is an Armstrong number\n", numbers)
    ldr x0, =msg2
    ldr x1, [fp, #numbers]        // x1 = numbers
    bl printf

next_number:
    // numbers++
    ldr x0, [fp, #numbers]
    add x0, x0, #1
    str x0, [fp, #numbers]

    b loop_numbers

end_loop_numbers:
    // Epilogue
    mov w0, #0
    ldp fp, lr, [sp], #size       // Restore fp and lr, adjust sp
    ret

//
// pow_long function
//

/**
 * pow_long(long base, long exp)
 * Computes base raised to the power of exp
 * Returns the result in x0
 */
pow_long:
    // Register aliases
    fp .req x29
    lr .req x30

    // Stack frame offsets
    .equ base,    16  // long
    .equ exp,     24  // long
    .equ result,  32  // long
    .equ size,    48  // Stack frame size (must be multiple of 16)

    // Prologue
    stp fp, lr, [sp, #-size]!     // Adjust sp by -size bytes, store fp and lr
    mov fp, sp                    // Set frame pointer

    // At entry, x0 = base, x1 = exp
    str x0, [fp, #base]
    str x1, [fp, #exp]

    // result = 1
    mov x0, #1
    str x0, [fp, #result]

pow_loop:
    ldr x0, [fp, #exp]            // x0 = exp
    cmp x0, #0
    ble pow_end_loop

    // result *= base
    ldr x1, [fp, #result]         // x1 = result
    ldr x2, [fp, #base]           // x2 = base
    mul x1, x1, x2
    str x1, [fp, #result]         // result = x1

    // exp--
    ldr x0, [fp, #exp]
    sub x0, x0, #1
    str x0, [fp, #exp]

    b pow_loop

pow_end_loop:
    ldr x0, [fp, #result]         // x0 = result

    // Epilogue
    ldp fp, lr, [sp], #size       // Restore fp and lr, adjust sp
    ret
