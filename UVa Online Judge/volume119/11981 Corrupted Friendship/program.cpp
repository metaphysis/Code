// Corrupted Friendship
// UVa ID: 11981
// Verdict: Accepted
// Submission Date: 2026-01-25
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> g[100005];  // 邻接表，存储每个节点的子节点（被邀请者）
long long r, cnt;       // r: 确定不是朋友的对数，cnt: 当前未访问节点数

// DFS遍历
void dfs(int u) {
    cnt--;  // 当前节点被访问，未访问节点数减1
    for (int i = 0; i < g[u].size(); i++)
        dfs(g[u][i]);      // 递归处理子节点
    r += cnt;              // 关键：累加当前未访问节点数
}

int main() {
    int T, cs = 0, N, x, y;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++) g[i].clear();
        for (int i = 1; i < N; i++) {
            scanf("%d %d", &x, &y);
            g[x].push_back(y);  // 建立有向边 x -> y
        }
        r = 0, cnt = N;  // 初始化
        dfs(1);          // 从根节点1开始DFS
        printf("Case %d: %d %lld\n", ++cs, N - 1, r);
    }
    return 0;
}
