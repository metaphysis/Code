// Combinatorial Summation
// UVa ID: 10694
// Verdict: Accepted
// Submission Date: 2025-11-23
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000;

// 高精度加法
vector<int> add(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int carry = 0;
    int i = a.size() - 1, j = b.size() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--];
        if (j >= 0) sum += b[j--];
        res.push_back(sum % 10);
        carry = sum / 10;
    }
    
    reverse(res.begin(), res.end());
    return res;
}

// 将整数转换为高精度数
vector<int> intToVector(int n) {
    if (n <= 0) return {0};
    vector<int> res;
    while (n > 0) {
        res.push_back(n % 10);
        n /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

// 打印高精度数
void printVector(const vector<int>& v) {
    for (int digit : v) {
        cout << digit;
    }
}

vector<vector<int>> result(MAX_N + 5);

// 预处理所有结果
void precompute() {
    result[0] = {0};
    result[1] = {1};
    
    // 使用递推关系: result[i] = result[i-1] + result[i-2] + i
    for (int i = 2; i <= 1000; i++) {
        result[i] = add(result[i-1], result[i-2]);
        result[i] = add(result[i], intToVector(i));
    }
}

int main() {
    precompute();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n <= 0) {
            cout << 0 << endl;
        } else {
            printVector(result[n]);
            cout << endl;
        }
    }
    return 0;
}
