# eitan.derdiger@gmail.com

# Compiler and flags
CXX      := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g

# Directories
SRC_DIR  := .
TEST_DIR := tests
OBJ_DIR  := build

# Source files from MatrixLib (exclude Main/tests)
SRCS := $(shell find $(SRC_DIR)/MatrixLib -name '*.cpp')
OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Compile each .cpp file to .o under build/
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: Main test valgrind clean

# Build the main program with all object files
Main: Main.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o Main
	./Main


# Compile and run tests (manually include source)
test:
	$(CXX) $(CXXFLAGS) tests/tests.cpp MatrixLib/SquareMat.cpp -o Tests
	./Tests

# Run valgrind memory leak check on Main
valgrind: Main
	valgrind --leak-check=full ./Main

# Clean object files and executables
clean:
	rm -rf $(OBJ_DIR) Main Tests
