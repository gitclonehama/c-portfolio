#include <iostream>
#include <sys/socket.h> // socket(), connet(), send(), recv()
#include <netinet/in.h> // sockaddr_in, htons()
#include <netdb.h>      // gethostbyname()
#include <cstring>      // memset(), strcmp()
#include <unistd.h>     // close(), write()

constexpr int BUFFER_SIZE = 64;
constexpr int PORT = 55555;

int main(int argc, char *argv[]) {
    // Parse command line args
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <hostname> <port> <filename>" << std::endl;
        return 1;
    }

    // First argument should be hostname
    const char* hostname = argv[1];
    // Second argument should be port
    // int port = std::stoi(argv[2]);   // Using hard coded port value
    // Third argument should be filename
    const char* filename = argv[3];

    // Create client socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Get server IP
    struct hostent* server = gethostbyname(hostname);
    if (server == nullptr) {
        std::cerr << "Host: " << hostname << " not found" << std::endl;
        close(clientSocket);
        return 1;
    }

    // Connect to server
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));   // Ensuring all 0s
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);   // Using hard coded port
    memcpy(&serverAddress.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to connect to server" << std::endl;
        close(clientSocket);
        return 1;
    }

    // Send filename to server
    if (send(clientSocket, filename, strlen(filename), 0) == -1) {
        std::cerr << "Failed to send filename to server" << std::endl;
        close(clientSocket);
        return 1;
    }

    // Wait for server response (OPEN or FAILED)
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    ssize_t bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytes <= 0) {
        std::cerr << "Failed to receive response from server" << std::endl;
        close(clientSocket);
        return 1;
    }

    // Check if server was able to open the file
    if (strcmp(buffer, "OPEN") == 0) {
        // Send "SEND" command to server
        const char* sendMsg = "SEND";
        if (send(clientSocket, sendMsg, 4, 0) == -1) {
            std::cerr << "Failed to send SEND message to server" << std::endl;
            close(clientSocket);
            return 1;
        }

        // Receive and dispaly file contents
        while ((bytes = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
            // Write the file contents to cout
            if (write(1, buffer, bytes) != bytes) {
                std::cerr << "Error writing to stdout" << std::endl;
                close(clientSocket);
                return 1;
            }
        }
        if (bytes == -1) {
            std::cerr << "Error receiving file data" << std::endl;
            close(clientSocket);
            return 1;
        }
    }
    else if (strcmp(buffer, "FAILED") == 0) {
        std::cerr << "Server could not open the file" << std::endl;
        close(clientSocket);
        return 1;
    }
    else {
        std::cerr << "Invalid response from server" << std::endl;
        close(clientSocket);
        return 1;
    }

    // Terminate
    close(clientSocket);
    return 0;
}

/*
WORKS CITED

Learning more about <sys/socket.h>
- https://pubs.opengroup.org/onlinepubs/7908799/xns/syssocket.h.html

Examples of server and client code
- https://www.geeksforgeeks.org/socket-programming-in-cpp/#

Using gethostbyname()
- https://man7.org/linux/man-pages/man3/gethostbyname.3.html

Further reading on server-client and sockets in CPP:
- https://www.geeksforgeeks.org/socket-programming-in-cpp/#

*/
