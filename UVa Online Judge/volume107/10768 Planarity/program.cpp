// Planarity
// UVa ID: 10768
// Verdict: Accepted
// Submission Date: 2025-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 21; // 最大顶点数

int n, m; // 顶点数和边数
bool adj[MAX_N][MAX_N]; // 邻接矩阵
bool removed[MAX_N]; // 标记顶点是否被删除
int degree[MAX_N]; // 每个顶点的度数

// 计算每个顶点的度数
void computeDegrees() {
    for (int i = 1; i <= n; i++) {
        degree[i] = 0;
        for (int j = 1; j <= n; j++)
            if (adj[i][j] && !removed[j])
                degree[i]++;
    }
}

// 移除度数为1的顶点
bool removeDegreeOne() {
    bool changed = false;
    for (int i = 1; i <= n; i++) {
        if (!removed[i] && degree[i] == 1) {
            removed[i] = true;
            changed = true;
        }
    }
    return changed;
}

// 移除度数为2的顶点，并用新边替代
bool removeDegreeTwo() {
    bool changed = false;
    for (int v = 1; v <= n; v++) {
        if (removed[v] || degree[v] != 2) continue;
        // 找到两个相邻顶点
        int neighbors[2], idx = 0;
        for (int u = 1; u <= n && idx < 2; u++)
            if (adj[v][u] && !removed[u])
                neighbors[idx++] = u;
        if (idx != 2) continue;
        int a = neighbors[0], b = neighbors[1];
        // 如果a和b之间没有边，则添加一条新边
        if (!adj[a][b]) {
            adj[a][b] = adj[b][a] = true;
            changed = true;
        }
        removed[v] = true; // 移除顶点v
    }
    return changed;
}

// 检查是否包含 K5 子图
bool hasK5() {
    // 选择5个未被删除的顶点
    vector<int> verts;
    for (int i = 1; i <= n; i++)
        if (!removed[i]) verts.push_back(i);
    if (verts.size() < 5) return false;
    // 检查所有5元组
    int sz = verts.size();
    for (int i1 = 0; i1 < sz; i1++)
        for (int i2 = i1 + 1; i2 < sz; i2++)
            for (int i3 = i2 + 1; i3 < sz; i3++)
                for (int i4 = i3 + 1; i4 < sz; i4++)
                    for (int i5 = i4 + 1; i5 < sz; i5++) {
                        int v1 = verts[i1], v2 = verts[i2], v3 = verts[i3], v4 = verts[i4], v5 = verts[i5];
                        if (adj[v1][v2] && adj[v1][v3] && adj[v1][v4] && adj[v1][v5] &&
                            adj[v2][v3] && adj[v2][v4] && adj[v2][v5] &&
                            adj[v3][v4] && adj[v3][v5] &&
                            adj[v4][v5])
                            return true;
                    }
    return false;
}

// 检查是否包含 K3,3 子图
bool hasK33() {
    vector<int> verts;
    for (int i = 1; i <= n; i++)
        if (!removed[i]) verts.push_back(i);
    if (verts.size() < 6) return false;
    int sz = verts.size();
    // 尝试所有划分为两个集合的方式，每个集合3个顶点
    vector<int> perm(sz);
    for (int i = 0; i < sz; i++) perm[i] = verts[i];
    do {
        // 前3个作为集合A，后3个作为集合B
        bool ok = true;
        for (int i = 0; i < 3 && ok; i++)
            for (int j = 3; j < 6 && ok; j++)
                if (!adj[perm[i]][perm[j]]) ok = false;
        if (ok) return true;
    } while (next_permutation(perm.begin(), perm.end()));
    return false;
}

// 判断图是否为平面图
bool isPlanar() {
    memset(removed, 0, sizeof removed);
    while (true) {
        computeDegrees();
        if (removeDegreeOne()) continue;
        if (removeDegreeTwo()) continue;
        break; // 无法继续简化
    }
    // 根据 Kuratowski 定理检查
    if (hasK5() || hasK33()) return false;
    return true;
}

int main() {
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        memset(adj, 0, sizeof adj);
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u][v] = adj[v][u] = true;
        }
        if (isPlanar()) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
