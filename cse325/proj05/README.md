# Multi-threaded Order Processing System

Producer-consumer implementation for processing customer orders against an inventory system using POSIX threads and semaphores for synchronization.

## Project Overview

This project implements a classic producer-consumer problem using multiple threads to process customer orders. Producer threads read orders from files and place them in a bounded buffer, while a consumer thread processes these orders, updates inventory, and logs transactions.

## Key Features

- **Multi-threaded Processing** - Multiple producer threads and one consumer thread
- **Bounded Buffer** - Circular buffer with configurable size for order queuing
- **Semaphore Synchronization** - Proper synchronization using POSIX semaphores
- **Inventory Management** - Loading, updating, and saving inventory data
- **Transaction Logging** - Comprehensive logging of all order processing results
- **Error Handling** - Robust error handling for file operations and thread management

## Command-Line Usage

```bash
# Basic usage with defaults (1 producer, buffer size 10)
./proj05

# Specify number of producers and buffer size
./proj05 -p 3 -b 20

# Options:
# -p <num> : Number of producer threads (1-9, default: 1)
# -b <size> : Buffer size (1-30, default: 10)
```

## Implementation Details

### Data Structures

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
    bool isEndMarker;  // Signals end of producer's orders
    int producerID;    // Tracks which producer created the order
};
```

### Synchronization Mechanism

The program uses three semaphores for thread synchronization:

```cpp
sem_t emptySlots;  // Counts available buffer slots
sem_t full;        // Counts filled buffer slots  
sem_t mutex;       // Binary semaphore for mutual exclusion
```

### Producer Thread Logic

```cpp
void* ProducerFunction(void* arg) {
    // Read orders from file (orders1, orders2, etc.)
    while (file >> customerID >> productID >> quantity) {
        Order order = {customerID, productID, quantity, false, producerID};
        
        // Wait for empty slot, then add to buffer
        sem_wait(&emptySlots);
        sem_wait(&mutex);
        
        buffer[in] = order;
        in = (in + 1) % bufferSize;
        count++;
        
        sem_post(&mutex);
        sem_post(&full);
    }
    
    // Insert end marker to signal completion
    // ...
}
```

### Consumer Thread Logic

```cpp
void* ConsumerFunction(void* arg) {
    int producersFinished = 0;
    
    while (producersFinished < numProducers) {
        // Wait for filled slot, then remove from buffer
        sem_wait(&full);
        sem_wait(&mutex);
        
        Order order = buffer[out];
        out = (out + 1) % bufferSize;
        count--;
        
        sem_post(&mutex);
        sem_post(&emptySlots);
        
        // Process order: check inventory, update stock, log transaction
        // ...
    }
}
```

## Learning Outcomes

### Multi-threading Concepts
- **Producer-Consumer Problem** - Classic synchronization problem implementation
- **Thread Synchronization** - Using semaphores for mutual exclusion and condition synchronization
- **Race Conditions** - Understanding and preventing concurrent access issues
- **Deadlock Prevention** - Proper ordering of semaphore operations

### C++ Programming Skills
- **POSIX Threads** - Creating and managing threads with pthreads
- **Semaphore Operations** - Using sem_wait() and sem_post() for synchronization
- **File I/O** - Reading from multiple input files and writing output files
- **Data Structures** - Using maps for inventory storage and circular buffers
- **Error Handling** - Thread-safe error reporting and handling

### System Programming
- **Process Synchronization** - Inter-thread communication and coordination
- **Memory Management** - Dynamic allocation and cleanup of shared resources
- **File System Operations** - Reading inventory files and writing transaction logs
- **Command-Line Parsing** - Processing program arguments and validation

## File Formats

### Inventory File (inventory.old)
```
<productID> <price> <stock> <description>
<productID> <price> <stock> <description>
...
```

Example:
```
1001 29.99 50 Wireless Mouse
1002 15.50 100 USB Cable
1003 89.99 25 Mechanical Keyboard
```

### Order Files (orders1, orders2, etc.)
```
<customerID> <productID> <quantity>
<customerID> <productID> <quantity>
...
```

Example (orders1):
```
12345 1001 2
67890 1002 1
12345 1003 1
```

### Transaction Log (log)
```
<customerID> <productID> <description> <quantity> <amount> <status>
```

Example:
```
0012345 001001 Wireless Mouse               00002  $059.98 filled
0067890 001002 USB Cable                   00001  $015.50 filled
0012345 001003 Mechanical Keyboard         00001  $000.00 rejected
```

## Build Instructions

```bash
cd proj05/
make
./proj05 -p 2 -b 15
```

## File Structure

```
proj05/
├── proj05.cpp         # Main producer-consumer implementation
├── Makefile          # Build configuration
└── README.md         # Project documentation
```

## Testing Examples

### Single Producer Test
```bash
# Create test inventory
echo "1001 10.00 5 Test Item 1" > inventory.old
echo "1002 20.00 3 Test Item 2" >> inventory.old

