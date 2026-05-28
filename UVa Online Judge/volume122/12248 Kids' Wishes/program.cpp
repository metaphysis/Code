// Kids' Wishes
// UVa ID: 12248
// Verdict: Accepted
// Submission Date: 2026-05-28
// UVa Run Time: 0.320s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
set<int> g[N];      // 邻接表，使用 set 自动去重
bool vis[N];        // DFS 访问标记
int deg[N];         // 每个顶点的度数
map<int, int> mp;   // 坐标压缩映射

// DFS 遍历连通分量
// u: 当前顶点，p: 父节点，cycle: 引用参数，标记是否发现环
bool dfs(int u, int p, bool &cycle) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (v == p) continue;
        if (vis[v]) {
            cycle = 1;      // 遇到已访问且非父节点的顶点 → 发现环
            continue;
        }
        if (!dfs(v, u, cycle)) return 0;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    long long K; int W;
    while (cin >> K >> W, K || W) {
        // 清空数据结构
        mp.clear();
        for (int i = 1; i <= W * 2; ++i) {
            g[i].clear();
            deg[i] = vis[i] = 0;
        }
        
        int cnt = 0;    // 实际出现过的不同顶点数
        for (int i = 0; i < W; ++i) {
            int a, b; cin >> a >> b;
            if (a == b) continue;           // 自环无效
            // 坐标压缩
            if (!mp.count(a)) mp[a] = ++cnt;
            if (!mp.count(b)) mp[b] = ++cnt;
            int u = mp[a], v = mp[b];
            // 去重
            if (g[u].count(v)) continue;
            g[u].insert(v); g[v].insert(u);
            deg[u]++; deg[v]++;
        }
        
        // 检查度数是否超过 2
        bool ok = 1;
        for (int i = 1; i <= cnt; ++i) {
            if (deg[i] > 2) { ok = 0; break; }
        }
        if (!ok) { cout << "N\n"; continue; }
        
        // 没有边的情况：所有孩子都是孤立点，总能排成环
        if (cnt == 0) { cout << "Y\n"; continue; }
        
        int chain = 0, cycle = 0;
        for (int i = 1; i <= cnt; ++i) {
            if (!vis[i] && deg[i]) {
                bool isCycle = 0;
                if (!dfs(i, -1, isCycle)) { ok = 0; break; }
                if (isCycle) cycle++;
                else chain++;
            }
        }
        
        if (!ok) cout << "N\n";
        else if (cycle == 1 && cnt == K && chain == 0) cout << "Y\n";
        else if (cycle == 0) cout << "Y\n";
        else cout << "N\n";
    }
    return 0;
}
