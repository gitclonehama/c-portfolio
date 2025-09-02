# TCP File Transfer Client-Server Application

Basic client-server file transfer application using TCP sockets for reliable file transmission over a network connection.

## Project Overview

This project implements a simple file transfer protocol using TCP sockets. The client requests a file from the server, and the server sends the file contents if the file exists and is accessible.

## Key Features

- **TCP Socket Communication** - Reliable connection-oriented file transfer
- **Simple Protocol** - Text-based command protocol (OPEN/FAILED/SEND)
- **File Transfer** - Chunked file transmission in 64-byte blocks
- **Error Handling** - Basic network and file error management
- **Command Line Interface** - Client accepts hostname, port, and filename arguments

## Implementation Details

### Server Component (`proj08.server.cpp`)

The server performs the following operations:
1. Creates a TCP socket and binds to port 55555
2. Listens for incoming client connections
3. Accepts a single client connection
4. Receives filename request from client
5. Attempts to open the requested file
6. Sends "OPEN" response if file exists, "FAILED" if not
7. If file is available, transfers contents in 64-byte chunks
8. Closes connection after transfer completion

### Client Component (`proj08.client.cpp`)

The client performs the following operations:
1. Parses command-line arguments (hostname, port, filename)
2. Creates a TCP socket and connects to server
3. Sends filename request to server
4. Receives server response (OPEN/FAILED)
5. If file is available, receives and displays file contents
6. Handles connection errors and invalid responses

## Usage

```bash
# Build both components
make

# Terminal 1: Start server
./proj08.server

# Terminal 2: Request file from server
./proj08.client <hostname> <port> <filename>
```

### Example Usage
```bash
# Start server
./proj08.server
# Output: hostname 55555

# Request a file
./proj08.client localhost 55555 test.txt

# If file exists, contents are displayed
# If file doesn't exist, error message is shown
```

## Technical Implementation

### Socket Programming
```cpp
// Server socket creation and binding
int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in serverAddress;
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(PORT);
serverAddress.sin_addr.s_addr = INADDR_ANY;
bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

// Client connection
int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen);
```

### File Transfer Protocol
```cpp
// Server: Send file in 64-byte chunks
char fileBuffer[64];
while (file.read(fileBuffer, sizeof(fileBuffer))) {
    send(clientSocket, fileBuffer, file.gcount(), 0);
}

// Client: Receive and display file contents
while ((bytes = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
    write(1, buffer, bytes);  // Write to stdout
}
```

## Learning Outcomes

### Network Programming Fundamentals
- **Socket Programming** - TCP socket creation, binding, listening, accepting
- **Client-Server Architecture** - Basic client-server communication patterns
- **Network Protocols** - TCP connection establishment and data transfer
- **Error Handling** - Network and file operation error checking

### C++ Systems Programming
- **System Calls** - Unix networking and I/O system calls
- **File I/O** - Reading and transmitting file contents
- **Command-Line Processing** - Argument parsing and validation
- **Memory Management** - Buffer management for network communication

### Software Engineering Skills
- **Modular Design** - Separating client and server functionality
- **Error Recovery** - Graceful handling of network failures
- **Resource Management** - Proper socket and file handle cleanup
- **Cross-Platform Compatibility** - Unix socket programming concepts

## File Structure

```
proj08/
├── proj08.server.cpp       # Server implementation
├── proj08.client.cpp       # Client implementation
├── Makefile               # Build configuration
└── README.md              # Project documentation
```

## Build Instructions

```bash
cd proj08/
make

# Build server
g++ -o proj08.server proj08.server.cpp

# Build client
g++ -o proj08.client proj08.client.cpp
```

## Testing Examples

### Basic File Transfer Test
```bash
# Create a test file
echo "Hello, this is a test file for transfer." > test.txt

# Start server in one terminal
./proj08.server

# Request file from another terminal
./proj08.client localhost 55555 test.txt
# Output: Hello, this is a test file for transfer.
```

### Error Handling Test
```bash
# Try to request non-existent file
./proj08.client localhost 55555 nonexistent.txt
# Output: Server could not open the file
```

### Large File Transfer Test
```bash
# Create a larger test file
dd if=/dev/urandom of=large_test.bin bs=1024 count=100

# Transfer the file
./proj08.client localhost 55555 large_test.bin
```

## Technical Details

### Network Protocol
- **Transport Layer**: TCP (reliable, connection-oriented)
- **Port**: 55555 (hardcoded for simplicity)
- **Message Format**: Simple text commands and binary file data
- **Chunk Size**: 64 bytes per transmission packet

### Error Conditions
- **Connection Failure**: Cannot connect to server
- **File Not Found**: Requested file doesn't exist on server
- **Network Errors**: Socket read/write failures
- **Invalid Responses**: Unexpected server responses

### Limitations
- **Single Client**: Server handles only one client at a time
- **No Authentication**: No security or access control
- **Fixed Port**: Port number is hardcoded
- **No Progress Indication**: No transfer progress feedback

## Educational Value

### Networking Concepts
- **TCP/IP Fundamentals** - Understanding reliable network communication
- **Client-Server Model** - Basic distributed system architecture
- **Socket Programming** - Low-level network programming interface
- **Protocol Design** - Simple application-level protocol implementation

### Systems Programming
- **Unix System Calls** - Network and file system interfaces
- **Error Handling** - Robust error checking and reporting
- **Resource Management** - Proper cleanup of system resources
- **Performance Considerations** - Network latency and throughput awareness

### Professional Development
- **Network Application Development** - Foundation for web servers, file servers, etc.
- **Debugging Network Code** - Techniques for debugging distributed applications
- **Security Awareness** - Understanding basic network security concepts
- **Scalability Considerations** - Limitations of simple client-server designs

## Real-World Applications

### File Transfer Protocols
- **FTP (File Transfer Protocol)** - Industry standard file transfer
- **HTTP File Downloads** - Web-based file transfer mechanisms
- **SCP/SFTP** - Secure file transfer protocols
- **BitTorrent** - Peer-to-peer file distribution

### Network Services
- **Web Servers** - HTTP request/response handling
- **Database Servers** - Client-server database communication
- **Mail Servers** - SMTP/POP3/IMAP protocols
- **Streaming Services** - Media streaming protocols

### Development Tools
- **Version Control Systems** - Git server/client communication
- **Remote Development** - SSH and remote development tools
- **API Services** - RESTful API client-server communication
- **Cloud Services** - Communication with cloud storage services

---

*This client-server file transfer project provides essential networking programming skills and serves as a foundation for understanding distributed systems, network protocols, and modern web application development.*
