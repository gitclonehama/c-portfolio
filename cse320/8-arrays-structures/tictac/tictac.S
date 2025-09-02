.data
//
// The Game description data structure
//
.equ	game_rows, 0
.equ	game_cols, 4
.equ	game_array, 8
.equ    game_size, 16

//
// The Game cell data structure
// This is the contents of a location in the array
//
.equ    cell_expected, 0
.equ    cell_actual, 4
.equ    cell_size, 8

//
// The game display format strings
//
.align 4
header_format:  .asciz "    "      // Spaces before column numbers
col_num_format: .asciz "%3d"       // Format for column numbers
newline:        .asciz "\n"        // Newline character
row_num_format: .asciz "%3d "      // Format for row numbers
item_format:    .asciz "  %c"      // Format for cell contents (X, O, or .)

.text

.global create_game

//
// Create the game abstract data type
// void *create_game(int rows, int cols)
//
create_game:
	stp x29, x30, [sp, #-16]!
	stp x19, x20, [sp, #-16]!
	stp x21, x22, [sp, #-16]!
    
 	mov w19, w0		// rows
	mov w20, w1		// cols

	mov w0, #1
	mov w1, #game_size
	bl calloc		// allocate

    //
    // Set the data structure initial values
    //
    str w19, [x0, #game_rows]
    str w20, [x0, #game_cols]

    mov x21, x0         // x21 = game pointer

    //
    // Allocate the game array
    //
    mul w0, w19, w20    // w0 = row * cols
    mov w1, #cell_size  // w1 = cell size
    bl calloc

    str x0, [x21, #game_array]    // Storing calloc result (x0) into game_array (x21 offset by #game_array)

    mov x0, x21                   // x0 = #game_array

create_game_done:
    ldp x21, x22, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x29, x30, [sp], #16
    ret
    
    
.global destroy_game
//
// void destroy_game(void *game)
// Destroy the game, freeing all memory
//
destroy_game:
	stp x29, x30, [sp, #-16]!
  	stp x19, x20, [sp, #-16]!

    ldr x19, [x0, #game_array]  // x19 = game_array pointer
    mov x20, x0  // x20 = *Game
    
    mov x0, x19                 // x0 = game_array pointer
    bl free                     // Free the game_array in memory

    mov x0, x20    // Pass the Game pointer to x0
    bl free       // Free the allocated memory
    
    ldp x19, x20, [sp], #16
    ldp x29, x30, [sp], #16
    ret
    
    
.global get_rows

//
// Get the number of rows in the game
// int get_rows(void *game)
//
get_rows:
    ldr w0, [x0, #game_rows]  // Load the value at offset game_rows into w0
    ret                       // Return with thee value in w0

.global get_cols

//
// Get the number of columns in the game
// int get_cols(void *game)
//
get_cols:
    ldr w0, [x0, #game_cols]  // Load the value at offset game_cols into w0
    ret                       // Return with the value in w0

.global display_game

//
// Display the game
//
display_game:
    // Function prologue
    stp x29, x30, [sp, #-16]!
    stp x19, x20, [sp, #-16]!

    mov x19, x0                   // x19 = game pointer

    // Load number of columns into w20
    ldr w20, [x19, #game_cols]    // w20 = game->cols

    // Load number of rows into w22
    ldr w22, [x19, #game_rows]    // w22 = game->rows

    // Print initial spaces before column numbers
    adr x0, header_format         // x0 = address of "    "
    bl printf                     // Call printf

    // Initialize column index w21 = 1
    mov w21, #1                   // w21 = column index

print_columns_loop:
    cmp w21, w20                  // Compare w21 with w20 (total columns)
    bgt done_printing_columns     // If w21 > w20, exit loop

    adr x0, col_num_format        // x0 = address of "%3d"
    mov w1, w21                   // w1 = current column index
    bl printf                     // Print the column number

    add w21, w21, #1              // w21 = w21 + 1
    b print_columns_loop          // Loop back

done_printing_columns:
    // Print newline
    adr x0, newline               // x0 = address of "\n"
    bl printf                     // Call printf

    // Initialize row index w23 = 1
    mov w23, #1                   // w23 = row index

print_rows_loop:
    cmp w23, w22                  // Compare w23 (current row) with w22 (total rows)
    bgt done_printing_rows        // If w23 > w22, exit the loop

    // Print the row number
    adr x0, row_num_format        // x0 = address of "%3d "
    mov w1, w23                   // w1 = w23 (current row index)
    bl printf                     // Call printf to print the row number

    // Initialize column index w21 = 1
    mov w21, #1                   // w21 = column index

print_cells_loop:
    cmp w21, w20                  // Compare w21 with w20 (total columns)
    bgt end_of_row                // If w21 > w20, exit inner loop

    // Get cell address
    mov x0, x19                   // x0 = game pointer
    mov w1, w23                   // w1 = row index (r)
    mov w2, w21                   // w2 = column index (c)
    bl game_index                 // x0 = cell address

    // Load cell_actual into w24
    ldr w24, [x0, #cell_actual]   // w24 = cell->actual

    // Prepare to print
    cmp w24, #0
    bne print_cell_value          // If cell_actual != 0, branch to print_cell_value

    // cell_actual == 0, print '.'
    mov w1, '.'                   // w1 = ASCII code for '.'
    b print_cell                  // Skip to printing the cell

print_cell_value:
    // cell_actual != 0, print the character
    mov w1, w24                   // w1 = cell_actual

print_cell:
    adr x0, item_format           // x0 = address of "  %c"
    bl printf                     // Print the cell value

    // Increment column index
    add w21, w21, #1              // w21 = w21 + 1
    b print_cells_loop            // Loop back to process the next cell

end_of_row:
    // Print newline
    adr x0, newline               // x0 = address of "\n"
    bl printf                     // Call printf

    // Increment row index
    add w23, w23, #1              // w23 = w23 + 1
    b print_rows_loop             // Loop back to process the next row

done_printing_rows:
    // Restore callee-saved registers
    ldp x19, x20, [sp], #16
    ldp x29, x30, [sp], #16
    ret

.global set_cell_actual

//
// int set_cell_actual(void *game, int row, int col, char ch);
// Returns: 1 if the answer value is correct
//
set_cell_actual:
	stp x29, x30, [sp, #-16]!
	stp x19, x20, [sp, #-16]!

	mov w19, w3    // w19 = ch
    bl game_index  // x0 = game_index

    // Store 'ch' into cell_actual
    str w19, [x0, #cell_actual] // *(cell + cell_actual) = ch

    // Load cell_expected into w20
    ldr w20, [x0, #cell_expected] // w20 = game.cell_expected

    cmp w19, w20    // compare actual (w19) vs expected (w20)
    cset w0, eq     // w0 = (ch == expected) ? 1 : 0

    b set_cell_actual_done

set_cell_actual_done:
	ldp x19, x20, [sp], #16
	ldp x29, x30, [sp], #16
    ret

.global set_cell_expected

//
// void set_cell_expected(void *game, int row, int col, char ch);
//
set_cell_expected:
	stp x29, x30, [sp, #-16]!
	stp x19, x20, [sp, #-16]!
    
    mov w19, w3    // save ch in w19
    bl game_index

    str w19, [x0, #cell_expected] // save ch into game.cell_expected

	ldp x19, x20, [sp], #16
	ldp x29, x30, [sp], #16
    ret



.global game_win

//
// int game_win(void *game)
// Returns true when the game is done/won
//
game_win:
    stp x29, x30, [sp, #-16]!
	stp x19, x20, [sp, #-16]!
    
	// x0 is the game pointer
    
    ldr w1, [x0, #game_rows]    // w1 = # of rows

    ldr w2, [x0, #game_cols]    // w2 = # of cols

    mul w3, w1, w2              // w3 = # of cells

    ldr x4, [x0, #game_array]   // x4 = pointer to game_array

    mov w5, #0                  // i = 0

    mov w0, #1                  // Assuming game is won
			
game_win_loop:
    cmp w5, w3                  // check if i == # of cells
    bge game_win_done

    // Calculate cell address x6 = x4 + (w5 * cell_size (8 bytes)
    mov w6, w5
    lsl w6, w6, #3          // w6 = w5 * 8
    add x6, x4, w6, uxtw    // x6 = address of current cell

    ldr w7, [x6, #cell_expected]
    ldr w8, [x6, #cell_actual]

    cmp w7, w8
    bne game_win_not

    add w5, w5, #1    // i++;
    b game_win_loop

game_win_not:
    mov w0, #0
    b game_win_done
    
game_win_done:
	ldp x19, x20, [sp], #16
    ldp x29, x30, [sp], #16
    ret

.global game_index
//
// int *game_index(void *game, int row, int col)
// Get the address of a row and column in the cells
//   
game_index:
    stp x29, x30, [sp, #-16]!

    sub w1, w1, #1   // w1 = zero based row
    sub w2, w2, #1   // w2 = zero based col

    ldr w3, [x0, #game_cols]    // Load number of columns into w3
    mul w3, w3, w1              // w3 = row * cols
    add w3, w3, w2              // w3 = (row * cols) + col
    mov w4, #cell_size          // Load cell_size
    mul w3, w3, w4              // w3 = index * cell_size

    ldr x4, [x0, #game_array]   // Load base address of game array into x4
    add x0, x4, w3, uxtw        // x0 = array_address + offset

    
    ldp x29, x30, [sp], #16
    ret                         // Return address in x0
