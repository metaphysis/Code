// Boxes of Chocolates Again
// UVa ID: 10590
// Verdict: Accepted
// Submission Date: 2025-11-10
// UVa Run Time: 0.320s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class BigInt {
private:
    vector<int> digits;
    static const int BASE = 10000;
    static const int BASE_DIGITS = 4;
    
public:
    BigInt() : digits(1, 0) {}
    
    BigInt(long long num) {
        if (num == 0) digits.push_back(0);
        while (num > 0) {
            digits.push_back(num % BASE);
            num /= BASE;
        }
    }
    
    BigInt& operator+=(const BigInt& other) {
        int carry = 0;
        int maxSize = max(digits.size(), other.digits.size());
        
        digits.resize(maxSize, 0);
        
        for (int i = 0; i < maxSize; i++) {
            int sum = digits[i] + (i < other.digits.size() ? other.digits[i] : 0) + carry;
            digits[i] = sum % BASE;
            carry = sum / BASE;
        }
        
        if (carry > 0) {
            digits.push_back(carry);
        }
        
        return *this;
    }
    
    friend ostream& operator<<(ostream& os, const BigInt& num) {
        os << num.digits.back();
        for (int i = num.digits.size() - 2; i >= 0; i--) {
            os << setw(BASE_DIGITS) << setfill('0') << num.digits[i];
        }
        return os;
    }
};

int main() {
    const int MAX_N = 5000;
    
    vector<BigInt> dp(MAX_N + 1);
    dp[0] = BigInt(1);
    
    for (int maxNum = 1; maxNum <= MAX_N; maxNum++) {
        for (int j = maxNum; j <= MAX_N; j++) {
            dp[j] += dp[j - maxNum];
        }
    }
    
    int n;
    while (cin >> n) {
        cout << dp[n] << endl;
    }
    
    return 0;
}
