# Memory and String Processing

Introduction to bit manipulation and character processing in C, implementing a custom character-to-binary decoder.

## Project Overview

This project introduces basic bit-level operations and character processing through implementation of a decoder that converts encoded character strings into binary data using custom character-to-bit mappings.

## decoder - Character-to-Binary Decoder

**Objective:** Implement a decoder that translates encoded character sequences into binary data using predefined character-to-bit mappings.

### Key Features

- **Custom Character Mapping** - Characters represent either 2-bit or 3-bit binary values
- **Bit-Level Operations** - Direct manipulation of individual bits in output buffer
- **Memory Safety** - Bounds checking to prevent buffer overflows
- **Character Processing** - Sequential parsing of input character stream

### Encoding Scheme

#### 3-Bit Characters (advance 3 bits, set specific bits)
| Character | Binary | Action |
|-----------|---------|---------|
| 'L' | 000 | Advance 3 bits (no bits set) |
| 'E' | 001 | Advance 2 bits, set bit 2 |
| 'i' | 010 | Advance 1 bit, set bit 1, advance 1 bit |
| 'q' | 011 | Advance 1 bit, set bits 1-2 |
| '0' | 100 | Set bit 0, advance 2 bits |
| 'Q' | 101 | Set bit 0, advance 1 bit, set bit 2 |
| 'h' | 110 | Set bits 0-1, advance 1 bit |
| '%' | 111 | Set bits 0-2 |

#### 2-Bit Characters (advance 2 bits, set specific bits)
| Character | Binary | Action |
|-----------|---------|---------|
| '3' | 00 | Advance 2 bits (no bits set) |
| '-' | 01 | Advance 1 bit, set bit 1 |
| '8' | 10 | Set bit 0, advance 1 bit |
| 'l' | 11 | Set bits 0-1 |

### Technical Implementation

#### Core Algorithm
```c
void decoder(const char *encoded, char *decoded, int maxLen) {
    // Initialize output buffer to zeros
    memset(decoded, 0, maxLen);
    
    // Nested helper function for bit setting
    void setBit(char *decoded, int maxLen, int bit) {
        int byte = bit / 8;
        if (byte < maxLen) {
            decoded[byte] |= (1 << (7 - (bit % 8)));
        }
    }
    
    int bit = 0;  // Current bit position
    
    // Process each character
    for (int i = 0; encoded[i] != '\0'; i++) {
        switch (encoded[i]) {
            case 'L':  // 000 - advance 3 bits
                bit += 3;
                break;
            case 'E':  // 001 - advance 2, set bit 2
                bit += 2;
                setBit(decoded, maxLen, bit++);
                break;
            // ... cases for other characters
        }
    }
}
```

#### Memory Operations

- **Buffer Initialization** - Zero out output buffer before processing
- **Bit Setting** - Set individual bits using bitwise OR operations
- **Bounds Checking** - Validate byte position before memory access
- **Sequential Processing** - Process characters in order

### Algorithm Characteristics

#### Time Complexity
- **O(n)** where n is input string length
- Single pass through input with constant work per character

#### Space Complexity
- **O(m)** where m is output buffer size
- Fixed-size output buffer with no dynamic allocation

#### Memory Access
- Sequential character reading from input string
- Calculated bit positions for output buffer
- Direct byte manipulation for efficiency

## Learning Outcomes

### Bit Manipulation Skills
- **Bit-Level Operations** - Setting and clearing individual bits
- **Byte Calculations** - Converting bit positions to byte offsets
- **Bitwise Operators** - Using OR, AND, and shift operations
- **Binary Representation** - Understanding bit ordering in bytes

### C Programming Techniques
- **Nested Functions** - Local helper functions for code organization
- **Switch Statements** - Multi-way branching for character processing
- **Pointer Arithmetic** - Memory addressing and buffer manipulation
- **String Processing** - Character-by-character input parsing

### Memory Management
- **Buffer Safety** - Preventing overflows with bounds checking
- **Memory Initialization** - Proper setup of output buffers
- **Direct Memory Access** - Low-level memory manipulation
- **Resource Management** - Fixed-size buffer handling

## Build and Usage

### Compilation
```bash
cd decoder/
make
./decoder
```

### Example Usage
```c
// Input: encoded character string
const char *encoded = "Eiq0Q";

// Output: binary data in buffer
char decoded[100];
decoder(encoded, decoded, sizeof(decoded));

// Result: bits set according to character mappings
```

## File Structure

```
2-memory-string/
└── decoder/
    ├── decoder.c       # Decoder implementation with bit manipulation
    ├── decoder.h       # Function prototype
    ├── main.c          # Test program with sample encoded string
    └── Makefile        # Build configuration
```

## Implementation Details

### Bit Setting Logic
- Each character advances the bit position by 2 or 3 bits
- Specific bits are set based on character encoding
- Bits are set from MSB to LSB within each byte
- Output buffer accumulates the final binary result

### Error Handling
- Unknown characters are ignored (default case in switch)
- Buffer bounds checking prevents memory corruption
- Null termination handling for input strings

### Testing Approach
- **Character Mapping** - Verify each character produces correct bit pattern
- **Buffer Bounds** - Test with various buffer sizes
- **Edge Cases** - Empty strings, long inputs, invalid characters
- **Bit Accuracy** - Manual verification of bit positions and values

## Educational Value

This project teaches:
- **Binary Operations** - Fundamental bit manipulation techniques
- **Memory Layout** - Understanding how bits are organized in memory
- **Character Encoding** - Custom encoding scheme design and implementation
- **Low-Level Programming** - Direct memory access and manipulation
- **Algorithm Design** - Systematic processing of sequential data

---

*This project introduces fundamental concepts in bit manipulation and memory operations, providing a foundation for more advanced systems programming topics.*
