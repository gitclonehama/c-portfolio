#include <iostream>
#include <sys/socket.h> // socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h> // sockaddr_in, htons()
#include <cstring>      // memset(), strcmp()
#include <unistd.h>     // close(), gethostname()
#include <fstream>      // For file operations

constexpr int BUFFER_SIZE = 64;
constexpr int PORT = 55555;

int main() {

    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    // Add socket option to allow reusing the address
    int optval = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        std::cerr << "Setsockopt failed" << std::endl;
        close(serverSocket);
        return 1;
    }
    
    // Bind to a port
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET; // IPv4 protocal family
    serverAddress.sin_port = htons(PORT);   // Convert machine byte order to network byte order
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Listen to all available IPs
    
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Bind failed" << std::endl;
        close(serverSocket);
        return 1;
    }

    // Display the host name and port number
    char hostname[BUFFER_SIZE];
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        std::cerr << "Gethostname failed" << std::endl;
        close(serverSocket);
        return 1;
    }
    std::cout << hostname << " " << PORT << std::endl;

    // Listen for a connection request on port
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Listen failed" << std::endl;
        close(serverSocket);
        return 1;
    }
    
    // Accept connection request from client
    struct sockaddr_in clientAddress;
    socklen_t clientAddrLen = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen);
    if (clientSocket == -1) {
        std::cerr << "Accept failed" << std::endl;
        close(serverSocket);
        return 1;
    }

    // Wait for client to send a file name
    char buffer[BUFFER_SIZE];
    std::memset(buffer, 0, sizeof(buffer)); // Reset buffer to all 0s
    ssize_t bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytes <= 0) {
        std::cerr << "Failed to receive buffer from client" << std::endl;
        close(serverSocket);
        close(clientSocket);
        return 1;
    }

    // Try to open file
    std::ifstream file(buffer, std::ios::binary);
    if (file.is_open()) {
        // Send "OPEN" to client
        const char* openMsg = "OPEN";
        if (send(clientSocket, openMsg, 4, 0) == -1) {
            std::cerr << "Failed to send OPEN message to client" << std::endl;
            file.close();
            close(serverSocket);
            close(clientSocket);
            return 1;
        }

        // Wait for client response
        std::memset(buffer, 0, sizeof(buffer));
        bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytes <= 0) {
            std::cerr << "Failed to receive response from client" << std::endl;
            file.close();
            close(serverSocket);
            close(clientSocket);
            return 1;
        }

        // If response == "SEND"
        if (strcmp(buffer, "SEND") == 0) {
            // Send the conents of input file to client
            char fileBuffer[64];    // 64-byte per assignment specs
            while (file.read(fileBuffer, sizeof(fileBuffer))) {
                // Send file data in 64 byte packets
                int sendStatus = send(clientSocket, fileBuffer, file.gcount(), 0);
                if (sendStatus == -1) {
                    std::cerr << "Failed to send file data" << std::endl;
                    file.close();
                    close(serverSocket);
                    close(clientSocket);
                    return 1;
                }
            }
            // Ensure entire file was sent (in case last packet is < 64 bytes)
            if (file.gcount() > 0) {
                if (send(clientSocket, fileBuffer, file.gcount(), 0) == -1) {
                    std::cerr << "Failed to send final file data" << std::endl;
                    file.close();
                    close(serverSocket);
                    close(clientSocket);
                    return 1;
                }
            }
        }

        // Successful file transfer, terminate
        file.close();
        close(serverSocket);
        close(clientSocket);

    } else {
        // Send "FAILED" to client and terminate
        const char* failed = "FAILED";
        if (send(clientSocket, failed, 6, 0) == -1) {
            std::cerr << "Failed to send FAILED message to client" << std::endl;
            close(serverSocket);
            close(clientSocket);
            return 1;
        }
    }
    
    return 0;
}


/*
CITATIONS

Learning more about <sys/socket.h>
- https://pubs.opengroup.org/onlinepubs/7908799/xns/syssocket.h.html

Examples of server and client code
- https://www.geeksforgeeks.org/socket-programming-in-cpp/#

Using INADDR_ANY (to bind to all interfaces)
- https://edstem.org/us/courses/71062/discussion/6594253

Learning about memset()
- https://www.geeksforgeeks.org/memset-c-example/
*/
