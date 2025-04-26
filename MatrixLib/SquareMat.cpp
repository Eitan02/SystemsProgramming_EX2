// eitan.derdiger@gmail.com

#include "SquareMat.h"
#include <algorithm>   // for std::swap
#include <cmath>       // for fmod, fabs

using namespace MatrixLib;

// ======= Constructors =======

// Initialize a square matrix with given size and fill value
SquareMat::SquareMat(std::size_t order, double initVal)
    : n(order), data(nullptr) {
    if (n == 0 && initVal != 0.0)
        throw std::invalid_argument("order 0 with value");
    if (n) {
        data = new double[n * n]; // allocate memory
        for (std::size_t i = 0; i < n * n; ++i)
            data[i] = initVal; // fill all cells
    }
}

// Initialize matrix from initializer list (like {{1,2},{3,4}})
SquareMat::SquareMat(std::initializer_list<std::initializer_list<double>> init)
    : n(init.size()), data(nullptr) {
    if (n == 0)
        throw std::invalid_argument("empty init");

    data = new double[n * n];
    std::size_t r = 0;
    for (const auto& row : init) {
        if (row.size() != n)
            throw std::invalid_argument("not square");
        std::size_t c = 0;
        for (double v : row)
            data[idx(r, c++)] = v; // copy values
        ++r;
    }
}

// Deep copy constructor
SquareMat::SquareMat(const SquareMat& other)
    : n(other.n), data(nullptr) {
    if (n) {
        data = new double[n * n];
        std::copy(other.data, other.data + n * n, data);
    }
}

// Assignment operator using copy-and-swap idiom
SquareMat& SquareMat::operator=(const SquareMat& other) {
    if (this == &other) return *this;
    SquareMat tmp(other);
    std::swap(n, tmp.n);
    std::swap(data, tmp.data);
    return *this;
}

// Destructor - frees memory
SquareMat::~SquareMat() {
    delete[] data;
}

// ======= Element Access =======

// Access row as array (non-const)
double* SquareMat::operator[](std::size_t row) {
    if (row >= n) throw std::out_of_range("row");
    return data + row * n;
}

// Access row as array (const version)
const double* SquareMat::operator[](std::size_t row) const {
    if (row >= n) throw std::out_of_range("row");
    return data + row * n;
}

// ======= Sum of Elements =======

// Calculate sum of all elements in matrix
double SquareMat::sum() const {
    double s = 0;
    for (std::size_t i = 0; i < n * n; ++i)
        s += data[i];
    return s;
}


// ======= Free Functions / Operators =======
namespace MatrixLib {

// Check if matrices have same size
void ensure_same(const SquareMat& a, const SquareMat& b) {
    if (a.order() != b.order())
        throw std::invalid_argument("order mismatch");
}

// Element-wise addition
SquareMat operator+(const SquareMat& a, const SquareMat& b) {
    ensure_same(a, b);
    std::size_t n = a.order();
    SquareMat r(n);
    for (std::size_t i = 0; i < n * n; ++i)
        r.data[i] = a.data[i] + b.data[i];
    return r;
}

// Element-wise subtraction
SquareMat operator-(const SquareMat& a, const SquareMat& b) {
    ensure_same(a, b);
    std::size_t n = a.order();
    SquareMat r(n);
    for (std::size_t i = 0; i < n * n; ++i)
        r.data[i] = a.data[i] - b.data[i];
    return r;
}

// Matrix multiplication
SquareMat operator*(const SquareMat& A, const SquareMat& B) {
    ensure_same(A, B);
    std::size_t n = A.order();
    SquareMat C(n, 0.0);
    for (std::size_t i = 0; i < n; ++i)
        for (std::size_t k = 0; k < n; ++k) {
            double aik = A[i][k];
            for (std::size_t j = 0; j < n; ++j)
                C[i][j] += aik * B[k][j];
        }
    return C;
}

// Scalar multiplication (scalar * matrix)
SquareMat operator*(double s, const SquareMat& M) {
    SquareMat R(M.order());
    for (std::size_t i = 0; i < M.order() * M.order(); ++i)
        R.data[i] = s * M.data[i];
    return R;
}

// Scalar multiplication (matrix * scalar)
SquareMat operator*(const SquareMat& M, double s) {
    return s * M;
}

// Division by scalar
SquareMat operator/(const SquareMat& M, double s) {
    if (std::fabs(s) < SquareMat::EPS)
        throw std::invalid_argument("divide by 0");
    SquareMat R(M.order());
    for (std::size_t i = 0; i < M.order() * M.order(); ++i)
        R.data[i] = M.data[i] / s;
    return R;
}

// Element-wise multiplication
SquareMat operator%(const SquareMat& A, const SquareMat& B) {
    ensure_same(A, B);
    SquareMat R(A.order());
    for (std::size_t i = 0; i < A.order() * A.order(); ++i)
        R.data[i] = A.data[i] * B.data[i];
    return R;
}

// Element-wise modulo with integer
SquareMat operator%(const SquareMat& M, int m) {
    if (m == 0)
        throw std::invalid_argument("mod 0");
    SquareMat R(M.order());
    for (std::size_t i = 0; i < M.order() * M.order(); ++i) {
        R.data[i] = std::fmod(M.data[i], static_cast<double>(m));
        if (R.data[i] < 0) R.data[i] += m;
    }
    return R;
}

// Print matrix nicely
std::ostream& operator<<(std::ostream& os, const SquareMat& M) {
    std::size_t n = M.order();
    for (std::size_t i = 0; i < n; ++i) {
        os << "[ ";
        for (std::size_t j = 0; j < n; ++j) {
            os << M.data[i * n + j];
            if (j + 1 < n) os << ", ";
        }
        os << " ]\n";
    }
    return os;
}

// Same as <<
std::ostream& operator>>(std::ostream& os, const SquareMat& M) {
    return operator<<(os, M);
}

} // namespace MatrixLib

