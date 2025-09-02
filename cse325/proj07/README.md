# Cache Memory Simulator

Basic cache memory system simulation demonstrating direct-mapped cache organization, write-back policy, and memory hierarchy concepts.

## Project Overview

This project implements a simple cache memory simulator that demonstrates fundamental computer architecture concepts related to memory hierarchy and cache organization. The simulator supports basic load and store operations with cache hit/miss handling and write-back policy.

## Key Features

- **Direct-Mapped Cache** - 8-line cache with 8-byte blocks
- **16-bit Architecture** - 16 registers and 64KB address space
- **Write-Back Policy** - Modified data written back to memory on eviction
- **Big-Endian Format** - Data stored in big-endian byte order
- **Cache Statistics** - Hit/miss tracking for each memory access
- **Debug Mode** - Step-by-step execution with state display

## Command-Line Usage

```bash
# Basic usage with instruction file
./proj07 -input instructions.txt

# Load initial RAM values and enable debug mode
./proj07 -input instructions.txt -ram ram_init.txt -debug

# Options:
# -input <file> : Instruction file to process
# -ram <file>   : Initial RAM values file (optional)
# -debug        : Enable debug mode with detailed output
```

## Implementation Details

### Memory System Architecture

```cpp
// 16-bit registers (R0-R15)
uint16_t registers[16] = {0};

// Direct-mapped cache with 8 lines
struct CacheLine {
    bool valid;       // Valid bit
    bool modified;    // Dirty bit for write-back
    uint16_t tag;     // 10-bit tag
    uint8_t data[8];  // 8-byte data block
};
CacheLine cache[8];

// 64KB RAM
uint8_t ram[65536] = {0};
```

### Address Mapping

The 16-bit address space is divided as follows:
- **Tag**: Bits 15-6 (10 bits)
- **Cache Line**: Bits 5-3 (3 bits, for 8 cache lines)
- **Byte Offset**: Bits 2-0 (3 bits, for 8-byte blocks)

```cpp
void breakdownAddress(uint16_t address, uint16_t& tag, uint8_t& line, uint8_t& offset) {
    offset = address & 0x7;          // Last 3 bits
    line = (address >> 3) & 0x7;     // Next 3 bits
    cacheLine = (address >> 6);       // Remaining 10 bits
}
```

### Cache Operations

#### Load Operation (LDR)
```cpp
if (cacheHit) {
    // Read from cache
    dataValue = (cache[cacheLine].data[offset] << 8) | 
                cache[cacheLine].data[offset + 1];
    registers[reg] = dataValue;
} else {
    // Cache miss - load block from RAM
    // Write back dirty line if necessary
    if (cache[cacheLine].valid && cache[cacheLine].modified) {
        // Write cache line back to RAM
    }
    // Load new block from RAM to cache
    // Read requested data
}
```

#### Store Operation (STR)
```cpp
if (cacheHit) {
    // Write to cache and mark as modified
    cache[cacheLine].data[offset] = (dataValue >> 8) & 0xFF;
    cache[cacheLine].data[offset + 1] = dataValue & 0xFF;
    cache[cacheLine].modified = true;
} else {
    // Cache miss - load block first, then write
    // Similar to load miss handling
}
```

## Learning Outcomes

### Memory System Concepts
- **Cache Organization** - Direct-mapped cache structure and operation
- **Memory Hierarchy** - Relationship between cache and main memory
- **Address Translation** - Breaking down addresses into components
- **Cache Policies** - Write-back and write-through strategies

### Computer Architecture Fundamentals
- **Memory Access Patterns** - Understanding cache hit/miss behavior
- **Data Alignment** - 2-byte alignment requirements for 16-bit data
- **Byte Ordering** - Big-endian vs. little-endian data formats
- **Performance Implications** - Impact of cache organization on performance

### C++ Programming Skills
- **Bit Manipulation** - Address decoding and data formatting
- **File I/O** - Reading instruction and memory initialization files
- **Data Structures** - Struct usage for cache line representation
- **Command-Line Parsing** - Processing program arguments
- **Hexadecimal Output** - Formatted display of memory contents

## File Formats

### Instruction File Format
```
<operation> <register> <address>
<operation> <register> <address>
...
```

Operations:
- **LDR**: Load register from memory
- **STR**: Store register to memory

