# Arrays and Structures

Introduction to basic data structures and simple image processing in C and ARM assembly language, demonstrating fundamental concepts of memory management, abstract data types, and basic file I/O operations.

## Project Overview

This project introduces basic data structure concepts and simple image manipulation techniques. Students learn to implement abstract data types, manage dynamic memory allocation, and work with basic file formats through hands-on programming exercises.

## Projects

### blocky - Basic Image Processing

**Objective:** Implement a simple image ADT and basic PNG file processing using libpng library.

**Image Abstract Data Type:**
```c
// Simple image structure (implemented in assembly)
typedef struct {
    int width;           // Image width in pixels
    int height;          // Image height in pixels
    double *pixels;      // Array of pixel values (grayscale)
} Image;
```

**Core Functions:**
```c
// Image ADT operations
void *create_image(int width, int height);     // Create image with given dimensions
void destroy_image(void *image);               // Free image memory
int get_width(void *image);                    // Get image width
int get_height(void *image);                   // Get image height
void set_pixel(void *image, int row, int col, double value);  // Set pixel value
double get_pixel(void *image, int row, int col);              // Get pixel value
```

**PNG File Processing:**
```c
// Basic PNG I/O using libpng
void *read_image(const char *filename);        // Read PNG file into image ADT
int write_image(void *image, const char *filename);  // Write image ADT to PNG file
```

**Image Processing Operation:**
The `blocky` function is a placeholder for image processing operations. Currently implemented as a stub that performs no transformation:

```assembly
// blocky.S - Placeholder for image processing
.text
.global blocky

blocky:
    ret  // Currently does nothing - just returns input unchanged
```

**Key Features:**
- **Memory Management** - Dynamic allocation of image data structures
- **File I/O** - Basic PNG reading and writing using libpng
- **Data Conversion** - RGB to grayscale conversion
- **Error Handling** - Basic file operation error checking

### tictac - Pattern Matching Game

**Objective:** Implement a simple pattern-matching puzzle game with basic game state management.

**Game Data Structure:**
```c
// Game ADT structure
typedef struct {
    int rows;           // Number of rows
    int cols;           // Number of columns
    Cell *array;        // Array of game cells
} Game;

// Cell structure for each position
typedef struct {
    char expected;      // Correct value for this position
    char actual;        // Current player guess
} Cell;
```

**Game Operations:**
```c
// Game management functions
void *create_game(int rows, int cols);         // Create new game
void destroy_game(void *game);                 // Free game memory
int get_rows(void *game);                      // Get number of rows
int get_cols(void *game);                      // Get number of columns
void display_game(void *game);                 // Display current game state
void set_cell_expected(void *game, int row, int col, char ch);  // Set correct value
int set_cell_actual(void *game, int row, int col, char ch);     // Set player guess
int game_win(void *game);                      // Check if game is complete
```

**Game File Format:**
Games are loaded from `.tictac` files with the following format:
```
4              // Number of rows
4              // Number of columns
XOOX           // Expected pattern (solution)
OXXO
XXOO
OOXX
.OO.           // Initial display pattern
....
XX..
.O..
```

**Gameplay:**
- Player enters guesses in format: `row column value`
- Values must be 'X' or 'O'
- If guess matches expected value, it's accepted
- If guess is wrong, player loses immediately
- Game continues until all positions are correctly filled or wrong guess is made

**Key Features:**
- **Dynamic Memory** - Game board allocation based on file dimensions
- **File Parsing** - Reading game configurations from text files
- **Input Validation** - Checking row/column bounds and valid characters
- **Game State** - Tracking progress and win/lose conditions

## Learning Outcomes

### Data Structure Fundamentals
- **Abstract Data Types** - Encapsulation of data and operations
- **Dynamic Memory Management** - malloc/calloc and free operations
- **Pointer Arithmetic** - Array indexing and memory access
- **Structure Alignment** - Memory layout considerations

### Assembly Language Skills
- **Function Prologues/Epilogues** - Stack frame management
- **Parameter Passing** - Register usage for function arguments
- **Memory Access** - Loading/storing data from/to memory
- **Basic Arithmetic** - Integer operations and address calculations

### File I/O and Libraries
- **Library Integration** - Using external libraries (libpng)
- **File Operations** - Opening, reading, and writing files
- **Error Handling** - Basic error checking and recovery
- **Data Formats** - Understanding simple file formats

### Programming Practices
- **Modular Design** - Separating interface from implementation
- **Memory Safety** - Proper allocation and deallocation
- **Input Validation** - Checking user input for validity
- **Code Organization** - Structuring programs into logical components

## File Structure

```
8-arrays-structures/
├── blocky/
│   ├── blocky.S            # Image processing stub (currently empty)
│   ├── image.h             # Image ADT header
│   ├── image.S             # Image ADT implementation
│   ├── main.c              # PNG processing application
│   ├── readimage.c         # PNG file reading
│   ├── writeimage.c        # PNG file writing
│   ├── Makefile            # Build configuration
│   ├── acro-squirrel.png   # Sample image
│   ├── cabbage-evil.png    # Sample image
│   ├── sparty-hama.png     # Sample image
│   ├── sparty-m.png        # Sample image
│   ├── sparty-m1.png       # Sample image
│   └── sparty.png          # Sample image
└── tictac/
    ├── tictac.S            # Game ADT implementation
    ├── main.c              # Game application
    ├── Makefile            # Build configuration
    ├── 4x4.tictac          # Sample game file
    ├── 6x6.tictac          # Sample game file
    ├── 6x8.tictac          # Sample game file
    └── 8x12hard.tictac     # Complex game file
```

## Build Instructions

```bash
# Build image processing project
cd blocky/
make
./blocky input.png output.png

# Build pattern matching game
cd tictac/
make
./tictac 4x4.tictac
```

## Usage Examples

### Image Processing
```bash
# Convert PNG to grayscale (currently just copies)
./blocky sparty.png output.png

# Process multiple images
for img in *.png; do
    ./blocky "$img" "processed_$img"
done
```

### Pattern Matching Game
```bash
# Play a 4x4 puzzle
./tictac 4x4.tictac

# Play larger puzzles
./tictac 6x6.tictac
./tictac 8x12hard.tictac
```

**Sample Game Interaction:**
```
TicTac: Game size 4 rows and 4 columns

     1  2  3  4
  1  .  .  .  .
  2  .  .  .  .
  3  X  X  .  .
  4  .  O  .  .

Enter guess (row column value): 1 1 X
Enter guess (row column value): 2 2 O
...
```

## Technical Skills Demonstrated

- **C Programming** - Basic syntax, functions, and control structures
- **ARM Assembly** - Function implementation and memory operations
- **Memory Management** - Dynamic allocation and deallocation
- **File I/O** - Reading and writing files in C
- **Library Usage** - Integrating external libraries
- **Data Structures** - Basic ADT design and implementation

---

*This project provides foundational experience with data structures, memory management, and basic file operations essential for systems programming and software development.*
