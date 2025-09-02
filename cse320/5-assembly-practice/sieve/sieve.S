//
// Data section
//
.data

usage: .asciz "Usage: sieve <size>\n";

minsize: .asciz "Sieve size must be at least 2\n";

//
// Text section
//

.text

.global main

//
// main(argc, argv)
// w0: The number of arguments
// x1: Pointer to an array of string pointers
// 
main: 
    stp x29, x30, [sp, #-16]!   // Push fp and lr onto the stack
    stp x19, x20, [sp, #-16]!   // Push x19 and x20 onto the stack
    stp x21, x22, [sp, #-16]!   // Push x21 and x22 onto the stack
    
	cmp w0, #2		// Compare argc to 2
	bge args_ok		// Branch if argc >= 2

	ldr x0, =usage		// Get address of message
	bl printf		// printf

	mov w0, #1		// Return value: 1
	b main_return		// return

args_ok:
	ldr x0, [x1,#8]		// Get argv[1]
	bl atoi
	
	cmp w0, #2
	bge size_ok
	
	ldr x0, =minsize	// "Sieve size must be at least 2\n";
	bl printf

	mov w0, #1		// Return value: 1
	b main_return		// return

size_ok:
	mov x0, #0
    
main_return:
    ldp x21, x22, [sp], #16     // Restore x21 and x22 from the stack
    ldp x19, x20, [sp], #16     // Restore x19 and x20 from the stack
    ldp x29, x30, [sp], #16     // Restore fp and lr from the stack
    ret
