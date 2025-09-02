# File Copy Utility

Basic file copying program with command-line options for buffer size and file handling modes.

## Project Overview

This project implements a simple file copy utility in C++ that demonstrates basic file I/O operations using Unix system calls. The program supports configurable buffer sizes and different file handling modes (append/truncate).

## Key Features

- **Configurable Buffer Size** - User-specified buffer size for file copying
- **File Mode Options** - Append mode (-a) and truncate mode (-t) support
- **Error Handling** - Comprehensive error checking for file operations
- **Command-Line Interface** - Flexible command-line argument parsing

## Command-Line Usage

```bash
# Basic file copy
./proj02 source.txt destination.txt

# Copy with custom buffer size
./proj02 source.txt destination.txt -b 1024

# Append to existing file
./proj02 source.txt destination.txt -a

# Truncate existing file
./proj02 source.txt destination.txt -t

# Combined options
./proj02 source.txt destination.txt -b 512 -a
```

## Implementation Details

### Command-Line Argument Processing

The program parses command-line arguments to extract:
- Source and destination file names
- Buffer size (-b option)
- File handling modes (-a for append, -t for truncate)

```cpp
// Argument parsing logic
for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    
    if (arg == "-b") {
        // Parse buffer size
        buffSize = std::stoi(argv[++i]);
    }
    else if (arg == "-a") {
        aMode = true;
    }
    else if (arg == "-t") {
        tMode = true;
    }
    else {
        // File name argument
        if (fileIn.empty()) {
            fileIn = arg;
        } else if (fileOut.empty()) {
            fileOut = arg;
        }
    }
}
```

### File Operations

The program uses Unix system calls for file operations:
- `open()` - Open source file for reading
- `read()` - Read data in configurable buffer sizes
- `write()` - Write data to destination file
- `close()` - Close file descriptors

```cpp
// File copying with buffer
std::vector<char> buffer(buffSize);
while ((readBytes = read(inFD, buffer.data(), buffSize)) > 0) {
    write(outFD, buffer.data(), readBytes);
}
```

### Error Handling

Comprehensive error checking includes:
- Missing command-line arguments
- Invalid buffer size values
- File access permission issues
- File operation failures
- Resource cleanup on errors

## Learning Outcomes

### System Programming Skills
- **Unix System Calls** - Using low-level file operations
- **File Descriptors** - Managing file handles and permissions
- **Error Handling** - Proper error checking and reporting
- **Resource Management** - Cleaning up file descriptors

### C++ Programming Techniques
- **Command-Line Parsing** - Processing program arguments
- **String Manipulation** - Working with C++ strings and C strings
- **Vector Usage** - Dynamic buffer management
- **Input Validation** - Checking user input for correctness

### File System Concepts
- **File Permissions** - Understanding Unix file permissions
- **File Modes** - Different file opening modes (read, write, append)
- **Buffer Management** - Memory-efficient file copying
- **Error Conditions** - Handling various file system errors

## Build Instructions

```bash
cd proj02/
make
./proj02 source.txt dest.txt -b 1024
```

## File Structure

```
proj02/
├── proj02.cpp         # Main file copy implementation
├── Makefile          # Build configuration
└── README.md         # Project documentation
```

## Testing Examples

### Basic Functionality
```bash
# Test basic file copy
echo "Hello World" > test.txt
./proj02 test.txt copy.txt
cat copy.txt  # Should show "Hello World"

# Test buffer size impact
./proj02 large_file.txt dest.txt -b 4096
./proj02 large_file.txt dest.txt -b 64
```

### Error Conditions
```bash
# Missing arguments
./proj02

# Invalid buffer size
./proj02 file1.txt file2.txt -b abc

# File doesn't exist
./proj02 nonexistent.txt dest.txt

# Permission denied
./proj02 /etc/passwd dest.txt
```

### Mode Testing
```bash
# Create initial file
echo "Line 1" > test.txt

# Test append mode
echo "Line 2" | ./proj02 - test.txt -a
cat test.txt  # Should show both lines

# Test truncate mode
echo "New content" | ./proj02 - test.txt -t
cat test.txt  # Should show only "New content"
```

## Technical Details

### Buffer Size Considerations
- **Small Buffers** - More system calls, better for small files
- **Large Buffers** - Fewer system calls, better for large files
- **Memory Usage** - Buffer size affects memory consumption
- **Performance Trade-offs** - Balance between memory and I/O efficiency

### File Mode Logic
- **Default Behavior** - Refuses to overwrite existing files
- **Append Mode** - Adds content to end of existing file
- **Truncate Mode** - Replaces existing file content
- **Safety Checks** - Prevents accidental data loss

## Educational Value

This project teaches:
- **System-Level Programming** - Direct interaction with operating system
- **File I/O Operations** - Low-level file handling techniques
- **Command-Line Interfaces** - Building user-friendly CLI programs
- **Error Handling** - Robust error management in C++
- **Resource Management** - Proper cleanup of system resources

---

*This project provides hands-on experience with Unix system calls and file operations, essential for systems programming and understanding operating system interfaces.*
