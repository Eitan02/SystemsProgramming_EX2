// eitan.derdiger@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../MatrixLib/SquareMat.h"
#include <sstream>

using MatrixLib::SquareMat;

// Test constructors and element access
TEST_CASE("constructors & access") {
    SquareMat Z;  // default constructor
    CHECK(Z.order() == 0);

    SquareMat A(3, 7.0);  // 3x3 filled with 7
    CHECK(A[2][2] == doctest::Approx(7.0));

    SquareMat B{{1,2},{3,4}};  // init list
    CHECK(B[1][0] == 3);

    // Invalid: not square
    CHECK_THROWS_AS((SquareMat(std::initializer_list<std::initializer_list<double>>{{1,2,3}})), std::invalid_argument);

    // Invalid access
    CHECK_THROWS_AS((void)B[5][0], std::out_of_range);
}

// Test basic arithmetic and unary minus
TEST_CASE("arithmetic +, -, unary -") {
    SquareMat A{{1,2},{3,4}};
    SquareMat B{{4,3},{2,1}};

    CHECK((A+B)[0][0] == 5);  // addition
    CHECK((A-B)[1][1] == 3);  // subtraction
    CHECK((-A)[0][1] == -2);  // negate
}

// Test matrix multiplication and scalar operations
TEST_CASE("matrix multiply & scalar ops") {
    SquareMat I{{1,0},{0,1}};  // identity matrix
    SquareMat X{{2,3},{4,5}};
    CHECK((I*X) == X);         // I * X = X

    SquareMat Y = 2 * I;
    CHECK(Y[1][1] == 2);       // scalar multiplication

    Y /= 2;
    CHECK(Y == I);             // back to identity

    CHECK_THROWS_AS(X/0.0, std::invalid_argument);  // division by 0
}

// Test elementwise multiplication and modulo
TEST_CASE("elementwise % and modulo int") {
    SquareMat A{{2,4},{6,8}};
    SquareMat B{{1,1},{2,2}};

    CHECK((A%B)[1][0] == 12);  // 6 * 2
    SquareMat M = A % 5;
    CHECK(M[1][1] == 3);       // 8 % 5 = 3

    CHECK_THROWS_AS(A % 0, std::invalid_argument); // modulo 0
}

// Test transpose and matrix exponentiation
TEST_CASE("transpose & power") {
    SquareMat A{{0,1},{2,3}};
    SquareMat At = ~A;
    CHECK(At[0][1] == 2);      // Aᵗ[0][1] = A[1][0]

    CHECK((A ^ 0)[1][1] == 1); // identity
    CHECK((A ^ 1) == A);       // power 1
    CHECK((A ^ 2)[0][0] == 2); // A^2[0][0]

    SquareMat empty;
    CHECK_THROWS_AS(empty ^ 2, std::logic_error); // power of empty
}

// Test determinant operator (!)
TEST_CASE("determinant") {
    SquareMat A{{1,2},{3,4}};
    CHECK(doctest::Approx(!A) == -2); // det = -2

    SquareMat B{{6}};
    CHECK(!B == 6);  // 1x1 determinant

}

// Test increment and decrement operators
TEST_CASE("increment / decrement ++ --") {
    SquareMat A{{1,1},{1,1}};
    ++A;
    CHECK(A[0][0] == 2);
    A--;
    CHECK(A[0][0] == 1);
}

// Test compound assignment operators
TEST_CASE("compound assignments") {
    SquareMat A{{1,2},{3,4}};
    SquareMat B{{4,3},{2,1}};

    A += B;
    CHECK(A[0][0] == 5);

    A -= B;
    CHECK(A[0][0] == 1);

    A *= B;
    CHECK(A[0][0] == 8);  // verify multiplication

    A %= 5;
    CHECK(A[0][0] == 3);  // mod 8 % 5 = 3
}

// Test comparisons (based on sum of elements)
TEST_CASE("comparisons") {
    SquareMat A{{1,1},{1,1}};  // sum = 4
    SquareMat B{{2,2},{2,0}};  // sum = 6

    CHECK(A <  B);
    CHECK(B >  A);
    CHECK(A != B);

    SquareMat C{{2,1,1},{0,0,0},{0,0,0}}; // sum = 4
    CHECK(A == C);
}

// Test that both << and >> behave the same
TEST_CASE("ostream << and >> identical") {
    SquareMat A{{1,2},{3,4}};
    std::ostringstream ss1, ss2;
    ss1 << A;
    ss2 >> A;
    CHECK(ss1.str() == ss2.str());  // both print formats match
}

// Test errors on size mismatch in operators
TEST_CASE("size mismatch throws") {
    SquareMat A{{1,2},{3,4}};
    SquareMat B{{1}};  // different size

    CHECK_THROWS_AS(A + B, std::invalid_argument);
    CHECK_THROWS_AS(A * B, std::invalid_argument);
}

// Test sum function
TEST_CASE("sum") {
    SquareMat A{{1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}};  // sum = 45

    SquareMat B{{9, 8, 7},
                {6, 5, 4},
                {3, 2, 1}};  // sum = 45

    // Test sum of matrix A
    CHECK(A.sum() == doctest::Approx(45.0));

    // Test sum of matrix B
    CHECK(B.sum() == doctest::Approx(45.0));

    // Test sum of A + B (should be 90)
    CHECK((A + B).sum() == doctest::Approx(90.0));

    // Test sum of A - B (should be 0)
    CHECK((A - B).sum() == doctest::Approx(0.0));
}

// Test ensure_same function indirectly
TEST_CASE("ensure_same") {
    SquareMat A{{1, 2},
                {3, 4}};  // 2x2 matrix

    SquareMat B{{5, 6},
                {7, 8}};  // 2x2 matrix

    SquareMat C{{1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}};  // 3x3 matrix

    // Test valid operation (same size matrices)
    CHECK_NOTHROW(A + B);  // No exception, matrices are the same size

    // Test invalid operation (different size matrices)
    CHECK_THROWS_AS(A + C, std::invalid_argument);  // Should throw exception due to size mismatch
}
