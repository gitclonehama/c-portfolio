//
// My first assembly language program
// Name:
//

.text
.global first
.global second
.global min

first:
	mov x1, x0
	add x0, x0, x1
	add x0, x0, x1
	ret

second:
	sub x0, x0, x1
	ret

// A function that determines the minimum of two values.
// (long a, long b) - x0 = a, x1 = b
min:
	subs x2, x0, x1  //  x0 set to a - b
	bge b_is_minimum //  If b >= a
	
	// In this case a is minimum
	mov x0, x0
	b after_block

b_is_minimum:
	// In this case b is the minimum
	mov x0, x1
	b after_block

after_block:
	ret