Example:
```
LDR 0 1000
STR 1 1002
LDR 2 1004
```

### RAM Initialization File Format
```
<address> <byte0> <byte1> <byte2> ... <byte15>
<address> <byte0> <byte1> <byte2> ... <byte15>
...
```

Example:
```
0000 12 34 56 78 9A BC DE F0 11 22 33 44 55 66 77 88
0010 AB CD EF 01 23 45 67 89 FE DC BA 98 76 54 32 10
```

## Build Instructions

```bash
cd proj07/
make
./proj07 -input test_instructions.txt -ram initial_ram.txt -debug
```

## File Structure

```
proj07/
├── proj07.cpp              # Main cache simulator
├── CSE325_Assignment7.pdf  # Project specification
├── proj07_tests.py         # Test suite
└── README.md              # Project documentation
```

## Testing Examples

### Basic Cache Operations
```bash
# Create test instructions
echo "LDR 0 0000" > instructions.txt
echo "STR 0 1000" >> instructions.txt
echo "LDR 1 1000" >> instructions.txt

./proj07 -input instructions.txt
```

### Cache Miss Testing
```bash
# Create instructions that will cause cache misses
echo "LDR 0 0000" > miss_test.txt
echo "LDR 1 2000" >> miss_test.txt  # Different cache line
echo "LDR 2 4000" >> miss_test.txt  # Another cache line

./proj07 -input miss_test.txt -debug
```

### Write-Back Testing
```bash
# Test write-back on cache line eviction
echo "STR 0 0000" > wb_test.txt
echo "STR 1 2000" >> wb_test.txt  # Different line
echo "STR 2 4000" >> wb_test.txt  # Evicts first line

./proj07 -input wb_test.txt -ram initial_ram.txt
```

## Technical Details

### Cache Mapping
- **Cache Size**: 64 bytes (8 lines × 8 bytes)
- **Associativity**: Direct-mapped (1-way set associative)
- **Block Size**: 8 bytes
- **Replacement Policy**: None (direct mapping)
- **Write Policy**: Write-back with write-allocate

### Address Space
- **Total Addressable Memory**: 64KB (0x0000 - 0xFFFF)
- **Cacheable Addresses**: All 64KB
- **Alignment Requirements**: 2-byte alignment for 16-bit data
- **Byte Ordering**: Big-endian (MSB first)

### Performance Characteristics
- **Cache Hit Time**: 1 cycle (simulated)
- **Cache Miss Penalty**: Multiple cycles (simulated)
- **Memory Access Time**: Variable based on location
- **Hit Rate**: Depends on access pattern

## Educational Value

### Computer Architecture Understanding
- **Memory Hierarchy** - Foundation for understanding modern memory systems
- **Cache Design** - Basic principles of cache organization and operation
- **Performance Analysis** - Impact of memory system design on performance
- **Trade-off Analysis** - Balancing cache size, associativity, and complexity

### Systems Programming Skills
- **Low-Level Programming** - Understanding hardware-software interface
- **Memory Management** - Direct memory access and manipulation
- **Debugging Techniques** - Debugging memory-related issues
- **Performance Tuning** - Optimizing memory access patterns

### Problem-Solving Approach
- **System Design** - Designing memory subsystems for specific requirements
- **Algorithm Implementation** - Implementing cache replacement and mapping algorithms
- **Testing Methodology** - Comprehensive testing of memory system behavior
- **Documentation** - Clear documentation of system design and operation

## Real-World Applications

### Computer System Design
- **Processor Architecture** - Understanding CPU cache design principles
- **Embedded Systems** - Memory system design for resource-constrained devices
- **High-Performance Computing** - Cache optimization for scientific computing
- **System-on-Chip Design** - On-chip memory hierarchy design

### Software Optimization
- **Compiler Design** - Code generation with cache awareness
- **Performance Analysis** - Memory profiling and optimization tools
- **Algorithm Design** - Cache-conscious algorithm development
- **System Software** - Operating system memory management

### Research and Education
- **Architecture Research** - Foundation for advanced memory system research
- **Teaching Tool** - Educational tool for computer architecture courses
- **Simulation Frameworks** - Basis for more complex architectural simulators
- **Performance Modeling** - Modeling memory system performance characteristics

---

*This cache simulator project provides hands-on experience with fundamental memory system concepts essential for understanding modern computer architecture and performance optimization.*
