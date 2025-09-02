# CSE 325 Project 8 - Distributed System
# Makefile for building both client and server

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executables
CLIENT = proj08_client
SERVER = proj08_server

# Source files
CLIENT_SRC = proj08.client.cpp
SERVER_SRC = proj08.server.cpp

# Default target - build both
all: $(CLIENT) $(SERVER)

# Build the client
$(CLIENT): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -o $(CLIENT) $(CLIENT_SRC)

# Build the server
$(SERVER): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -o $(SERVER) $(SERVER_SRC)

# Clean build artifacts
clean:
	rm -f $(CLIENT) $(SERVER)

# Debug builds
debug: CXXFLAGS += -DDEBUG -O0
debug: all

# Individual targets
client: $(CLIENT)
server: $(SERVER)

# Phony targets
.PHONY: all clean debug client server
