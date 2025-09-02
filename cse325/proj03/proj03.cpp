#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Process States
enum State { READY, RUNNING, BLOCKED, TERMINATED };

class Process {
private:
    int pid;
    int priority;
    State state;
    queue<string> instructions;
    // The "unblockTime" is the global time (i.e. number of instructions executed) 
    // at which the process will become ready again.
    int unblockTime; 

public:
    Process(int id, int prio) : pid(id), priority(prio), state(READY), unblockTime(0) {}

    int getPID() const { return pid; }
    int getPriority() const { return priority; }
    State getState() const { return state; }
    bool hasInstructions() const { return !instructions.empty(); }
    // Returns and removes the next instruction.
    string getNextInstruction() {
        string inst = instructions.front();
        instructions.pop();
        return inst;
    }
    int getUnblockTime() const { return unblockTime; }

    void setState(State s) { state = s; }
    void setUnblockTime(int t) { unblockTime = t; }
    void addInstruction(const string &inst) { instructions.push(inst); }
};

// Global Data Structures
vector<Process*> readyQueue;    // Ready Queue
vector<Process*> blockedQueue;  // Blocked Queue
Process* runningProcess = nullptr;  // Currently Running Process

// Global time (counts the number of instructions executed)
int globalTime = 0;             
// Time slice counter for the currently running process (counts only normal instructions)
int currentTimeSlice = 0;       
ofstream logFile("LOG.txt");    // Log File Output

// Function Declarations
void loadProcesses(int numProcesses);
void simulateExecution();
/// executeInstruction returns true if a normal instruction was executed (and time advanced),
/// or false if the instruction was a blocking/terminating one.
bool executeInstruction(Process* process);
void handleBlockedProcesses();
void logEvent(const string &event);
void sortReadyQueue();


// Sort the ready queue by priority (higher priority first)
void sortReadyQueue() {
    sort(readyQueue.begin(), readyQueue.end(), [](Process* a, Process* b) {
        return a->getPriority() > b->getPriority();
    });
}

// Main function
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./proj03 <num_processes>" << endl;
        return 1;
    }
    string arg = argv[1];
    if (!all_of(arg.begin(), arg.end(), ::isdigit)) {
        cerr << "Error: Argument must be a number (e.g., ./proj03 3)" << endl;
        return 1;
    }
    int numProcesses = stoi(arg);
    loadProcesses(numProcesses);
    simulateExecution();
    logFile.close();
    return 0;
}

// Read process files (e.g., process1, process2, etc.) and load them into the ready queue.
void loadProcesses(int numProcesses) {
    for (int i = 1; i <= numProcesses; i++) {
        string filename = "process" + to_string(i);
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Could not open " << filename << endl;
            continue;
        }
        int priority;
        file >> priority;
        Process* process = new Process(i, priority);
        string line;
        getline(file, line); // consume the rest of the line after priority
        while (getline(file, line)) {
            if (!line.empty())
                process->addInstruction(line);
        }
        readyQueue.push_back(process);
        file.close();
    }
    sortReadyQueue();
}

// Main simulation loop.
// Note: globalTime is incremented on every instruction execution (normal or blocking).
// After a normal instruction execution, we call handleBlockedProcesses().
void simulateExecution() {
    // Continue until there are no processes left.
    while (!readyQueue.empty() || runningProcess || !blockedQueue.empty()) {
        // If no process is running, immediately select one from the ready queue.
        if (!runningProcess && !readyQueue.empty()) {
            runningProcess = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
            runningProcess->setState(RUNNING);
            currentTimeSlice = 0; // reset time slice counter
            logEvent("Process " + to_string(runningProcess->getPID()) + ": Ready -> Running");
        }
        // If a process is running, execute one instruction.
        if (runningProcess) {
            // executeInstruction returns true if a normal instruction was executed.
            bool normalExecuted = executeInstruction(runningProcess);
            // Only after a normal instruction do we check for unblocking.
            if (normalExecuted) {
                handleBlockedProcesses();
            }
        }
        // If no process is running but readyQueue is nonempty, simply loop (do not advance time).
    }
}

