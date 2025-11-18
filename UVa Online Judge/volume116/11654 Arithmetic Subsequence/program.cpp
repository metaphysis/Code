// Arithmetic Subsequence
// UVa ID: 11654
// Verdict: Accepted
// Submission Date: 2025-11-15
// UVa Run Time: 0.150s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 10000007;

int main() {
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<unordered_map<long long, int>> dp(n);
        long long r = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                long long d = a[i] - a[j];
                dp[i][d] = (dp[i][d] + dp[j][d] + 1) % MOD;
                r = (r + dp[j][d] + 1) % MOD;
            }
        }
        // 在线测试数据将整个序列也认为是真子集，只要符合算术序列的定义，所以不需特判
        cout << "Case " << cs << ": " << r + n << endl;
    }
    return 0;
}
