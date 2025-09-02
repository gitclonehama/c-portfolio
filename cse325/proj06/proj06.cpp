#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <vector>

//
// Registers - 16 registers of 16 bits each
//
uint16_t registers[16] = {0};  // Vector of 16 bit ints all 0

//
// Data Cache - 8 lines with metadata and data
//
struct CacheLine {
  bool valid;       // Valid bit (1 if data is valid)
  bool modified;    // Modified bit (1 if data has been changed)
  uint16_t tag;     // Tag bits (10 bits)
  uint8_t data[8];  // 8-byte data block
};
// 8 CacheLines
CacheLine cache[8] = {};  // Initialize all fields to zero/false

//
// RAM - 65536 bytes of memory
//
uint8_t ram[65536] = {0};  // Initialize all to 0

//
// Helper function signatures
//

// Load RAM initial values from file
int loadRamFromFile(const std::string& filename);
// Break down address into tag, line, and offset
void breakdownAddress(uint16_t address, uint16_t& tag, uint8_t& line, uint8_t& offset);
// Process instructions from input file
void processInstructions(const std::string& filename, bool debug);
// Display contents of all registers
void displayRegisters();
// Display contents of cache
void displayCache();
// Display first 128 bytes of RAM
void displayRam();


/// @brief Our main function where we will parse the input and call the appropriate functions
/// @param argc Argument count
/// @param argv Vector of given arguments (space delimited)
/// @return 0 for success, 1 in case of errors
int main(int argc, char* argv[]) {
  // Default vals
  std::string inputFile;
  std::string ramFile;
  bool debug = false;
  
  // Parse command line args
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];  // Current arg we are parsing

    // "-input" case
    if (arg == "-input" && i + 1 < argc) {
      inputFile = argv[++i];
    }
    // "-ram" case
    else if (arg == "-ram" && i + 1 < argc) {
      ramFile = argv[++i];
    }
    // "-debug" case
    else if (arg == "-debug") {
      debug = true;
    }
  }

  // Ensure input file was provided
  if (inputFile.empty()) {
    std::cerr << "Error: Input file not specified" << std::endl;
    return 1;
  }
  
  // Ensure input file exists and can be opened
  std::ifstream inputCheck(inputFile);
  if (!inputCheck.is_open()) {
    std::cerr << "Error: Could not open input file " << inputFile << std::endl;
    return 1;
  }
  inputCheck.close();

  // Check RAM file if specified
  if (!ramFile.empty()) {
    std::ifstream ramCheck(ramFile);
    if (!ramCheck.is_open()) {
      std::cerr << "Error: Could not open RAM file " << ramFile << std::endl;
      return 1;
    }
    ramCheck.close();
    
    // Load ram from file if all checks pass
    loadRamFromFile(ramFile);
  }

  // Process the instructions from input file
  // "-debug" option functionality is handled in function
  processInstructions(inputFile, debug);

  // Display final state (all instructions are processed)
  displayRegisters();
  displayCache();
  displayRam();

  return 0;
}


// Function to load initial RAM values from file
int loadRamFromFile(const std::string& filename) {
  // Open file (check was done before calling this)
  std::ifstream file(filename);
  
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    uint16_t address;
    
    // Read the address (first value in the line)
    if (!(iss >> std::hex >> address)) {
      std::cerr << "Error: Invalid RAM file format" << std::endl;
      continue;
    }
    
    // Read 16 bytes of data
    for (int i = 0; i < 16; i++) {
      uint16_t value;
      if (iss >> std::hex >> value) {
        ram[address + i] = static_cast<uint8_t>(value);
      } else {
        // If we couldn't read 16 values, that's not an error
        // The spec doesn't require all 16 values
        break;
      }
    }
  }
  // Success
  return 0;
}

// Function to break down address into tag, line, and offset
void breakdownAddress(uint16_t address, uint16_t& tag, uint8_t& line, uint8_t& offset) {
  offset = address & 0x7;          // Last 3 bits (byte offset)
  line = (address >> 3) & 0x7;     // Next 3 bits (cache line)
  tag = address >> 6;              // Remaining 10 bits (tag)
}

