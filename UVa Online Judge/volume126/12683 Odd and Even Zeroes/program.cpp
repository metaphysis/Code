// Odd and Even Zeroes
// UVa ID: 12683
// Verdict: Accepted
// Submission Date: 2026-02-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> digits;          // 存储 n 的五进制表示，低位在前
ll dp[30][2][2];             // dp[pos][parity][tight]

// 数位 DFS
ll dfs(int pos, int parity, int tight) {
    if (pos == -1) return (parity == 0) ? 1 : 0;
    if (dp[pos][parity][tight] != -1) return dp[pos][parity][tight];

    int up = tight ? digits[pos] : 4;   // 当前位能取的最大值
    ll res = 0;

    for (int d = 0; d <= up; ++d) {
        int newParity = parity;
        // 如果当前位是奇数位（从 1 开始计数，即 pos 为奇数）
        if (pos % 2 == 1) {
            newParity ^= (d & 1);       // 更新奇偶性
        }
        res += dfs(pos - 1, newParity, tight && d == up);
    }

    return dp[pos][parity][tight] = res;
}

// 计算答案
ll countEvenZ(ll n) {
    if (n < 0) return 0;
    digits.clear();
    ll m = n;
    while (m > 0) {
        digits.push_back(m % 5);
        m /= 5;
    }
    if (digits.empty()) digits.push_back(0);   // n = 0 的情况

    memset(dp, -1, sizeof dp);
    return dfs(digits.size() - 1, 0, 1);
}

int main() {
    ll n;
    while (cin >> n) {
        if (n == -1) break;
        cout << countEvenZ(n) << "\n";
    }
    return 0;
}
