// The Perspectographer
// UVa ID: 10661
// Verdict: Accepted
// Submission Date: 2026-01-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int m;
vector<int> graph[20];
int color[20];
int nodeOrder[20];
int maxCliqueSize;  // 最大团大小，作为颜色数的下界

// 计算最大团大小（Bron–Kerbosch算法）
int maxClique() {
    int maxSize = 0;
    // 使用位掩码表示集合
    vector<int> adjMask(m);
    for (int i = 0; i < m; ++i) {
        int mask = 0;
        for (int v : graph[i]) mask |= (1 << v);
        adjMask[i] = mask;
    }
    
    function<void(int, int, int)> dfsClique = [&](int r, int p, int x) {
        if (p == 0 && x == 0) {
            maxSize = max(maxSize, r);
            return;
        }
        // 选择度最大的顶点作为枢轴
        int u = -1, maxDeg = -1;
        int unionSet = p | x;
        while (unionSet) {
            int v = __builtin_ctz(unionSet);
            int deg = __builtin_popcount(adjMask[v] & p);
            if (deg > maxDeg) {
                maxDeg = deg;
                u = v;
            }
            unionSet &= unionSet - 1;
        }
        
        int candidates = p & ~adjMask[u];
        while (candidates) {
            int v = __builtin_ctz(candidates);
            dfsClique(r + 1, p & adjMask[v], x & adjMask[v]);
            p &= ~(1 << v);
            x |= (1 << v);
            candidates &= candidates - 1;
        }
    };
    
    dfsClique(0, (1 << m) - 1, 0);
    return maxSize;
}

// 检查节点v能否染颜色c
bool canColor(int v, int c) {
    for (int u : graph[v]) if (color[u] == c) return false;
    return true;
}

// 尝试用k种颜色着色
bool dfs(int idx, int k) {
    if (idx == m) return true;
    int v = nodeOrder[idx];
    
    // 剪枝：如果已经用了太多颜色，或者不可能在k种颜色内完成
    int usedColors = 0;
    bool colorUsed[20] = {false};
    for (int i = 0; i < m; ++i) if (color[i] != -1) colorUsed[color[i]] = true;
    for (int i = 0; i < k; ++i) if (colorUsed[i]) usedColors++;
    
    // 如果剩下的节点数 > (k - usedColors) * 某个上界，可以剪枝，但这里简化
    // 优先尝试已用过的颜色（减少颜色数）
    for (int c = 0; c < k; ++c) {
        if (!colorUsed[c] && usedColors >= k) continue;  // 颜色数已达上限
        if (canColor(v, c)) {
            color[v] = c;
            bool newColor = !colorUsed[c];
            if (dfs(idx + 1, k)) return true;
            color[v] = -1;
        }
    }
    return false;
}

// 检查k种颜色是否可行
bool check(int k) {
    memset(color, -1, sizeof(color));
    return dfs(0, k);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> m;
        int p;
        cin >> p;
        
        for (int i = 0; i < m; ++i) graph[i].clear();
        
        // 读入图
        while (p--) {
            char a, b;
            cin >> a >> b;
            int u = a - 'A';
            int v = b - 'A';
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        // 计算最大团大小作为下界
        maxCliqueSize = maxClique();
        
        // 按度从大到小排序节点
        int degree[20] = {0};
        for (int i = 0; i < m; ++i) degree[i] = graph[i].size();
        iota(nodeOrder, nodeOrder + m, 0);
        sort(nodeOrder, nodeOrder + m, [&](int a, int b) {
            return degree[a] > degree[b];
        });
        
        // 从最大团大小开始尝试
        int ans = m;
        for (int k = maxCliqueSize; k <= m; ++k) {
            if (check(k)) {
                ans = k;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
