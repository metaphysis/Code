#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

struct Rational {
    cpp_int num, den;
    Rational() : num(0), den(1) {}
    Rational(long long value) : num(value), den(1) {}
    Rational(cpp_int numerator, cpp_int denominator) : num(numerator), den(denominator) {
        normalize();
    }
    cpp_int gcdValue(cpp_int a, cpp_int b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b != 0) {
            cpp_int temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }
    void normalize() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        cpp_int value = gcdValue(num, den);
        if (value != 0) {
            num /= value;
            den /= value;
        }
    }
};

Rational operator +(const Rational &a, const Rational &b) {
    return Rational(a.num * b.den + b.num * a.den, a.den * b.den);
}

Rational operator -(const Rational &a, const Rational &b) {
    return Rational(a.num * b.den - b.num * a.den, a.den * b.den);
}

Rational operator *(const Rational &a, const Rational &b) {
    return Rational(a.num * b.num, a.den * b.den);
}

Rational operator /(const Rational &a, const Rational &b) {
    return Rational(a.num * b.den, a.den * b.num);
}

bool operator ==(const Rational &a, const Rational &b) {
    return a.num == b.num && a.den == b.den;
}

string toString(const cpp_int &value) {
    return value.convert_to<string>();
}

string coefficientText(const Rational &value) {
    if (value.den == 1) return toString(value.num);
    return toString(value.num) + "/" + toString(value.den);
}

void printPolynomial(Rational polynomial[], int degree) {
    bool printed = false;
    for (int i = 0; i <= degree; ++i) {
        if (polynomial[i] == Rational(0)) continue;
        if (printed) cout << " ";
        cout << "(" << coefficientText(polynomial[i]) << "," << i << ")";
        printed = true;
    }
    if (!printed) cout << "(0,0)";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n, f[10];
    bool firstCase = true;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;
        int total = m + n;
        for (int i = 0; i < total; ++i) cin >> f[i];
        Rational matrix[5][6], q[5], p[5];
        for (int row = 0; row < n; ++row) {
            int k = m + row;
            for (int col = 0; col < n; ++col) {
                matrix[row][col] = Rational(0);
                int index = k - col;
                if (index >= 0) matrix[row][col] = Rational(f[index]);
            }
            matrix[row][n] = Rational(row == n - 1 ? 1 : 0);
        }
        for (int col = 0; col < n; ++col) {
            int pivot = col;
            while (pivot < n && matrix[pivot][col] == Rational(0)) ++pivot;
            swap(matrix[pivot], matrix[col]);
            Rational divisor = matrix[col][col];
            for (int j = col; j <= n; ++j) matrix[col][j] = matrix[col][j] / divisor;
            for (int i = 0; i < n; ++i) {
                if (i == col) continue;
                Rational factor = matrix[i][col];
                if (factor == Rational(0)) continue;
                for (int j = col; j <= n; ++j) matrix[i][j] = matrix[i][j] - factor * matrix[col][j];
            }
        }
        for (int i = 0; i < n; ++i) q[i] = matrix[i][n];
        for (int i = 0; i < m; ++i) {
            p[i] = Rational(0);
            for (int j = 0; j < n; ++j) {
                int index = i - j;
                if (index >= 0) p[i] = p[i] + q[j] * Rational(f[index]);
            }
        }
        if (!firstCase) cout << "\n";
        firstCase = false;
        printPolynomial(p, m - 1);
        printPolynomial(q, n - 1);
    }
    return 0;
}
