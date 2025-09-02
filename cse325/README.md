# CSE 325 - Computer Architecture

This directory contains projects from CSE 325, focusing on computer architecture concepts, memory systems, performance analysis, and hardware-software interaction using C++.

## Course Overview

CSE 325 explores fundamental computer architecture concepts including:
- Memory addressing and hexadecimal arithmetic
- Computer organization and instruction set architecture
- Memory hierarchy and cache systems
- Performance analysis and optimization
- Hardware-software interface
- Network programming and distributed systems
- Modern computer architecture trends

## Project Directory

### [Project 1 - Memory Addressing](./proj01/)
**Skills:** Hexadecimal arithmetic, memory calculation, input validation

Implementation of memory addressing calculations and hexadecimal validation.

**Key Features:**
- Hexadecimal input validation
- Memory size calculations based on address width
- Command-line argument processing
- Error handling for invalid inputs

### [Project 2 - Core Architecture Concepts](./proj02/)
**Skills:** Computer organization fundamentals, C++ programming

Building foundational understanding of computer architecture principles.

### [Project 3 - Intermediate Architecture](./proj03/)
**Skills:** Advanced architecture concepts, system design

Implementation of intermediate-level architecture concepts and system design patterns.

### [Project 4 - Data Processing Systems](./proj04/)
**Skills:** File processing, data structures, algorithm optimization

Advanced data processing with file I/O operations and inventory management systems.

### [Project 5 - System Optimization](./proj05/)
**Skills:** Performance analysis, optimization techniques

Focus on system performance analysis and optimization strategies.

### [Project 6 - Cache Simulation](./proj06/)
**Skills:** Memory hierarchy, cache design, performance modeling

**Comprehensive cache memory simulator implementing:**

- **Cache Architecture**
  - 8-line direct-mapped cache with 8-byte blocks
  - Valid and modified bits for cache coherency
  - Tag-based address mapping system

- **Memory Hierarchy**
  - 65536-byte RAM simulation
  - Cache-to-memory data transfer
  - Write-back cache policy implementation

- **Address Breakdown**
  - 16-bit address space
  - Tag (10 bits), Line (3 bits), Offset (3 bits)
  - Efficient address parsing and validation

- **Instruction Processing**
  - LDR (Load Register) operations
  - STR (Store Register) operations
  - Debug mode with step-by-step execution

- **Performance Analysis**
  - Cache hit/miss tracking
  - Memory access pattern analysis
  - System state visualization

### [Project 7 - Advanced Architecture Topics](./proj07/)
**Skills:** Modern computer architecture, advanced optimization

Exploration of advanced computer architecture concepts and modern processor design.

### [Project 8 - Network Programming](./proj08/)
**Skills:** Client-server architecture, network protocols, distributed systems

**Distributed system implementation featuring:**

- **Client-Server Architecture**
  - Robust client-server communication
  - Network protocol implementation
  - Connection management and error handling

- **Concurrent Programming**
  - Multi-threaded server design
  - Client request handling
  - Resource synchronization

## Key Learning Outcomes

### Architecture Concepts Mastered
- **Memory Systems** - Understanding of cache hierarchies, memory mapping, and performance optimization
- **Instruction Set Architecture** - Knowledge of how software instructions translate to hardware operations
- **Performance Analysis** - Ability to analyze and optimize system performance
- **Hardware-Software Interface** - Deep understanding of how software interacts with hardware components
- **Computer Organization** - Comprehensive knowledge of CPU design and system organization

### Programming Skills Developed
- **C++ Proficiency** - Modern C++ features, STL usage, object-oriented design
- **System Programming** - Low-level programming concepts applied to architecture simulation
- **Network Programming** - Client-server development and distributed system design
- **Performance Optimization** - Code optimization techniques for systems programming
- **Testing and Validation** - Comprehensive testing frameworks for complex systems

### Tools and Technologies
- **Development Environment** - C++ compilation, debugging, and profiling tools
- **Memory Analysis** - Tools for memory usage analysis and optimization
- **Performance Profiling** - Techniques for measuring and improving system performance
- **Network Tools** - Socket programming and network debugging utilities

## Project Highlights

### Cache Simulator (Project 6)
The cache simulation project represents a comprehensive implementation of computer memory hierarchy concepts:

- **Technical Achievement** - Complete cache memory system with all standard features
- **Educational Value** - Demonstrates deep understanding of memory hierarchy design
- **Practical Application** - Real-world relevant cache optimization techniques
- **Code Quality** - Well-structured, documented, and maintainable implementation

### Network Programming (Project 8)
The client-server project showcases distributed systems programming:

- **Scalability** - Multi-client server architecture
- **Reliability** - Robust error handling and connection management
- **Performance** - Efficient communication protocols and resource management

## Development Environment

- **Language:** C++ (C++11/14/17 features)
- **Compiler:** G++ with optimization flags
- **Build System:** Make with dependency management
- **Platform:** Linux/Unix systems
- **Testing:** Custom test frameworks and validation scripts
- **Documentation:** Comprehensive inline documentation and project reports

## Project Structure

Standard project organization:
```
proj##/
├── Makefile              # Build configuration
├── proj##.cpp           # Main implementation
├── [additional-files]   # Supporting files and headers
├── test-inputs/         # Test cases and validation data
├── documentation/       # Project reports and analysis
└── README.md           # Project-specific documentation
```

## Performance Considerations

Each project emphasizes:
- **Algorithm Efficiency** - Optimal time and space complexity
- **Memory Management** - Careful resource allocation and cleanup
- **Code Optimization** - Compiler optimizations and manual optimizations
- **Scalability** - Design for larger datasets and extended functionality
- **Maintainability** - Clean, readable, and extensible code

## Getting Started

To build and run projects:

```bash
cd proj##/
make clean && make
./proj##
```

For projects with special requirements:
```bash
# Project 6 (Cache Simulator)
./proj06 -input instructions.txt -ram initial_ram.txt -debug

# Project 8 (Client-Server)
# Terminal 1 (Server)
./proj08.server

# Terminal 2 (Client)
./proj08.client
```

## Academic Rigor

These projects demonstrate:
- **Theoretical Understanding** - Solid grasp of computer architecture principles
- **Practical Implementation** - Ability to translate theory into working code
- **Problem-Solving Skills** - Creative solutions to complex technical challenges
- **Professional Development** - Industry-standard coding practices and documentation

---

*This coursework provides a comprehensive foundation in computer architecture concepts essential for systems programming, performance optimization, and hardware-software co-design.*
