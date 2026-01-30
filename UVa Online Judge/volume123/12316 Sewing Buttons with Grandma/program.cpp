// Sewing Buttons with Grandma
// UVa ID: 12316
// Verdict: Accepted
// Submission Date: 2026-01-30
// UVa Run Time: 0.290s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

class BigInt {
private:
    vector<int> digits;
    static const int BASE = 10000;
    static const int WIDTH = 4;
    
public:
    BigInt() : digits(1, 0) {}
    BigInt(long long num) {
        if (num == 0) digits.push_back(0);
        while (num > 0) {
            digits.push_back(num % BASE);
            num /= BASE;
        }
    }
    
    bool isZero() const { return digits.size() == 1 && digits[0] == 0; }
    
    void trim() {
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
    }
    
    BigInt operator+(const BigInt& other) const {
        BigInt res;
        res.digits.clear();
        int carry = 0;
        int maxSize = max(digits.size(), other.digits.size());
        for (int i = 0; i < maxSize || carry; i++) {
            if (i == res.digits.size()) res.digits.push_back(0);
            int sum = carry + res.digits[i];
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            res.digits[i] = sum % BASE;
            carry = sum / BASE;
        }
        return res;
    }
    
    BigInt operator*(const BigInt& other) const {
        if (isZero() || other.isZero()) return BigInt(0);
        BigInt res(0);
        vector<long long> temp(digits.size() + other.digits.size(), 0);
        for (int i = 0; i < digits.size(); i++)
            for (int j = 0; j < other.digits.size(); j++)
                temp[i + j] += 1LL * digits[i] * other.digits[j];
        long long carry = 0;
        for (int i = 0; i < temp.size(); i++) {
            carry += temp[i];
            if (i < res.digits.size()) res.digits[i] = carry % BASE;
            else res.digits.push_back(carry % BASE);
            carry /= BASE;
        }
        while (carry) {
            res.digits.push_back(carry % BASE);
            carry /= BASE;
        }
        res.trim();
        return res;
    }
    
    friend ostream& operator<<(ostream& os, const BigInt& num) {
        os << num.digits.back();
        for (int i = (int)num.digits.size() - 2; i >= 0; i--)
            os << setw(WIDTH) << setfill('0') << num.digits[i];
        return os;
    }
};

BigInt comb[55][55];
void initComb() {
    comb[0][0] = BigInt(1);
    for (int i = 1; i < 55; i++) {
        comb[i][0] = comb[i][i] = BigInt(1);
        for (int j = 1; j < i; j++) comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }
}

int main() {
    initComb();
    int m, k;
    while (cin >> m >> k and (m != 0 or k != 0)) {
        vector<int> n(k);
        for (int i = 0; i < k; i++) cin >> n[i];
        vector<BigInt> dp(m + 1, BigInt(0));
        dp[0] = BigInt(1);
        for (int i = 0; i < k; i++) {
            vector<BigInt> newDp(m + 1, BigInt(0));
            for (int used = 0; used <= m; used++) {
                if (dp[used].isZero()) continue;
                int maxJ = min(n[i], m - used);
                for (int j = 0; j <= maxJ; j++)
                    newDp[used + j] = newDp[used + j] + (dp[used] * comb[used + j][j]);
            }
            dp = newDp;
        }
        cout << dp[m] << endl;
    }
    return 0;
}
