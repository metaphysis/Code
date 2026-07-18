// Prefix Codes
// UVa ID: 12057
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const long long INF = 4e18;

int n;
long long p[MAXN], pref[MAXN];
long long dp[MAXN][MAXN];
int best[MAXN][MAXN];
vector<string> code;

void build(int l, int r, string prefix) {
    if (l == r) {
        code[l] = prefix;
        return;
    }
    int k = best[l][r];
    build(l, k, prefix + "0");
    build(k + 1, r, prefix + "1");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool firstCase = true;
    while (cin >> n && n != 0) {
        // 读入概率并转为整数（乘以10000）
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s; // 格式 "0.dddd"
            // 提取小数部分四位数字
            int val = (s[2] - '0') * 1000 + (s[3] - '0') * 100 + (s[4] - '0') * 10 + (s[5] - '0');
            p[i] = val;
        }
        // 前缀和
        pref[0] = 0;
        for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + p[i];
        // 初始化 dp
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dp[i][j] = (i == j ? 0 : INF);
        // 区间长度从 2 到 n
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                long long sum = pref[j + 1] - pref[i];
                for (int k = i; k < j; ++k) {
                    long long cost = dp[i][k] + dp[k + 1][j] + sum;
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                        best[i][j] = k;
                    }
                }
            }
        }
        // 构建编码
        code.assign(n, "");
        if (n > 0) build(0, n - 1, "");
        // 输出
        if (!firstCase) cout << '\n';
        firstCase = false;
        double avg = dp[0][n - 1] / 10000.0;
        cout << fixed << setprecision(4) << avg << '\n';
        for (int i = 0; i < n; ++i) cout << code[i] << '\n';
    }
    return 0;
}
