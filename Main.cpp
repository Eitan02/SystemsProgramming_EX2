// eitan.derdiger@gmail.com

#include "MatrixLib/SquareMat.h"
#include <iostream>

using MatrixLib::SquareMat;

// Helper to visually separate test sections
void print_section(const std::string& title) {
    std::cout << "\n==================== " << title << " ====================\n";
}

int main() {
    // Create two 3x3 matrices
    SquareMat A{{1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}};

    SquareMat B{{9, 8, 7},
                {6, 5, 4},
                {3, 2, 1}};

    print_section("Matrix A");
    std::cout << A;

    print_section("Matrix B");
    std::cout << B;

    // Addition
    print_section("Addition (A + B)");
    std::cout << A + B;

    // Subtraction
    print_section("Subtraction (A - B)");
    std::cout << A - B;

    // Unary minus
    print_section("Unary Minus (-A)");
    std::cout << -A;

    // Matrix multiplication
    print_section("Matrix Multiplication (A * B)");
    std::cout << A * B;

    // Scalar multiplication
    print_section("Scalar Multiplication (2 * A)");
    std::cout << 2 * A;

    print_section("Scalar Multiplication (A * 2)");
    std::cout << A * 2;

    // Scalar division
    print_section("Scalar Division (A / 2)");
    std::cout << A / 2;

    // Element-wise multiplication
    print_section("Elementwise Multiplication (A % B)");
    std::cout << A % B;

    // Modulo with integer
    print_section("Modulo by Integer (A % 3)");
    std::cout << A % 3;

    // Transpose
    print_section("Transpose (~A)");
    std::cout << ~A;

    // Matrix powers
    print_section("Power (A ^ 0) - Identity Matrix");
    std::cout << (A ^ 0);

    print_section("Power (A ^ 2)");
    std::cout << (A ^ 2);

    // Increment and decrement operators
    print_section("Pre-Increment (++A)");
    std::cout << ++A;

    print_section("Post-Increment (A++)");
    std::cout << A++;
    std::cout << "After A++:\n" << A;

    print_section("Pre-Decrement (--A)");
    std::cout << --A;

    print_section("Post-Decrement (A--)");
    std::cout << A--;
    std::cout << "After A--:\n" << A;

    // Determinant
    print_section("Determinant (!A)");
    std::cout << "!A = " << !A << "\n";

    // Compound assignment tests
    SquareMat C = A;

    print_section("Compound Assignments");
    std::cout << "(C is a copy of A used for compound assignments)\n\n";

    C += B;
    std::cout << "C += B:\n" << C << "\n";

    C -= B;
    std::cout << "C -= B:\n" << C << "\n";

    C *= B;
    std::cout << "C *= B:\n" << C << "\n";

    C *= 0.5;
    std::cout << "C *= 0.5:\n" << C << "\n";

    C /= 0.5;
    std::cout << "C /= 0.5:\n" << C << "\n";

    C %= B;
    std::cout << "C %= B:\n" << C << "\n";

    C %= 7;
    std::cout << "C %= 7:\n" << C << "\n";

    // Comparison operators (based on sum of elements)
    print_section("Comparisons");
    std::cout << "A == A? " << (A == A) << "\n";
    std::cout << "A != B? " << (A != B) << "\n";
    std::cout << "A < B?  " << (A < B) << "\n";
    std::cout << "A <= B? " << (A <= B) << "\n";
    std::cout << "B > A?  " << (B > A) << "\n";
    std::cout << "B >= A? " << (B >= A) << "\n";

    // Element access and modification
    print_section("Element Access");
    std::cout << "A[0][0] = " << A[0][0] << "\n";
    std::cout << "A[1][1] = " << A[1][1] << "\n";
    std::cout << "A[2][2] = " << A[2][2] << "\n";

    std::cout << "\nSetting A[0][1] = 42\n";
    A[0][1] = 42;
    std::cout << "Updated A:\n" << A;

    std::cout << "\nSetting A[2][0] = -7\n";
    A[2][0] = -7;
    std::cout << "Updated A:\n" << A;

    // Final print test
    print_section("Print with <<");
    std::cout << A;

    return 0;
}
