#include <bits/stdc++.h>
using namespace std;

struct Mat {
    long long a[2][2];
};

Mat mulMat(const Mat &x, const Mat &y) {
    Mat z = {};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                z.a[i][j] = (z.a[i][j] + x.a[i][k] * y.a[k][j]) % 1000;
    return z;
}

Mat powMat(Mat x, long long n) {
    Mat r = {};
    r.a[0][0] = 1;
    r.a[1][1] = 1;
    while (n > 0) {
        if (n & 1) r = mulMat(r, x);
        x = mulMat(x, x);
        n >>= 1;
    }
    return r;
}

string getOrd(long long n) {
    long long x = n % 100;
    if (x >= 11 && x <= 13) return "th";
    if (n % 10 == 1) return "st";
    if (n % 10 == 2) return "nd";
    if (n % 10 == 3) return "rd";
    return "th";
}

string getName(char type) {
    if (type == 'G') return "Golden";
    if (type == 'S') return "Silver";
    return "Bronze";
}

void getPara(char type, long long &p, long long &a0, long long &a1, long double &alpha) {
    if (type == 'G') {
        p = 1;
        a0 = 2;
        a1 = 1;
        alpha = (1.0L + sqrtl(5.0L)) / 2.0L;
    } else if (type == 'S') {
        p = 2;
        a0 = 2;
        a1 = 2;
        alpha = 1.0L + sqrtl(2.0L);
    } else {
        p = 3;
        a0 = 2;
        a1 = 3;
        alpha = (3.0L + sqrtl(13.0L)) / 2.0L;
    }
}

long long getSmall(long long n, char type) {
    long long p, a0, a1, x0, x1, x2;
    long double alpha;
    if (n == 0) return 1;
    if (type == 'G' && n == 1) return 2;
    getPara(type, p, a0, a1, alpha);
    if (n == 1) return a1;
    x0 = a0;
    x1 = a1;
    for (long long i = 2; i <= n; i++) {
        x2 = p * x1 + x0;
        x0 = x1;
        x1 = x2;
    }
    return x1;
}

string getLarge(long long n, char type) {
    long long p, a0, a1, first, last, digit;
    long double alpha, value, frac;
    Mat base = {};
    getPara(type, p, a0, a1, alpha);
    base.a[0][0] = p;
    base.a[0][1] = 1;
    base.a[1][0] = 1;
    Mat r = powMat(base, n - 1);
    last = (r.a[0][0] * a1 + r.a[0][1] * a0) % 1000;
    value = n * log10l(alpha);
    digit = (long long)floorl(value) + 1;
    frac = value - floorl(value);
    first = (long long)floorl(powl(10.0L, frac + 2.0L));
    string tail = to_string(last);
    while (tail.size() < 3) tail = "0" + tail;
    return to_string(first) + "..." + tail + "(" + to_string(digit) + " digits)";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, value;
    char type;
    while (cin >> n >> type) {
        long long p, a0, a1;
        long double alpha, logVal;
        getPara(type, p, a0, a1, alpha);
        logVal = n * log10l(alpha);
        cout << "The " << n << getOrd(n) << " " << getName(type) << " Power is ";
        if (n == 0) cout << "1";
        else if (logVal < 9.0L) {
            value = getSmall(n, type);
            cout << value;
        } else {
            cout << getLarge(n, type);
        }
        cout << ".\n";
    }
    return 0;
}
