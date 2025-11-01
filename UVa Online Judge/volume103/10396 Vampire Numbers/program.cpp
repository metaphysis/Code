// Vampire Numbers
// UVa ID: 10396
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 1.380s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 使用位运算记录数字频率（每个数字 0-9 用 4 位存储，共 40 位）
long long getDigitSignature(int num) {
    long long signature = 0;
    while (num > 0) {
        int digit = num % 10;
        signature += (1LL << (digit * 4));  // 每个数字用 4 位计数
        num /= 10;
    }
    return signature;
}

// 检查是否为吸血鬼数（纯数学方法）
bool isVampireMath(int x, int y, int v, int n) {
    // 检查双0结尾
    if (x % 10 == 0 && y % 10 == 0) return false;
    
    // 检查数字组成是否相同
    long long sig_v = getDigitSignature(v);
    long long sig_xy = getDigitSignature(x * (int)pow(10, n/2) + y);
    
    return sig_v == sig_xy;
}

vector<int> findEvenVampireNumbers(int n) {
    set<int> results;
    int half = n / 2;
    int start = pow(10, half - 1);
    int end = pow(10, half) - 1;
    
    // 预计算范围
    int min_v = pow(10, n - 1);
    int max_v = pow(10, n) - 1;
    
    for (int x = start; x <= end; x++) {
        // 计算y的有效范围
        int min_y = max(x, (min_v + x - 1) / x);  // 向上取整
        int max_y = min(end, max_v / x);
        
        for (int y = min_y; y <= max_y; y++) {
            int v = x * y;
            
            // 快速检查：必须是偶数
            if ((v & 1) != 0) continue;
            
            // 使用数学方法检查数字组成
            if (isVampireMath(x, y, v, n)) {
                results.insert(v);
            }
        }
    }
    
    return vector<int>(results.begin(), results.end());
}

// 预计算并缓存结果
vector<int> getPrecomputedEvenVampires(int n) {
    static vector<int> cache4, cache6, cache8;
    static bool computed4 = false, computed6 = false, computed8 = false;
    
    switch (n) {
        case 4:
            if (!computed4) {
                cache4 = {1260, 1530, 6880};  // 已知的 4 位偶数吸血鬼数
                computed4 = true;
            }
            return cache4;
        case 6:
            if (!computed6) {
                cache6 = findEvenVampireNumbers(6);
                computed6 = true;
            }
            return cache6;
        case 8:
            if (!computed8) {
                cache8 = findEvenVampireNumbers(8);
                computed8 = true;
            }
            return cache8;
        default:
            return vector<int>();
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    vector<int> inputs;
    while (cin >> n) inputs.push_back(n);
    for (size_t i = 0; i < inputs.size(); i++) {
        vector<int> result = getPrecomputedEvenVampires(inputs[i]);
        for (int v : result) cout << v << '\n';
        cout << '\n';
    }

    return 0;
}
