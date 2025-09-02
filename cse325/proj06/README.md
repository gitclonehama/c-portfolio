# Cache Memory Simulator

**Skills:** Computer architecture, cache design, address translation, memory hierarchy, C++ programming

## Project Overview

Cache memory simulation implementing basic cache operations with address parsing and instruction processing. Demonstrates understanding of computer architecture concepts including cache design, memory hierarchy, and address translation.

## System Architecture

### Cache Specifications
- **Architecture Type:** Direct-mapped cache simulation
- **Cache Size:** 8 lines × 8 bytes = 64 bytes total
- **Block Size:** 8 bytes per cache line
- **Address Space:** 16-bit addressing (65,536 bytes)
- **Cache State:** Valid and modified bits per cache line

### Memory Components
- **Cache:** 8-line direct-mapped with 8-byte blocks
- **Main Memory:** 65,536-byte RAM array
- **Registers:** 16 registers (R0-RF) of 16 bits each
- **Address Mapping:** Tag (10 bits) + Line (3 bits) + Offset (3 bits)

## Implementation Details

### Cache Line Structure
```cpp
struct CacheLine {
    bool valid;       // Valid bit (1 if data is valid)
    bool modified;    // Modified bit (1 if data has been changed)
    uint16_t tag;     // Tag bits (10 bits)
    uint8_t data[8];  // 8-byte data block
};
```

### Address Translation
```cpp
void breakdownAddress(uint16_t address, uint16_t& tag, uint8_t& line, uint8_t& offset) {
    offset = address & 0x7;          // Last 3 bits (byte offset)
    line = (address >> 3) & 0x7;     // Next 3 bits (cache line)
    tag = address >> 6;              // Remaining 10 bits (tag)
}
```

## Key Features

### Address Translation System
```cpp
void breakdownAddress(uint16_t address, uint16_t& tag, uint8_t& line, uint8_t& offset) {
    offset = address & 0x7;          // Last 3 bits (byte offset)
    line = (address >> 3) & 0x7;     // Next 3 bits (cache line)
    tag = address >> 6;              // Remaining 10 bits (tag)
}
```

**Address Breakdown Example:**
- Address: `0x1A3F` (binary: 0001101000111111)
- Tag: `0x068` (bits 15-6: 0001101000)
- Line: `7` (bits 5-3: 111)
- Offset: `7` (bits 2-0: 111)

### Instruction Processing

#### LDR (Load Register) Operation
1. Parse instruction format: `LDR <register> <address>`
2. Break down address into tag, line, and offset
3. Check cache for hit/miss condition
4. Handle cache miss with memory fetch
5. Update register with loaded value

#### STR (Store Register) Operation
1. Parse instruction format: `STR <register> <address>`
2. Perform address translation
3. Check cache status and handle accordingly
4. Write data to cache and set modified bit
5. Update memory hierarchy as needed

### Advanced Features

#### Debug Mode
- **Step-by-step execution** - Detailed trace of each instruction
- **State visualization** - Complete system state after each operation
- **Cache analysis** - Hit/miss tracking and performance metrics
- **Memory inspection** - Full memory and register dumps

#### Performance Monitoring
- **Cache hit rate calculation**
- **Memory access pattern analysis**
- **Instruction execution statistics**
- **System bottleneck identification**

## Implementation Highlights

### Memory Management
```cpp
// RAM initialization from file
int loadRamFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        uint16_t address;
        
        if (!(iss >> std::hex >> address)) continue;
        
        // Read 16 bytes of data per line
        for (int i = 0; i < 16; i++) {
            uint16_t value;
            if (iss >> std::hex >> value) {
                ram[address + i] = static_cast<uint8_t>(value);
            }
        }
    }
    return 0;
}
```

### Cache Visualization
```cpp
void displayCache() {
    std::cout << "\nDATA CACHE" << std::endl;
    std::cout << "     V M Tag  0  1  2  3  4  5  6  7" << std::endl;
    std::cout << "____________________________________" << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << "[" << std::hex << i << "]: "
                  << (cache[i].valid ? "1" : "0") << " "
                  << (cache[i].modified ? "1" : "0") << " "
                  << std::setfill('0') << std::setw(3) << cache[i].tag << "  ";
        
        for (int j = 0; j < 8; j++) {
            std::cout << std::setfill('0') << std::setw(2) 
                      << static_cast<int>(cache[i].data[j]) << " ";
        }
        std::cout << std::endl;
    }
}
```