// ======= Unary Operators / Transpose / Power =======

// Negate all elements
SquareMat SquareMat::operator-() const {
    SquareMat R(n);
    for (std::size_t i = 0; i < n * n; ++i)
        R.data[i] = -data[i];
    return R;
}

// Transpose the matrix
SquareMat SquareMat::operator~() const {
    SquareMat R(n);
    for (std::size_t i = 0; i < n; ++i)
        for (std::size_t j = 0; j < n; ++j)
            R.data[j * n + i] = data[i * n + j];
    return R;
}

// Raise matrix to power k (k ≥ 0)
SquareMat SquareMat::operator^(unsigned int k) const {
    if (n == 0) throw std::logic_error("power of empty matrix");
    if (k == 0) {
        SquareMat I(n, 0.0);
        for (std::size_t i = 0; i < n; ++i)
            I.data[i * n + i] = 1.0; // identity matrix
        return I;
    }
    if (k == 1) return *this;
    SquareMat half = (*this) ^ (k / 2);
    SquareMat res = half * half;
    if (k % 2) res = res * (*this);
    return res;
}

// Determinant using Gaussian Elimination
double SquareMat::operator!() const {
    if (n == 0) throw std::logic_error("det of empty matrix");

    // Make a copy of the matrix to modify (we don't modify the original)
    SquareMat A(*this);
    
    double det = 1.0;
    // Perform Gaussian elimination
    for (std::size_t i = 0; i < n; ++i) {
        // Find the row with the largest pivot (for numerical stability)
        std::size_t max_row = i;
        for (std::size_t j = i + 1; j < n; ++j) {
            if (std::fabs(A[j][i]) > std::fabs(A[max_row][i])) {
                max_row = j;
            }
        }

        // Swap rows if necessary
        if (i != max_row) {
            for (std::size_t k = 0; k < n; ++k) {
                std::swap(A[i][k], A[max_row][k]);
            }
            det *= -1;  // Changing rows reverses the sign of the determinant
        }

        // If the pivot is basically zero, the determinant is zero
        if (std::fabs(A[i][i]) < EPS) return 0;

        // Eliminate all entries below the pivot
        for (std::size_t j = i + 1; j < n; ++j) {
            double factor = A[j][i] / A[i][i];
            for (std::size_t k = i; k < n; ++k) {
                A[j][k] -= factor * A[i][k];
            }
        }

        // Multiply the determinant by the pivot element
        det *= A[i][i];
    }

    if (std::fabs(det) < EPS) {
        det = 0;
    }
    
    return det;
}


// ======= Increment / Decrement Operators =======

// Pre-increment
SquareMat& SquareMat::operator++() {
    for (std::size_t i = 0; i < n * n; ++i)
        ++data[i];
    return *this;
}

// Post-increment
SquareMat SquareMat::operator++(int) {
    SquareMat t(*this);
    ++(*this);
    return t;
}

// Pre-decrement
SquareMat& SquareMat::operator--() {
    for (std::size_t i = 0; i < n * n; ++i)
        --data[i];
    return *this;
}

// Post-decrement
SquareMat SquareMat::operator--(int) {
    SquareMat t(*this);
    --(*this);
    return t;
}

// ======= Compound Assignment Operators =======

SquareMat& SquareMat::operator+=(const SquareMat& rhs) {
    return *this = *this + rhs;
}
SquareMat& SquareMat::operator-=(const SquareMat& rhs) {
    return *this = *this - rhs;
}
SquareMat& SquareMat::operator*=(const SquareMat& rhs) {
    return *this = *this * rhs;
}
SquareMat& SquareMat::operator*=(double s) {
    for (std::size_t i = 0; i < n * n; ++i)
        data[i] *= s;
    return *this;
}
SquareMat& SquareMat::operator/=(double s) {
    return *this = *this / s;
}
SquareMat& SquareMat::operator%=(const SquareMat& rhs) {
    return *this = *this % rhs;
}
SquareMat& SquareMat::operator%=(int m) {
    return *this = *this % m;
}

// ======= Comparison Operators (based on sum) =======

bool SquareMat::operator==(const SquareMat& rhs) const {
    return std::fabs(sum() - rhs.sum()) < EPS;
}
bool SquareMat::operator!=(const SquareMat& rhs) const {
    return !(*this == rhs);
}
bool SquareMat::operator< (const SquareMat& rhs) const {
    return sum() < rhs.sum() - EPS;
}
bool SquareMat::operator<=(const SquareMat& rhs) const {
    return *this < rhs || *this == rhs;
}
bool SquareMat::operator> (const SquareMat& rhs) const {
    return rhs < *this;
}
bool SquareMat::operator>=(const SquareMat& rhs) const {
    return rhs <= *this;
}
