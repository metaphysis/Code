#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;

cpp_int absValue(cpp_int value) {
    if (value < 0) return -value;
    return value;
}

cpp_int getGcd(cpp_int a, cpp_int b) {
    a = absValue(a);
    b = absValue(b);
    while (b != 0) {
        cpp_int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

struct Fraction {
    cpp_int num, den;

    Fraction(cpp_int n = 0, cpp_int d = 1) {
        num = n;
        den = d;
        reduce();
    }

    void reduce() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        cpp_int gcd = getGcd(num, den);
        num /= gcd;
        den /= gcd;
    }

    Fraction operator + (const Fraction &other) const {
        return Fraction(num * other.den + other.num * den, den * other.den);
    }

    Fraction operator - (const Fraction &other) const {
        return Fraction(num * other.den - other.num * den, den * other.den);
    }

    Fraction operator * (const Fraction &other) const {
        return Fraction(num * other.num, den * other.den);
    }

    Fraction operator / (const Fraction &other) const {
        return Fraction(num * other.den, den * other.num);
    }
};

Fraction getSum(Fraction ratio, int count) {
    Fraction sum(0), power(1);
    for (int i = 0; i < count; i++) {
        sum = sum + power;
        power = power * ratio;
    }
    return sum;
}

Fraction solveCase(int p, int q, int k1, int k2) {
    Fraction safe(q - p, q), out(p, q);
    Fraction eBase(0), eCoef(0), fBase(0), fCoef(0), e1(0), f1(0);
    if (k1 > 1) {
        Fraction sum = getSum(safe, k1 - 1);
        eBase = sum;
        eCoef = out * sum;
    }
    if (k2 > 1) {
        Fraction sum = getSum(out, k2 - 1);
        fBase = sum;
        fCoef = safe * sum;
    }
    if (k1 > 1 && k2 > 1) {
        e1 = (eBase + eCoef * fBase) / (Fraction(1) - eCoef * fCoef);
        f1 = fBase + fCoef * e1;
    } else if (k1 > 1) {
        e1 = eBase;
    } else if (k2 > 1) {
        f1 = fBase;
    }
    return Fraction(1) + safe * e1 + out * f1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, caseId, p, q, k1, k2;
    cin >> testCount;
    for (caseId = 1; caseId <= testCount; caseId++) {
        cin >> p >> q >> k1 >> k2;
        Fraction answer = solveCase(p, q, k1, k2);
        cout << "Case " << caseId << ": " << answer.num << " / " << answer.den << '\n';
    }
    return 0;
}
