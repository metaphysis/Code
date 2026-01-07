// Minimizing Maximizer
// UVa ID: 1322
// Verdict: Accepted
// Submission Date: 2026-01-02
// UVa Run Time: 0.270s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAX_N = 50005;
int dp[MAX_N];
int segTree[4 * MAX_N];

// 更新线段树：将位置 idx 的值设为 value
void update(int node, int left, int right, int idx, int value) {
    if (left == right) {
        segTree[node] = value;
        return;
    }
    int mid = (left + right) / 2;
    if (idx <= mid) update(node * 2, left, mid, idx, value);
    else update(node * 2 + 1, mid + 1, right, idx, value);
    segTree[node] = min(segTree[node * 2], segTree[node * 2 + 1]);
}

// 查询区间 [ql, qr] 的最小值
int query(int node, int left, int right, int ql, int qr) {
    if (qr < left || ql > right) return INF;
    if (ql <= left && right <= qr) return segTree[node];
    int mid = (left + right) / 2;
    return min(query(node * 2, left, mid, ql, qr),
               query(node * 2 + 1, mid + 1, right, ql, qr));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        // 初始化 dp 数组
        for (int i = 1; i <= n; i++) dp[i] = INF;
        dp[1] = 0;
        // 初始化线段树
        for (int i = 0; i < 4 * MAX_N; i++) segTree[i] = INF;
        update(1, 1, n, 1, 0);
        for (int k = 0; k < m; k++) {
            int i, j;
            cin >> i >> j;
            if (i > j) swap(i, j);  // 确保 i < j
            // 查询 dp[i] 到 dp[j-1] 的最小值
            int minVal = query(1, 1, n, i, j - 1);
            if (minVal + 1 < dp[j]) {
                dp[j] = minVal + 1;
                update(1, 1, n, j, dp[j]);
            }
        }
        cout << dp[n] << "\n";
        if (t) cout << "\n";  // 测试用例之间输出空行
    }
    return 0;
}
