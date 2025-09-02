CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = proj06
SOURCE = proj06.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

debug: CXXFLAGS += -DDEBUG
debug: $(TARGET)

.PHONY: clean debug
