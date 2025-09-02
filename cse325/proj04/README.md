# Inventory Management System with Threading

**Skills:** Multi-threading, file I/O, data structures, process synchronization, C++ programming

## Project Overview

Multi-threaded inventory management system that processes customer orders and updates inventory using producer-consumer pattern with pthread library. Demonstrates concurrent programming concepts and file processing.

## Implementation

### Core Components

#### Data Structures
```cpp
struct InventoryItem {
    unsigned int productID;
    double price;
    unsigned int stock;
    string description;
};

struct Order {
    unsigned int customerID;
    unsigned int productID;
    unsigned int quantity;
};
```

#### Threading Model
- **Producer Thread** - Reads orders from file and stores in vector
- **Consumer Thread** - Processes orders and updates inventory
- **Main Thread** - Coordinates execution and handles file I/O

### Key Features

#### File Processing
- **Inventory Loading** - Reads product data from `inventory.old`
- **Order Processing** - Reads customer orders from `orders` file
- **Inventory Saving** - Writes updated inventory to `inventory.new`
- **Transaction Logging** - Records all transactions in `log` file

#### Thread Synchronization
- **Producer-Consumer Pattern** - Sequential execution using pthread_join
- **Data Sharing** - Global data structures for inventory and orders
- **Error Handling** - Thread-safe error reporting and validation

#### Transaction Processing
- **Stock Validation** - Checks if sufficient quantity available
- **Order Fulfillment** - Updates inventory on successful orders
- **Order Rejection** - Logs rejected orders with reason
- **Financial Tracking** - Calculates transaction amounts

## Usage

```bash
# Build the program
make

# Run with input files
./proj04
# Expects: inventory.old and orders files in current directory
# Produces: inventory.new and log files
```

### Input File Formats

**inventory.old:**
```
100492 2.50 360 Northern Red Oak
201005 10.17 62 Shagbark Hickory
100305 1.95 1043 Sugar Maple
```

**orders:**
```
9981532 100305 65
9981532 100492 40
0003183 100305 100
```

### Output Files

**inventory.new:** Updated inventory with remaining stock
**log:** Transaction history with formatted output

## Technical Skills Demonstrated

- **Multi-threading** - pthread library usage and thread management
- **File I/O** - Reading and writing structured data files
- **Data Structures** - STL containers (map, vector) for data organization
- **Process Synchronization** - Coordinating thread execution
- **Error Handling** - Input validation and error reporting
- **String Formatting** - Precise output formatting with iomanip

## Educational Outcomes

### Concurrent Programming
- Understanding of producer-consumer design pattern
- Thread creation, execution, and synchronization
- Shared data access and thread safety considerations
- Error handling in multi-threaded environments

### Systems Programming
- File handling and data persistence
- Memory management with STL containers
- Process coordination and workflow management
- Input validation and robust error checking

---

*Demonstrates foundational understanding of concurrent programming and file processing in C++.*
