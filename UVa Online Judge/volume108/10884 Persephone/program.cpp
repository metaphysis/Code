// Persephone
// UVa ID: 10884
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

class BigInteger {
private:
    static const int base = 1000000000;
    vector<int> digits;
    void trim() {
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
    }
public:
    BigInteger(long long value = 0) {
        if (value == 0) digits.push_back(0);
        while (value > 0) {
            digits.push_back(value % base);
            value /= base;
        }
    }
    void multiply(int value) {
        long long carry = 0;
        for (int &digit : digits) {
            long long current = 1LL * digit * value + carry;
            digit = current % base;
            carry = current / base;
        }
        while (carry > 0) {
            digits.push_back(carry % base);
            carry /= base;
        }
        trim();
    }
    void divide(int value) {
        long long remainder = 0;
        for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
            long long current = digits[i] + remainder * base;
            digits[i] = current / value;
            remainder = current % value;
        }
        trim();
    }
    void subtract(const BigInteger &other) {
        long long borrow = 0;
        for (int i = 0; i < static_cast<int>(digits.size()); ++i) {
            long long current = 1LL * digits[i] - borrow;
            if (i < static_cast<int>(other.digits.size())) current -= other.digits[i];
            if (current < 0) {
                current += base;
                borrow = 1;
            } else borrow = 0;
            digits[i] = static_cast<int>(current);
        }
        trim();
    }
    string toString() const {
        string result = to_string(digits.back());
        for (int i = static_cast<int>(digits.size()) - 2; i >= 0; --i) {
            string part = to_string(digits[i]);
            result += string(9 - part.size(), '0') + part;
        }
        return result;
    }
};

BigInteger calculateCombination(int total, int selected) {
    selected = min(selected, total - selected);
    BigInteger result(1);
    for (int i = 1; i <= selected; ++i) {
        result.multiply(total - selected + i);
        result.divide(i);
    }
    return result;
}

BigInteger calculateAnswer(int fenceCount) {
    if (fenceCount < 4 || fenceCount % 2 == 1) return BigInteger(0);
    if (fenceCount == 4) return BigInteger(1);
    if (fenceCount == 6) return BigInteger(2);
    int halfPerimeter = fenceCount / 2;
    BigInteger powerOfFour(1);
    for (int i = 0; i < halfPerimeter - 4; ++i) powerOfFour.multiply(4);
    BigInteger firstTerm = powerOfFour;
    firstTerm.multiply(2 * halfPerimeter + 3);
    BigInteger secondTerm = calculateCombination(2 * halfPerimeter - 8, halfPerimeter - 4);
    secondTerm.multiply(4 * (2 * halfPerimeter - 7));
    firstTerm.subtract(secondTerm);
    return firstTerm;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        int fenceCount;
        cin >> fenceCount;
        cout << "Case #" << caseIndex << ": " << calculateAnswer(fenceCount).toString() << '\n';
    }
    return 0;
}
