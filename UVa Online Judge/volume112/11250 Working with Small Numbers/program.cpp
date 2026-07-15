// Working with Small Numbers
// UVa ID: 11250
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.460s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

class BigInt {
    string digits;
public:
    BigInt() : digits("0") {}
    BigInt(unsigned long long n) { digits = to_string(n); }
    BigInt(const string& s) { digits = s; normalize(); }

    void normalize() {
        size_t pos = digits.find_first_not_of('0');
        if (pos == string::npos) digits = "0";
        else digits = digits.substr(pos);
    }

    bool isZero() const { return digits == "0"; }

    int compare(const BigInt& other) const {
        if (digits.size() != other.digits.size())
            return digits.size() < other.digits.size() ? -1 : 1;
        if (digits == other.digits) return 0;
        return digits < other.digits ? -1 : 1;
    }

    bool operator==(const BigInt& o) const { return digits == o.digits; }
    bool operator!=(const BigInt& o) const { return !(*this == o); }
    bool operator<(const BigInt& o) const { return compare(o) < 0; }
    bool operator>(const BigInt& o) const { return compare(o) > 0; }
    bool operator>=(const BigInt& o) const { return !(*this < o); }

    BigInt operator+(const BigInt& o) const {
        string a = digits, b = o.digits;
        if (a.size() < b.size()) swap(a, b);
        int carry = 0;
        int i = (int)a.size() - 1, j = (int)b.size() - 1;
        for (; i >= 0; --i, --j) {
            int sum = (a[i] - '0') + (j >= 0 ? b[j] - '0' : 0) + carry;
            carry = sum / 10;
            a[i] = char(sum % 10 + '0');
        }
        if (carry) a = "1" + a;
        return BigInt(a);
    }

    BigInt operator-(const BigInt& o) const {
        string a = digits, b = o.digits;
        int borrow = 0;
        int i = (int)a.size() - 1, j = (int)b.size() - 1;
        for (; i >= 0; --i, --j) {
            int diff = (a[i] - '0') - (j >= 0 ? b[j] - '0' : 0) - borrow;
            if (diff < 0) { diff += 10; borrow = 1; }
            else borrow = 0;
            a[i] = char(diff + '0');
        }
        BigInt res(a);
        res.normalize();
        return res;
    }

    BigInt operator*(const BigInt& o) const {
        string a = digits, b = o.digits;
        if (a == "0" || b == "0") return BigInt(0);
        int n = (int)a.size(), m = (int)b.size();
        vector<int> res(n + m, 0);
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int mul = (a[i] - '0') * (b[j] - '0');
                int sum = res[i + j + 1] + mul;
                res[i + j + 1] = sum % 10;
                res[i + j] += sum / 10;
            }
        }
        string s;
        for (int x : res)
            if (!(s.empty() && x == 0)) s.push_back(char(x + '0'));
        if (s.empty()) s = "0";
        return BigInt(s);
    }

    BigInt operator%(const BigInt& b) const {
        if (b.isZero()) throw runtime_error("mod by zero");
        BigInt rem("0");
        for (char ch : digits) {
            rem = rem * BigInt(10) + BigInt(ch - '0');
            while (rem >= b) rem = rem - b;
        }
        return rem;
    }

    BigInt operator/(const BigInt& divisor) const {
        if (divisor.isZero()) throw runtime_error("division by zero");
        BigInt rem("0");
        string quot;
        for (char ch : digits) {
            rem = rem * BigInt(10) + BigInt(ch - '0');
            int q = 0;
            while (rem >= divisor) { rem = rem - divisor; ++q; }
            quot.push_back(char(q + '0'));
        }
        BigInt res(quot);
        res.normalize();
        return res;
    }

    string toString() const { return digits; }
};

BigInt gcd(BigInt a, BigInt b) {
    while (!b.isZero()) {
        BigInt r = a % b;
        a = b;
        b = r;
    }
    return a;
}

BigInt getP(unsigned long long k) {
    BigInt a(k + 1), b(k + 2), c(k + 3);
    return a * b * c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long m, n;
    int caseNo = 1;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;

        BigInt Pm = getP(m);
        BigInt Pn = getP(n);

        BigInt product = Pm * Pn;
        BigInt sum = Pm + Pn;
        BigInt sixSum = BigInt(6) * sum;

        BigInt numerator = product - sixSum + BigInt(36);
        BigInt denominator = BigInt(324) * product;

        BigInt g = gcd(numerator, denominator);
        BigInt a = numerator / g;
        BigInt b = denominator / g;

        string bStr = b.toString();
        int len = (int)bStr.size();
        string line(len, '-');

        cout << "Case " << caseNo << ":" << "\n";
        cout << a.toString() << "\n";
        cout << line << "\n";
        cout << bStr << "\n";
        cout << "\n";

        ++caseNo;
    }

    return 0;
}
