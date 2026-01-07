// Jumping Monkey
// UVa ID: 12274
// Verdict: Accepted
// Submission Date: 2026-01-03
// UVa Run Time: 0.280s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 21;

int n, m;
int neighborMask[MAXN];  // 每个节点的邻居掩码

// 并查集
int parent[MAXN];
int findSet(int x) {
    return parent[x] == x ? x : parent[x] = findSet(parent[x]);
}
bool unionSet(int x, int y) {
    x = findSet(x);
    y = findSet(y);
    if (x == y) return false;  // 已经连通，有环
    parent[x] = y;
    return true;
}

// BFS求解
void solve() {
    int fullMask = (1 << n) - 1;
    // dp[mask] = 最小步数，-1表示未访问
    vector<int> dp(1 << n, -1);
    // link[mask][0] = 前驱状态，link[mask][1] = 射击的树
    vector<pair<int, int>> link(1 << n);
    queue<int> q;
    dp[fullMask] = 0;
    q.push(fullMask);
    while (!q.empty()) {
        int mask = q.front(); q.pop();
        int steps = dp[mask];
        // 尝试射击每个可能的目标
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) continue;  // 猴子不可能在i上
            // 计算新状态
            int newMask = 0;
            for (int j = 0; j < n; j++)
                if (mask & (1 << j))
                    if (j != i)
                        newMask |= neighborMask[j]; // 猴子从j跳到所有邻居
            if (dp[newMask] == -1) {
                dp[newMask] = steps + 1;
                link[newMask] = {mask, i};
                if (newMask == 0) {
                    // 找到解，输出
                    cout << dp[newMask] << ":";
                    stack<int> path;
                    int current = newMask;
                    while (current != fullMask) {
                        path.push(link[current].second);
                        current = link[current].first;
                    }
                    while (!path.empty()) {
                        cout << ' ' << path.top();
                        path.pop();
                    }
                    cout << '\n';
                    return;
                }
                q.push(newMask);
            }
        }
    }
    // 没有找到解
    cout << "Impossible\n";
}

int main() {
    while (cin >> n >> m, n) {
        // 初始化
        for (int i = 0; i < n; i++) {
            neighborMask[i] = 0;
            parent[i] = i;
        }
        bool hasCycle = false;
        // 读入图
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            neighborMask[a] |= (1 << b);
            neighborMask[b] |= (1 << a);
            // 检测是否有环
            if (!unionSet(a, b)) hasCycle = true;
        }
        // 特殊情况：只有一棵树
        if (n == 1) {
            cout << "1: 0\n";
            continue;
        }
        // 如果有环，不可能
        if (hasCycle) {
            cout << "Impossible\n";
            continue;
        }
        // 否则求解
        solve();
    }
    return 0;
}