// Process instructions from input file
void processInstructions(const std::string& filename, bool debug) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open input file " << filename << std::endl;
    return;
  }

  // Display initial state if debug is enabled
  if (debug) {
    std::cout << std::endl;
    displayRegisters();
    displayCache();
    displayRam();
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string operation;
    uint16_t reg, address;
    
    // Validate parsing
    if (!(iss >> operation >> std::hex >> reg >> address)) {
      std::cerr << "Error: Malformed instruction line" << std::endl;
      continue;
    }

    // Validate operation value
    if (operation != "LDR" && operation != "STR") {
      std::cerr << "Error: Unknown operation: " << operation << std::endl;
      continue;
    }

    // Validate register value
    if (reg > 0xF) {  // Register number must be 0-15 (0-F in hex)
      std::cerr << "Error: Invalid register number: " << std::hex << reg << std::endl;
      continue;
    }
    
    // Calculate cache mapping
    uint16_t tag;
    uint8_t cacheLine, offset;
    breakdownAddress(address, tag, cacheLine, offset);
    
    // Display instruction information
    std::cout << "\n" << operation << " " 
              << std::hex << reg << " " 
              << std::setfill('0') << std::setw(4) << address << " " 
              << std::setfill('0') << std::setw(3) << tag << " " 
              << static_cast<int>(cacheLine) << " " 
              << static_cast<int>(offset) << std::endl;
    
    // If debug mode is enabled, display cache after each instruction
    if (debug) {
        displayCache();
    }
  }
}

// Display contents of all registers
void displayRegisters() {
  std::cout << "\nREGISTERS" << std::endl;
  
  // Display in column form (R0, R1, R2, R3 in first column, etc.)
  for (int row = 0; row < 4; row++) {
    // First column (R0-R3)
    std::cout << "R" << std::hex << row << ": " 
              << std::setfill('0') << std::setw(4) << registers[row] << "    ";
    
    // Second column (R4-R7)
    std::cout << "R" << std::hex << (row + 4) << ": " 
              << std::setfill('0') << std::setw(4) << registers[row + 4] << "    ";
    
    // Third column (R8-Rb)
    std::cout << "R" << std::hex << (row + 8) << ": " 
              << std::setfill('0') << std::setw(4) << registers[row + 8] << "    ";
    
    // Fourth column (Rc-Rf)
    std::cout << "R" << std::hex << (row + 12) << ": " 
              << std::setfill('0') << std::setw(4) << registers[row + 12];
    
    std::cout << std::endl;
  }
}

// Display contents of cache
void displayCache() {
  std::cout << "\nDATA CACHE" << std::endl;
  std::cout << "     V M Tag  0  1  2  3  4  5  6  7" << std::endl;
  std::cout << "____________________________________" << std::endl;
  for (int i = 0; i < 8; i++) {
    std::cout << "[" << std::hex << i << "]: "
              << (cache[i].valid ? "1" : "0") << " "
              << (cache[i].modified ? "1" : "0") << " "
              << std::setfill('0') << std::setw(3) << cache[i].tag << "  ";
    
    // Display the 8 bytes of data
    for (int j = 0; j < 8; j++) {
      std::cout << std::setfill('0') << std::setw(2) 
                << static_cast<int>(cache[i].data[j]) << " ";
    }
    std::cout << std::endl;
  }
}

// Display first 128 bytes of RAM
void displayRam() {
  std::cout << "\nRAM" << std::endl;
  for (int i = 0; i < 128; i += 16) {
    std::cout << std::hex << std::setfill('0') << std::setw(4) << i << ": ";
    for (int j = 0; j < 16; j++) {
      std::cout << std::setfill('0') << std::setw(2) 
                << static_cast<int>(ram[i + j]) << " ";
    }
    std::cout << std::endl;
  }
}