// executeInstruction executes one instruction from the running process.
// It returns true if the instruction was normal (i.e. time advances and unblocking is checked),
// or false if it was a blocking/termination instruction (or timer interrupt) so that time is not advanced again.
bool executeInstruction(Process* process) {
    if (!process->hasInstructions()) {
        logEvent("Process " + to_string(process->getPID()) + ": Running -> Halted");
        process->setState(TERMINATED);
        delete process;
        runningProcess = nullptr;
        return false;
    }
    
    string instruction = process->getNextInstruction();
    
    // Check if the instruction is a system call.
    if (instruction.find("SYS_CALL") != string::npos) {
        // Log the system call exactly as given.
        logEvent(instruction);
        // We'll parse the system call details.
        size_t commaPos = instruction.find(',');
        if (commaPos != string::npos) {
            string callDetail = instruction.substr(commaPos + 1);
            // Trim leading whitespace.
            callDetail.erase(0, callDetail.find_first_not_of(" \t"));
            stringstream ss(callDetail);
            string type;
            ss >> type;
            
            // For blocking calls (NETWORK or I/O), we increment time and then set unblockTime.
            if (type == "NETWORK" || type == "I/O") {
                string param;
                ss >> param;
                int duration = stoi(param);
                // Increment globalTime for this instruction.
                globalTime++;
                // Set unblockTime = current globalTime + duration.
                process->setUnblockTime(globalTime + duration);
                logEvent("Process " + to_string(process->getPID()) + ": Running -> Blocked");
                process->setState(BLOCKED);
                blockedQueue.push_back(process);
                runningProcess = nullptr;
                // Return false so that we do not call handleBlockedProcesses immediately.
                return false;
            }
            else if (type == "TERMINATE") {
                // Increment globalTime.
                globalTime++;
                logEvent("Process " + to_string(process->getPID()) + ": Running -> Halted");
                process->setState(TERMINATED);
                delete process;
                runningProcess = nullptr;
                return false;
            }
            else if (type == "ERROR") {
                // Increment globalTime.
                globalTime++;
                logEvent("Process " + to_string(process->getPID()) + ": Running -> Halted");
                process->setState(TERMINATED);
                delete process;
                runningProcess = nullptr;
                return false;
            }
        }
    }
    else {
        // Normal instruction.
        logEvent("Process " + to_string(process->getPID()) + ": " + instruction);
        currentTimeSlice++;
        // Increment globalTime.
        globalTime++;
        // Check for timer interrupt after 5 normal instructions.
        if (currentTimeSlice == 5) {
            logEvent("Hardware Interrupt: Timer interval");
            logEvent("Process " + to_string(process->getPID()) + ": Running -> Ready");
            process->setState(READY);
            readyQueue.push_back(process);
            runningProcess = nullptr;
            return false;
        }
        // Return true to indicate a normal instruction was executed.
        return true;
    }
    // Should not reach here.
    return false;
}

// Check each blocked process. If globalTime is greater than or equal to its unblockTime, then unblock it.
// (Processes in blockedQueue are kept in FIFO order.)
void handleBlockedProcesses() {
    vector<Process*> stillBlocked;
    // Process blockedQueue in order.
    for (auto process : blockedQueue) {
        if (globalTime >= process->getUnblockTime()) {
            logEvent("Process " + to_string(process->getPID()) + ": Blocked -> Ready");
            process->setState(READY);
            readyQueue.push_back(process);
        } else {
            stillBlocked.push_back(process);
        }
    }
    blockedQueue = stillBlocked;
}

// Log an event to both standard output and LOG.txt.
void logEvent(const string &event) {
    cout << event << endl;
    logFile << event << endl;
}
