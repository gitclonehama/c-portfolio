# Process Scheduler Simulator

Basic operating system process scheduling simulation demonstrating priority-based scheduling, time slicing, and process state management.

## Project Overview

This project implements a simple process scheduler simulator in C++ that demonstrates fundamental operating system concepts. The program simulates process execution with priority scheduling, time quantum management, and blocking operations.

## Key Features

- **Priority-Based Scheduling** - Higher priority processes execute first
- **Time Slicing** - 5-instruction time quantum with preemption
- **Process States** - READY, RUNNING, BLOCKED, TERMINATED states
- **Blocking Operations** - NETWORK and I/O system calls with duration
- **Event Logging** - Comprehensive logging of process state transitions

## Command-Line Usage

```bash
# Run simulation with 3 processes
./proj03 3

# The program expects process files: process1, process2, process3
```

## Implementation Details

### Process Management

The simulator uses a `Process` class to represent each process:

```cpp
class Process {
private:
    int pid;                    // Process ID
    int priority;               // Process priority
    State state;                // Current state (READY/RUNNING/BLOCKED/TERMINATED)
    queue<string> instructions; // Instruction queue
    int unblockTime;           // Time when blocked process becomes ready
};
```

### Scheduling Algorithm

The scheduler implements priority-based scheduling with round-robin time slicing:

```cpp
// Sort ready queue by priority (higher priority first)
void sortReadyQueue() {
    sort(readyQueue.begin(), readyQueue.end(), [](Process* a, Process* b) {
        return a->getPriority() > b->getPriority();
    });
}
```

### Process States and Transitions

The simulator manages four process states:
- **READY** - Process is waiting for CPU time
- **RUNNING** - Process is currently executing
- **BLOCKED** - Process is waiting for I/O or network operation
- **TERMINATED** - Process has completed execution

### Time Management

- **Global Time** - Incremented on each instruction execution
- **Time Slice** - 5 normal instructions per time quantum
- **Unblock Time** - Calculated as current time + blocking duration

```cpp
// Timer interrupt after 5 normal instructions
if (currentTimeSlice == 5) {
    logEvent("Hardware Interrupt: Timer interval");
    // Preempt current process
}
```

## Learning Outcomes

### Operating System Concepts
- **Process Scheduling** - Understanding of different scheduling algorithms
- **Process States** - State transitions in operating systems
- **Time Sharing** - CPU time division among multiple processes
- **System Calls** - Blocking vs. non-blocking operations

### C++ Programming Skills
- **Object-Oriented Design** - Class design and encapsulation
- **Data Structures** - Queues, vectors, and state management
- **File I/O** - Reading process definition files
- **String Processing** - Parsing instruction and system call strings

### System Programming
- **Process Management** - Simulating OS process control
- **Event Handling** - Managing asynchronous events and interrupts
- **Logging Systems** - Output formatting and file writing
- **Resource Management** - Memory cleanup and process termination

## Process File Format

Each process is defined in a separate file (process1, process2, etc.):

```
<priority>
<instruction1>
<instruction2>
SYS_CALL, NETWORK 10
<instruction3>
SYS_CALL, I/O 5
SYS_CALL, TERMINATE
```

### Example Process File

```
3
COMPUTE
CALCULATE
SYS_CALL, NETWORK 8
STORE_RESULT
SYS_CALL, TERMINATE
```

## Build Instructions

```bash
cd proj03/
make
./proj03 2  # Run with 2 processes
```

## File Structure

```
proj03/
├── proj03.cpp         # Main scheduler implementation
└── README.md          # Project documentation
```

## Testing Examples

### Single Process Execution
```bash
# Create process1 file
echo "5" > process1
echo "COMPUTE" >> process1
echo "CALCULATE" >> process1
echo "SYS_CALL, TERMINATE" >> process1

./proj03 1
```

### Multiple Process Scheduling
```bash
# Process 1 (high priority)
echo "8" > process1
echo "COMPUTE_A" >> process1
echo "SYS_CALL, NETWORK 3" >> process1
echo "SYS_CALL, TERMINATE" >> process1

# Process 2 (lower priority)
echo "3" > process2
echo "COMPUTE_B" >> process2
echo "SYS_CALL, I/O 2" >> process2
echo "SYS_CALL, TERMINATE" >> process2

./proj03 2
```

### Output Analysis
The program generates both console output and a LOG.txt file showing:
- Process state transitions
- Instruction executions
- System calls
- Timer interrupts
- Blocking and unblocking events

## Technical Details

### Scheduling Logic
- **Priority Queue** - Ready processes sorted by priority
- **Round Robin** - Time slicing within same priority level
- **Preemption** - Higher priority processes can preempt lower ones
- **Non-Preemptive Blocking** - Blocking calls don't trigger preemption

### System Call Handling
```cpp
if (type == "NETWORK" || type == "I/O") {
    int duration = stoi(param);
    process->setUnblockTime(globalTime + duration);
    // Move to blocked queue
}
```

### Memory Management
- **Dynamic Allocation** - Process objects created with `new`
- **Cleanup** - Proper deletion when processes terminate
- **Resource Tracking** - Queues manage process lifecycle

## Educational Value

### Operating Systems Fundamentals
- **Process Management** - Core OS process control mechanisms
- **Scheduling Algorithms** - Different approaches to CPU allocation
- **Concurrency** - Managing multiple simultaneous activities
- **System Calls** - Interface between user programs and OS kernel

### Programming Methodology
- **Simulation Design** - Modeling complex systems in software
- **State Machines** - Implementing state-based logic
- **Event-Driven Programming** - Handling asynchronous events
- **Logging and Debugging** - System monitoring and troubleshooting

### Problem-Solving Skills
- **System Design** - Designing software to model real systems
- **Algorithm Implementation** - Translating concepts to working code
- **Testing and Validation** - Verifying correct system behavior
- **Performance Analysis** - Understanding scheduling efficiency

## Real-World Applications

### Operating System Development
- **Kernel Design** - Understanding OS kernel architecture
- **Process Control** - Implementing process management in OS
- **Scheduling Systems** - Real-world CPU scheduling algorithms
- **System Monitoring** - Process state tracking and logging

### Embedded Systems
- **RTOS Design** - Real-time operating system concepts
- **Task Scheduling** - Managing tasks in embedded applications
- **Interrupt Handling** - Hardware interrupt processing
- **Resource Management** - Memory and CPU resource allocation

### Performance Analysis
- **Scheduling Efficiency** - Measuring scheduler performance
- **Process Behavior** - Analyzing process execution patterns
- **System Utilization** - CPU and resource usage metrics
- **Bottleneck Identification** - Finding system performance issues

---

*This project provides hands-on experience with operating system process scheduling concepts, essential for understanding how modern operating systems manage multiple processes and system resources.*
