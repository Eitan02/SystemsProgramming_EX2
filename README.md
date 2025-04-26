# eitan.derdiger@gmail.com

# SquareMat – Assignment 2: Operator Overloading for Square Matrices

This project implements the `SquareMat` class in C++ as part of Assignment 2 for the "System Programming 2" course. It represents real-valued square matrices with complete operator overloading, memory safety, and unit testing.

---

## 📁 Project Structure

SquareMatProject/
├── MatrixLib/
│   ├── SquareMat.h         # Class interface
│   └── SquareMat.cpp       # Class implementation
├── Main.cpp                # Demo application (prints matrix operations)
├── tests/
|   ├── doctest.h           # Doctest header
│   └── tests.cpp           # Unit tests using doctest
├── Makefile                # Build, test, valgrind, and cleanup commands
├── README.md               # Project documentation

---

## Compilation & Execution

Build and run the demo:
make Main

Run the unit tests:
make test

Run memory leak check with valgrind:
make valgrind

Clean all build files:
make clean

---

## Features

- No use of STL containers (no `vector`, `array`, etc.)
- Dynamically allocated memory using `new[]`/`delete[]`
- Rule of Three compliance:
  - Copy constructor
  - Copy assignment operator
  - Destructor
- Full operator overloading:
  - Arithmetic: `+`, `-`, `*`, `/`, `%`
  - Scalar operations: `scalar * matrix`, `matrix * scalar`, `matrix / scalar`...
  - Power: `^` (repeated multiplication)
  - Unary minus `-`, transpose `~`, determinant `!`
  - Compound assignments: `+=`, `-=`, `*=`, `/=`, `%=` (matrix and scalar)
  - Increment/Decrement: `++`, `--` (both pre and post)
  - Element access: `matrix[i][j]`
  - Comparison: `==`, `!=`, `<`, `>`, `<=`, `>=` (based on sum of elements)
- Input validation and exception handling
- Determinant calculation
- Comprehensive test coverage using `doctest`

---

## Exception Handling

- `std::invalid_argument` – for invalid matrix operations (e.g., size mismatch, division/modulo by zero)
- `std::out_of_range` – for invalid element access
- `std::logic_error` – for invalid logic (e.g., determinant of empty or too-large matrix)

---

## Dependencies

- clang++ compiler installed

---

## 🧼 Memory Safety

All dynamic memory allocations are managed manually and tested.
Use valgrind to check:
valgrind --leak-check=full ./Main

---

## Submission Notes

- The project does not use any standard containers
- Fully modular and tested
- Meets all assignment requirements

---