# CSE 325 Project 7 - Virtual Memory Simulator
# Makefile for building the project

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executable
TARGET = proj07

# Source files
SOURCES = proj07.cpp

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Debug build with additional debugging information
debug: CXXFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Phony targets
.PHONY: all clean debug
