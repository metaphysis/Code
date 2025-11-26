// Bloques
// UVa ID: 10844
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.600s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int BASE = 10000;

vector<int> add(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int carry = 0;
    size_t len = max(a.size(), b.size());
    for (size_t i = 0; i < len || carry; i++) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        res.push_back(carry % BASE);
        carry /= BASE;
    }
    return res;
}

void printBigInt(const vector<int>& num) {
    cout << num.back();
    for (int i = num.size() - 2; i >= 0; i--) {
        cout << setw(4) << setfill('0') << num[i];
    }
}

int main() {
    const int MAX_N = 900;
    vector<vector<vector<int>>> bell(MAX_N + 1);
    
    // 初始化贝尔三角形
    bell[0].resize(1);
    bell[0][0] = {1};
    
    // 使用贝尔三角形递推计算所有贝尔数
    for (int n = 1; n <= MAX_N; n++) {
        bell[n].resize(n + 1);
        // B(n,0) = B(n-1,n-1)
        bell[n][0] = bell[n - 1][n - 1];
        // B(n,k) = B(n,k-1) + B(n-1,k-1)
        for (int k = 1; k <= n; k++) {
            bell[n][k] = add(bell[n][k - 1], bell[n - 1][k - 1]);
        }
    }
    
    // 处理输入输出
    int n;
    while (cin >> n && n != 0) {
        cout << n << ", ";
        printBigInt(bell[n][0]);
        cout << endl;
    }
    
    return 0;
}
