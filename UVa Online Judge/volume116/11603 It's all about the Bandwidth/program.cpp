// It's all about the Bandwidth
// UVa ID: 11603
// Verdict: Accepted
// Submission Date: 2025-11-17
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w > other.w; // 最大生成树
    }
};

vector<int> parent;

int findSet(int x) {
    if (parent[x] != x)
        parent[x] = findSet(parent[x]);
    return parent[x];
}

bool unionSet(int x, int y) {
    int rx = findSet(x), ry = findSet(y);
    if (rx == ry) return false;
    parent[rx] = ry;
    return true;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> t(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> t[i][j];

    // 检查三角不等式，忽略 k=i 或 k=j 的情况
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (k != i && k != j && t[i][j] < min(t[i][k], t[k][j])) {
                    cout << "Impossible\n";
                    return;
                }
            }
        }
    }

    // 构建边列表
    vector<Edge> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            edges.push_back({i, j, t[i][j]});

    sort(edges.begin(), edges.end());

    // 最大生成树
    parent.resize(n);
    for (int i = 0; i < n; i++) parent[i] = i;

    vector<vector<pair<int, int>>> tree(n);
    int mstEdges = 0;
    for (const auto& e : edges) {
        if (unionSet(e.u, e.v)) {
            tree[e.u].push_back({e.v, e.w});
            tree[e.v].push_back({e.u, e.w});
            mstEdges++;
            if (mstEdges == n - 1) break;
        }
    }

    // 输出结果
    cout << n - 1 << "\n";
    for (int u = 0; u < n; u++)
        for (const auto& nb : tree[u])
            if (u < nb.first)
                cout << u << " " << nb.first << " " << nb.second << "\n";
}

int main() {
    int N;
    cin >> N;
    for (int caseNum = 1; caseNum <= N; caseNum++) {
        cout << "Case #" << caseNum << ": ";
        solve();
    }
    return 0;
}