# Create test orders
echo "123 1001 2" > orders1
echo "456 1002 1" >> orders1

# Run with single producer
./proj05 -p 1 -b 5
```

### Multiple Producer Test
```bash
# Producer 1 orders
echo "111 1001 1" > orders1
echo "222 1002 2" >> orders1

# Producer 2 orders  
echo "333 1001 1" > orders2
echo "444 1002 1" >> orders2

# Run with two producers
./proj05 -p 2 -b 10
```

### Buffer Size Testing
```bash
# Test with small buffer (may cause blocking)
./proj05 -p 3 -b 3

# Test with larger buffer (less blocking)
./proj05 -p 3 -b 20
```

## Technical Details

### Circular Buffer Implementation
- **Fixed Size** - Configurable buffer size (1-30)
- **Thread-Safe** - Protected by mutex semaphore
- **Blocking Operations** - Producers block when buffer is full, consumer blocks when empty

### Synchronization Protocol
1. **Producer**: Wait for empty slot → acquire mutex → add item → release mutex → signal full slot
2. **Consumer**: Wait for full slot → acquire mutex → remove item → release mutex → signal empty slot

### End Marker System
- Each producer inserts an "end marker" when finished
- Consumer counts end markers to know when all producers are done
- Prevents consumer from waiting indefinitely

### Error Handling
- **File Errors** - Producer threads handle missing order files gracefully
- **Thread Creation** - Validates successful thread creation
- **Resource Cleanup** - Proper semaphore destruction and memory cleanup
- **Thread Safety** - Error reporting protected by mutex

## Educational Value

### Operating Systems Concepts
- **Concurrency** - Managing multiple threads of execution
- **Synchronization** - Coordinating access to shared resources
- **Process Communication** - Inter-thread communication patterns
- **Resource Management** - Managing shared buffers and system resources

### Programming Methodology
- **Modular Design** - Separating producer and consumer logic
- **Error Recovery** - Handling errors in multi-threaded environments
- **Testing Strategies** - Testing concurrent programs and synchronization
- **Performance Considerations** - Understanding buffer size impact on performance

### Professional Development
- **Multi-threaded Programming** - Essential skills for modern software development
- **System Programming** - Low-level programming with threads and synchronization
- **Debugging** - Debugging concurrent programs and race conditions
- **Code Quality** - Writing thread-safe, maintainable concurrent code

## Real-World Applications

### E-commerce Systems
- **Order Processing** - Processing customer orders in online stores
- **Inventory Management** - Real-time inventory tracking and updates
- **Transaction Logging** - Audit trails for financial transactions
- **Scalable Systems** - Handling multiple concurrent users

### Message Processing Systems
- **Message Queues** - Processing messages from multiple producers
- **Event Processing** - Handling events in distributed systems
- **Data Pipeline** - Processing data through multiple stages
- **Load Balancing** - Distributing work among processing units

### Database Systems
- **Transaction Processing** - Processing database transactions
- **Concurrency Control** - Managing concurrent database access
- **Logging Systems** - Transaction logging and recovery
- **Replication** - Synchronizing data across multiple nodes

---

*This project demonstrates fundamental concepts in concurrent programming and system design, providing essential skills for developing multi-threaded applications and understanding operating system principles.*
