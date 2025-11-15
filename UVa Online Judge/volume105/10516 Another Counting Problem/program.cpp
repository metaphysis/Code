// Another Counting Problem
// UVa ID: 10516
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 高精度整数类
class BigInt {
public:
    vector<int> digits;

    BigInt() {}
    
    BigInt(long long num) {
        if (num == 0) digits.push_back(0);
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
    }
    
    BigInt(const string& str) {
        for (int i = str.size() - 1; i >= 0; i--) {
            digits.push_back(str[i] - '0');
        }
        removeLeadingZeros();
    }
    
    void removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }
    
    BigInt operator+(const BigInt& other) const {
        BigInt result;
        int carry = 0;
        int maxSize = max(digits.size(), other.digits.size());
        
        for (int i = 0; i < maxSize || carry; i++) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        
        return result;
    }
    
    BigInt operator-(const BigInt& other) const {
        BigInt result;
        int borrow = 0;
        
        for (int i = 0; i < digits.size(); i++) {
            int diff = digits[i] - borrow;
            if (i < other.digits.size()) diff -= other.digits[i];
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits.push_back(diff);
        }
        
        result.removeLeadingZeros();
        return result;
    }
    
    BigInt operator*(const BigInt& other) const {
        BigInt result;
        result.digits.resize(digits.size() + other.digits.size(), 0);
        
        for (int i = 0; i < digits.size(); i++) {
            int carry = 0;
            for (int j = 0; j < other.digits.size() || carry; j++) {
                long long product = result.digits[i + j] + carry;
                if (j < other.digits.size()) product += (long long)digits[i] * other.digits[j];
                result.digits[i + j] = product % 10;
                carry = product / 10;
            }
        }
        
        result.removeLeadingZeros();
        return result;
    }
    
    BigInt pow(int exponent) const {
        BigInt result(1);
        BigInt base = *this;
        
        while (exponent > 0) {
            if (exponent & 1) {
                result = result * base;
            }
            base = base * base;
            exponent >>= 1;
        }
        
        return result;
    }
    
    string toString() const {
        string str;
        for (int i = digits.size() - 1; i >= 0; i--) {
            str += to_string(digits[i]);
        }
        return str;
    }
};

int main() {
    int n, d;
    
    while (cin >> n >> d) {
        if (n == 0 && d == 0) {
            break;
        }
        
        vector<BigInt> g(d + 2); // G[d] = 深度不超过d的树的数量
        g[0] = BigInt(1); // 深度0：只有根节点
        
        // 计算G[d]
        for (int i = 1; i <= d; i++) {
            g[i] = g[i - 1].pow(n) + BigInt(1);
        }
        
        // 计算F[d] = G[d] - G[d-1]
        BigInt result;
        if (d == 0) {
            result = g[0];
        } else {
            result = g[d] - g[d - 1];
        }
        
        cout << n << " " << d << " " << result.toString() << endl;
    }
    
    return 0;
}
