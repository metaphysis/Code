#include <bits/stdc++.h>
using namespace std;

struct Fraction {
    long long num, den;
    Fraction(long long n = 0, long long d = 1) {
        if (d < 0) {
            n = -n;
            d = -d;
        }
        long long g = gcdValue(llabs(n), d);
        num = n / g;
        den = d / g;
    }
    static long long gcdValue(long long a, long long b) {
        while (b != 0) {
            long long t = a % b;
            a = b;
            b = t;
        }
        return a == 0 ? 1 : a;
    }
};

long long modValue(long long a, long long b) {
    long long r = a % b;
    return r < 0 ? r + b : r;
}

bool sameFraction(const Fraction& a, const Fraction& b) {
    return a.num == b.num && a.den == b.den;
}

void updateAnswer(const Fraction& value, bool& hasAnswer, Fraction& answer) {
    if (value.num < 0) return;
    if (!hasAnswer || value.num * answer.den < answer.num * value.den) {
        answer = value;
        hasAnswer = true;
    }
}

bool getRoot(long long a, long long b, bool& allTime, Fraction& root) {
    if (a == 0) {
        if (b != 0) return false;
        allTime = true;
        return true;
    }
    allTime = false;
    root = Fraction(-b, a);
    return true;
}

void checkOrigin(long long a1, long long b1, long long a2, long long b2, bool& hasAnswer, Fraction& answer) {
    bool allTime1, allTime2;
    Fraction root1, root2;
    if (!getRoot(a1, b1, allTime1, root1)) return;
    if (!getRoot(a2, b2, allTime2, root2)) return;
    if (allTime1 && allTime2) {
        updateAnswer(Fraction(0, 1), hasAnswer, answer);
    } else if (allTime1) {
        updateAnswer(root2, hasAnswer, answer);
    } else if (allTime2) {
        updateAnswer(root1, hasAnswer, answer);
    } else if (sameFraction(root1, root2)) {
        updateAnswer(root1, hasAnswer, answer);
    }
}

void checkCollision(long long p, long long q, long long u, long long v, long long m, bool& hasAnswer, Fraction& answer) {
    if (p != 0) {
        Fraction time(-q, p);
        if (time.num < 0) return;
        long long value = u * time.num + (v - m) * time.den;
        if (value % (360 * time.den) == 0) updateAnswer(time, hasAnswer, answer);
        return;
    }
    if (q != 0) return;
    if (u == 0) {
        if (modValue(v - m, 360) == 0) updateAnswer(Fraction(0, 1), hasAnswer, answer);
        return;
    }
    long long remainder = modValue(m - v, 360);
    long long numerator = u > 0 ? remainder : (remainder == 0 ? 0 : remainder - 360);
    updateAnswer(Fraction(numerator, u), hasAnswer, answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a1, b1, c1, d1, a2, b2, c2, d2;
    while (cin >> a1 >> b1 >> c1 >> d1 >> a2 >> b2 >> c2 >> d2) {
        if (a1 == 0 && b1 == 0 && c1 == 0 && d1 == 0 && a2 == 0 && b2 == 0 && c2 == 0 && d2 == 0) break;
        bool hasAnswer = false;
        Fraction answer;
        long long angleA = c1 - c2, angleB = d1 - d2;
        checkOrigin(a1, b1, a2, b2, hasAnswer, answer);
        checkCollision(a1 - a2, b1 - b2, angleA, angleB, 0, hasAnswer, answer);
        checkCollision(a1 + a2, b1 + b2, angleA, angleB, 180, hasAnswer, answer);
        if (hasAnswer) cout << answer.num << " " << answer.den << "\n";
        else cout << "0 0\n";
    }
    return 0;
}
