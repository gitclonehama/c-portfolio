.data
.balign 8
zero:   .double 0.0             // Constant for 0.0
four:   .double 4.0             // Constant for 4.0

.text
.global ship

//
// int ship(double xn0, double yn0);
//

ship:
        stp x29, x30, [sp, #-16]!

        // Load 0.0 from memory
        ldr x1, =zero
        ldr d6, [x1]                 // d6 = 0.0 (for initializing x and y)
        fmov d7, d1                  // d7 = yn0
        fmov d1, d6                  // d1 = x = 0.0
        fmov d2, d6                  // d2 = y = 0.0
        mov w0, #0                   // w0 = i = 0

ship_loop:

        // Compute x^2 + y^2
        fmul d3, d1, d1              // d3 = x^2
        fmul d4, d2, d2              // d4 = y^2
        fadd d5, d3, d4              // d5 = x^2 + y^2

        // Compare (x^2 + y^2) < 4
        ldr x2, =four                // Load address of "four"
        ldr d8, [x2]                 // d8 = 4.0
        fcmp d5, d8
        bge ship_done                // If (x^2 + y^2) >= 4, exit loop

        // Compare iteration < 255
        cmp w0, #255
        bge ship_done                // If i >= 255, exit loop

        // Compute abs(x)
        fcmp d1, d6                  // Compare x >= 0.0
        bge abs_y                    // if true, check abs(y)
        fneg d1, d1                  // x = -x (abs x)

abs_y:
        // Compute abs(y)
        fcmp d2, d6                  // Compare y >= 0.0
        bge ship_compute             // y and x are positive, continue
        fneg d2, d2                  // y = -y (abs y)

ship_compute:
        // xn1 = x^2 - y^2 + xn0
        fmul d3, d1, d1              // d3 = x^2
        fmul d4, d2, d2              // d4 = y^2
        fsub d8, d3, d4              // d8 = x^2 - y^2
        fadd d8, d8, d0              // d8 = (x^2 - y^2) + xn0

        // yn1 = 2xy + yn0
        fmul d3, d1, d2              // d3 = x * y
        fadd d3, d3, d3              // d3 = 2 * x * y
        fadd d3, d3, d7              // d3 = 2xy + yn0

        // Update x and y
        fmov d1, d8                  // x = xn1
        fmov d2, d3                  // y = yn1

        // Increment i
        add w0, w0, #1               // i++

        // repeat loop
        b ship_loop

ship_done:
        ldp x29, x30, [sp], #16
        ret                          // Return i (result)

