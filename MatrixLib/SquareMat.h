// eitan.derdiger@gmail.com

#ifndef MATRIXLIB_SQUAREMAT_H
#define MATRIXLIB_SQUAREMAT_H

#include <cstddef>          // for size_t
#include <iostream>         // for ostream
#include <stdexcept>        // for exceptions
#include <initializer_list> // for initializer_list
#include <cmath>            // for fabs

namespace MatrixLib {

class SquareMat {
    std::size_t n;     // size of matrix (n x n)
    double* data;      // flat array for elements in row-major order

    // helper: convert (i, j) to linear index in data[]
    inline std::size_t idx(std::size_t i, std::size_t j) const { return i * n + j; }

public:
    // epsilon for floating-point comparisons
    static constexpr double EPS = 1e-9;

    // ===== Rule of Three =====

    // construct with size and optional initial value (default 0)
    explicit SquareMat(std::size_t order = 0, double initVal = 0.0);

    // construct from nested initializer list (e.g. {{1,2},{3,4}})
    SquareMat(std::initializer_list<std::initializer_list<double>> init);

    // copy constructor
    SquareMat(const SquareMat& other);

    // copy assignment operator
    SquareMat& operator=(const SquareMat& other);

    // destructor
    ~SquareMat();

    // ===== Element Access =====

    // access row i (modifiable)
    double* operator[](std::size_t row);

    // access row i (read-only)
    const double* operator[](std::size_t row) const;

    // ===== External Binary Operators =====

    // matrix + matrix
    friend SquareMat operator+(const SquareMat&, const SquareMat&);

    // matrix - matrix
    friend SquareMat operator-(const SquareMat&, const SquareMat&);

    // matrix * matrix
    friend SquareMat operator*(const SquareMat&, const SquareMat&);

    // scalar * matrix
    friend SquareMat operator*(double, const SquareMat&);

    // matrix * scalar
    friend SquareMat operator*(const SquareMat&, double);

    // matrix / scalar
    friend SquareMat operator/(const SquareMat&, double);

    // element-wise matrix % matrix
    friend SquareMat operator%(const SquareMat&, const SquareMat&);

    // matrix % scalar
    friend SquareMat operator%(const SquareMat&, int);

    // check size match before binary operations
    friend void ensure_same(const SquareMat&, const SquareMat&);

    // ===== Unary Operators =====

    SquareMat operator-() const;                // negate elements
    SquareMat operator~() const;                // transpose
    SquareMat operator^(unsigned int k) const;  // power (matrix^k)
    double    operator!() const;                // determinant

    // ===== Increment / Decrement =====

    SquareMat& operator++();    // pre-increment: ++mat
    SquareMat  operator++(int); // post-increment: mat++
    SquareMat& operator--();    // pre-decrement
    SquareMat  operator--(int); // post-decrement

    // ===== Compound Assignment =====

    SquareMat& operator+=(const SquareMat&);
    SquareMat& operator-=(const SquareMat&);
    SquareMat& operator*=(const SquareMat&);
    SquareMat& operator*=(double);
    SquareMat& operator/=(double);
    SquareMat& operator%=(const SquareMat&);
    SquareMat& operator%=(int);

    // ===== Comparison Operators =====

    bool operator==(const SquareMat&) const;  // same sum
    bool operator!=(const SquareMat&) const;
    bool operator< (const SquareMat&) const;  // based on sum
    bool operator<=(const SquareMat&) const;
    bool operator> (const SquareMat&) const;
    bool operator>=(const SquareMat&) const;

    // ===== I/O Operators =====

    friend std::ostream& operator<<(std::ostream&, const SquareMat&); // print matrix
    friend std::ostream& operator>>(std::ostream&, const SquareMat&); // alias for <<

    // ===== Helpers =====

    // get matrix order (size n)
    [[nodiscard]] std::size_t order() const { return n; }

    // sum of all elements
    double sum() const;
};

} // namespace MatrixLib
#endif
