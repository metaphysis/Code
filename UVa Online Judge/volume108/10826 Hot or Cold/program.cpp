// Hot or Cold
// UVa ID: 10826
// Verdict: Accepted
// Submission Date: 2025-12-24
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310, INF = 0x3f3f3f3f;

// dp[length][dist] 还需要的最小猜测次数
int dp[MAXN][MAXN];

// 计算在区间 [l, r] 内，已知上次猜测是 last 时，还需要的最小猜测次数
int dfs(int l, int r, int last) {
    // 区间只剩一个数
    if (l == r) return (last == l) ? 1 : 2;
    // 压缩状态：length = 区间长度，dist = last到边界的距离
    int length = r - l;
    int dist = (last >= l) ? (last - l) : (r - last);
    // 记忆化
    if (~dp[length][dist]) return dp[length][dist];
    int best = INF;
    // 枚举当前猜测点 g
    for (int g = l; g <= r; ++g) {
        if (g == last) continue;  // 不能重复猜同一个数
        // 计算分界点：|t-g| < |t-last| 等价于 t > mid
        int mid1 = (g + last) / 2;      // 向下取整
        int mid2 = (g + last + 1) / 2;  // 向上取整
        int hot = 0;   // "更热"情况
        int cold = 0;  // "更冷"情况
        if (g < last) {
            // g 在 last 左边
            // "更热": 目标在右边 [max(l,mid2), r]
            if (mid2 <= r) hot = dfs(max(l, mid2), r, g);
            // "更冷": 目标在左边 [l, min(r,mid1)]
            cold = dfs(l, min(r, mid1), g);
        } else {
            // g 在 last 右边
            // "更热": 目标在左边 [l, min(r,mid1)]
            if (mid1 >= l) hot = dfs(l, min(r, mid1), g);
            // "更冷": 目标在右边 [max(l,mid2), r]
            cold = dfs(max(l, mid2), r, g);
        }
        // 最坏情况 + 当前这次猜测
        int worst = max(hot, cold) + 1;
        best = min(best, worst);
    }
    return dp[length][dist] = best;
}

int main() {
    // 初始化记忆化数组
    memset(dp, -1, sizeof dp);
    int n;
    while (cin >> n && n) {
        int answer = INF;
        // 第一次猜测可以选择任意位置
        for (int first = 1; first <= n; ++first) {
            answer = min(answer, dfs(1, n, first));
        }
        cout << answer << " guess(es) required." << endl;
    }
    return 0;
}
