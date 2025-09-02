# Memory Addressing and Hexadecimal Calculations

Foundation project in computer architecture focusing on memory addressing concepts, hexadecimal arithmetic, and the relationship between address width and memory space.

## Project Overview

This project introduces fundamental computer architecture concepts through implementation of memory addressing calculations. Students learn the relationship between address width, memory space, and hexadecimal number systems while developing robust input validation and error handling techniques.

## Core Functionality

### Memory Address Calculator

**Objective:** Calculate total memory space based on hexadecimal address width

**Key Algorithm:**
```cpp
// Extract hex address from command line
std::string hexAddress = argv[1];

// Calculate address width in bits
int hexLength = hexAddress.size();
int addressSize = hexLength * 4;  // 4 bits per hex digit

// Calculate total addressable memory
long long memorySize = std::pow(2, addressSize);  // 2^(address_bits)
```

### Input Validation System

**Hexadecimal Validation:**
```cpp
// Validate each character is a valid hex digit
for (auto ch : hexAddress) {
    if (std::isxdigit(ch) == false) {
        std::cerr << "Error! Please ensure all inputs are valid hex digits." << std::endl;
        return 2;
    }
}
```

**Features:**
- **Character-by-character validation** using `std::isxdigit()`
- **Comprehensive error reporting** with specific error codes
- **Case-insensitive hex digit recognition** (0-9, A-F, a-f)
- **Robust command-line argument processing**

## Technical Implementation

### Memory Calculation Logic

#### Address Space Mathematics
- **1 hex digit** = 4 bits of address space
- **n hex digits** = n × 4 bits total address width
- **Address space** = 2^(address_width) bytes

#### Example Calculations
| Hex Address | Address Bits | Memory Space |
|-------------|--------------|--------------|
| `FF` | 8 bits | 256 bytes |
| `FFF` | 12 bits | 4,096 bytes |
| `FFFF` | 16 bits | 65,536 bytes |
| `FFFFF` | 20 bits | 1,048,576 bytes |

### Error Handling Strategy

#### Error Codes
- **Return 1:** Insufficient command-line arguments
- **Return 2:** Invalid hexadecimal characters in input
- **Return 0:** Successful execution

#### User-Friendly Error Messages
```cpp
if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " HEX ADDRESS" << std::endl;
    return 1;
}
```

## Learning Outcomes

### Computer Architecture Concepts
- **Memory Addressing** - Understanding how addresses relate to memory space
- **Number Systems** - Proficiency with hexadecimal representation and conversion
- **Address Space Calculation** - Mathematical relationship between address width and memory size
- **Memory Hierarchy** - Foundation for understanding memory system design

### C++ Programming Skills
- **Command-Line Processing** - Robust argument parsing and validation
- **String Manipulation** - Character-by-character processing and validation
- **Mathematical Operations** - Exponential calculations and type conversions
- **Error Handling** - Comprehensive error checking and user feedback
- **Standard Library Usage** - Effective use of `<cctype>`, `<cmath>`, and `<iostream>`

### Software Engineering Practices
- **Input Validation** - Defensive programming techniques
- **Error Reporting** - Clear, actionable error messages
- **Code Documentation** - Comprehensive comments and documentation
- **Modular Design** - Logical separation of validation and calculation logic

## Usage Examples

### Valid Inputs
```bash
./proj01 FF
# Output:
# Address Size: 8 bits
# Memory Size: 256 bytes

./proj01 ABCD
# Output:
# Address Size: 16 bits
# Memory Size: 65536 bytes

./proj01 123456
# Output:
# Address Size: 24 bits
# Memory Size: 16777216 bytes
```

### Error Cases
```bash
./proj01
# Output: Usage: ./proj01 HEX ADDRESS

./proj01 GGFF
# Output: Error! Please ensure all inputs are valid hex digits.

./proj01 12XY
# Output: Error! Please ensure all inputs are valid hex digits.
```

## Build Instructions

```bash
cd proj01/
make
./proj01 <HEX_ADDRESS>
```

### Makefile Configuration
```makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

proj01: proj01.cpp
	$(CXX) $(CXXFLAGS) -o proj01 proj01.cpp

clean:
	rm -f proj01

.PHONY: clean
```

## Testing Strategy

### Test Categories

#### Valid Input Testing
- **Single digit:** `F` → 4 bits → 16 bytes
- **Double digit:** `FF` → 8 bits → 256 bytes
- **Quad digit:** `FFFF` → 16 bits → 65,536 bytes
- **Mixed case:** `aBcD` → 16 bits → 65,536 bytes

#### Invalid Input Testing
- **Non-hex characters:** `GGGG`, `123Z`, `HELLO`
- **Mixed valid/invalid:** `A1B2G`, `FF3X`
- **Empty input:** (no arguments)
- **Special characters:** `!@#$`, `12-34`

#### Edge Case Testing
- **Maximum address width:** Test with very long hex strings
- **Single character:** `0`, `F`
- **Leading zeros:** `000F`, `0123`

### Automated Testing
```bash
# Test script example
./proj01 FF && echo "Test 1 PASSED" || echo "Test 1 FAILED"
./proj01 GGGG 2>/dev/null && echo "Test 2 FAILED" || echo "Test 2 PASSED"
```

## File Structure

```
proj01/
├── proj01.cpp          # Main implementation
├── Makefile           # Build configuration
├── test_inputs/       # Test case files
│   ├── valid_hex.txt
│   └── invalid_hex.txt
└── README.md          # Project documentation
```

## Advanced Concepts

### Memory Architecture Implications
- **Addressing Modes** - Understanding how different address widths affect system design
- **Memory Mapping** - Relationship between logical and physical addresses
- **Address Translation** - Foundation for virtual memory concepts
- **System Limitations** - Hardware constraints on maximum memory size

### Performance Considerations
- **Algorithm Efficiency** - O(n) validation where n is string length
- **Memory Usage** - Minimal memory overhead for calculation
- **Error Handling Overhead** - Fast-fail validation for invalid inputs

### Extensibility
- **Additional Number Systems** - Framework for binary, octal calculations
- **Enhanced Validation** - Support for address range validation
- **Output Formatting** - Multiple output formats (bytes, KB, MB, GB)

## Educational Value

### Foundation Skills
- **Computer Architecture Understanding** - Essential concepts for advanced coursework
- **Mathematical Foundations** - Number system conversions and calculations
- **Programming Fundamentals** - Input validation, error handling, and user interface design
- **Problem-Solving Skills** - Breaking down complex problems into manageable components

### Real-World Applications
- **Embedded Systems** - Memory planning and address space allocation
- **Operating Systems** - Virtual memory management and address translation
- **Computer Design** - Memory hierarchy planning and optimization
- **Software Engineering** - Robust input validation and error handling patterns

---

*This foundational project establishes essential computer architecture concepts while demonstrating professional software development practices, serving as a stepping stone to more advanced architecture and systems programming topics.*
