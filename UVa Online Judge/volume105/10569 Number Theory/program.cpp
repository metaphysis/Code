// Number Theory
// UVa ID: 10569
// Verdict: Accepted
// Submission Date: 2025-11-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 高精度整数类（简化版，仅支持需要的操作）
class BigInt {
public:
    string digits;
    
    BigInt() {}
    BigInt(string s) : digits(s) {}
    BigInt(long long n) : digits(to_string(n)) {}
    
    // 转换为字符串
    string str() const { return digits; }
    
    // 乘法：仅实现乘以小整数（<=6）
    BigInt multiply(int n) const {
        string result;
        int carry = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            int product = (digits[i] - '0') * n + carry;
            result.push_back('0' + product % 10);
            carry = product / 10;
        }
        while (carry) {
            result.push_back('0' + carry % 10);
            carry /= 10;
        }
        reverse(result.begin(), result.end());
        return BigInt(result);
    }
};

vector<vector<string>> precomputed(101);

void precompute() {
    // n = 1: 平凡解
    precomputed[1] = {"1", "1"};
    // n = 2: 无解（费马大定理）
    precomputed[2] = {"-1", "0", "0"};
    // n = 3: 已知解
    precomputed[3] = {"71", "14", "23", "70"};
    // n = 4: 已知解
    precomputed[4] = {"100", "56", "58", "67", "69"};
    
    // 对于 n >= 5，从 n-2 的解构造
    for (int n = 5; n <= 100; n++) {
        vector<string> prev = precomputed[n - 2];
        BigInt minVal(prev[1]);  // 第一个 a_i 就是最小的
        BigInt f(prev[0]);
        
        vector<string> current;
        current.push_back(f.multiply(6).str());  // F = 6f
        current.push_back(minVal.multiply(3).str());  // 3a₁
        current.push_back(minVal.multiply(4).str());  // 4a₁
        current.push_back(minVal.multiply(5).str());  // 5a₁
        
        // 其余 a_i 都乘以 6
        for (int i = 2; i < prev.size(); i++) {
            BigInt val(prev[i]);
            current.push_back(val.multiply(6).str());
        }
        
        precomputed[n] = current;
    }
}

int main() {
    precompute();  // 预先计算所有解
    
    int t;
    cin >> t;
    for (int caseNum = 1; caseNum <= t; caseNum++) {
        int n;
        cin >> n;
        cout << "Case " << caseNum << ":";
        // 输出对应 n 的解
        for (const string& s : precomputed[n]) cout << " " << s;
        cout << "\n";
    }
    return 0;
}
