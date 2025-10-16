// The Battle of Chibi
// UVa ID: 12983
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.520s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 1005;

int T, N, M;
int a[MAXN];
int dp[MAXN][MAXN];

// Fenwick Tree
class Fenwick {
    int n;
    vector<int> bit;
public:
    Fenwick(int n) : n(n), bit(n+1, 0) {}
    void update(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] = (bit[idx] + delta) % MOD;
        }
    }
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum = (sum + bit[idx]) % MOD;
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N >> M;
        vector<int> vals;
        for (int i = 1; i <= N; i++) {
            cin >> a[i];
            vals.push_back(a[i]);
        }

        // 离散化
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int sz = vals.size();
        for (int i = 1; i <= N; i++) {
            a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
        }

        // 初始化 dp
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= N; i++) {
            dp[i][1] = 1;
        }

        // DP
        for (int l = 2; l <= M; l++) {
            Fenwick ft(sz);
            for (int i = 1; i <= N; i++) {
                dp[i][l] = ft.query(a[i] - 1); // 所有小于 a[i] 的 dp[j][l-1] 之和
                ft.update(a[i], dp[i][l-1]);   // 加入 dp[i][l-1] 到树状数组
            }
        }

        // 计算结果
        int ans = 0;
        for (int i = 1; i <= N; i++) {
            ans = (ans + dp[i][M]) % MOD;
        }
        cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}
