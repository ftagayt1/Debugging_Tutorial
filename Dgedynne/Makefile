# Makefile for debugging examples
# Compile with debugging symbols for GDB and Valgrind

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -O0

# Targets
all: logic_error_example memory_leak_example

# Logic error example - good for GDB stepping
logic_error_example: logic_error_example.cpp
	$(CXX) $(CXXFLAGS) -o logic_error_example logic_error_example.cpp

# Memory leak example - good for Valgrind
memory_leak_example: memory_leak_example.cpp
	$(CXX) $(CXXFLAGS) -o memory_leak_example memory_leak_example.cpp

# Clean up compiled files
clean:
	rm -f logic_error_example memory_leak_example

# Run logic error example with GDB
debug-logic:
	gdb ./logic_error_example

# Run memory leak example with Valgrind
debug-memory:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./memory_leak_example

# Run memory leak example with more detailed Valgrind output
debug-memory-detailed:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_output.txt ./memory_leak_example

.PHONY: all clean debug-logic debug-memory debug-memory-detailed 