## Usage Examples

### Basic Execution
```bash
./proj06 -input instructions.txt
```

### With Initial RAM State
```bash
./proj06 -input instructions.txt -ram initial_memory.txt
```

### Debug Mode Execution
```bash
./proj06 -input instructions.txt -ram initial_memory.txt -debug
```

### Sample Instruction File
```
LDR 0 1A3F
STR 1 2B48
LDR 2 1A40
STR 0 3C59
```

### Sample RAM File
```
0000: 12 34 56 78 9A BC DE F0 11 22 33 44 55 66 77 88
0010: AA BB CC DD EE FF 00 11 22 33 44 55 66 77 88 99
```

## Performance Analysis

### Cache Performance Metrics
- **Hit Rate:** Percentage of memory accesses satisfied by cache
- **Miss Rate:** Percentage of memory accesses requiring main memory
- **Average Access Time:** Weighted average of cache and memory access times
- **Throughput:** Instructions processed per unit time

### Memory Access Patterns
- **Spatial Locality:** Effectiveness of block-based caching
- **Temporal Locality:** Benefit of keeping recently accessed data in cache
- **Working Set Analysis:** Memory usage patterns over time

## Educational Outcomes

### Computer Architecture Mastery
- **Memory Hierarchy Design** - Deep understanding of cache organization and operation
- **Address Translation** - Comprehensive knowledge of virtual to physical address mapping
- **Cache Coherency** - Implementation of cache consistency protocols
- **Performance Optimization** - Techniques for maximizing memory system performance

### Systems Programming Skills
- **Low-Level Programming** - Direct hardware simulation and modeling
- **Data Structure Design** - Efficient implementation of complex system components
- **File I/O Operations** - Robust handling of configuration and data files
- **Error Handling** - Comprehensive error checking and graceful failure modes

### Software Engineering Practices
- **Modular Design** - Clean separation of concerns and functionality
- **Documentation** - Comprehensive code comments and user documentation
- **Testing Strategy** - Systematic validation of complex system behavior
- **Performance Profiling** - Analysis and optimization of system performance

## File Structure

```
proj06/
├── proj06.cpp              # Complete cache simulator implementation
├── Makefile               # Build configuration and optimization flags
├── instructions.txt       # Sample instruction sequences
├── initial_memory.txt     # Sample RAM initialization data
├── test_cases/           # Comprehensive test suite
│   ├── basic_tests.txt
│   ├── performance_tests.txt
│   └── edge_cases.txt
└── documentation/
    ├── design_analysis.pdf
    └── performance_report.pdf
```

## Advanced Concepts Demonstrated

### Cache Optimization Techniques
- **Write-Back Policy** - Delayed write operations for performance
- **Valid Bit Management** - Efficient cache line state tracking
- **Tag Comparison** - Fast hit/miss determination
- **Block Replacement** - Direct-mapped replacement strategy

### System Design Principles
- **Modularity** - Separate functions for distinct operations
- **Extensibility** - Design allowing for easy feature additions
- **Maintainability** - Clean, well-documented code structure
- **Testability** - Comprehensive testing and validation framework

## Real-World Applications

### Industry Relevance
- **Processor Design** - Understanding of real CPU cache implementations
- **System Optimization** - Skills applicable to performance tuning
- **Embedded Systems** - Memory hierarchy optimization for resource-constrained environments
- **High-Performance Computing** - Cache-aware algorithm design

### Academic Foundation
- **Graduate Studies** - Preparation for advanced computer architecture courses
- **Research Projects** - Foundation for memory system research
- **Industry Internships** - Practical skills for systems engineering roles

---

*This cache simulation project demonstrates comprehensive understanding of computer architecture principles and provides practical experience with the memory hierarchy concepts that underlie all modern computing systems.*
