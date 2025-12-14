// Kingdoms
// UVa ID: 12507
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, cost;
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

int findParent(vector<int>& parent, int x) {
    if (parent[x] != x) parent[x] = findParent(parent, parent[x]);
    return parent[x];
}

bool unionSets(vector<int>& parent, vector<int>& rank, int a, int b) {
    int ra = findParent(parent, a), rb = findParent(parent, b);
    if (ra == rb) return false;
    if (rank[ra] < rank[rb]) parent[ra] = rb;
    else if (rank[ra] > rank[rb]) parent[rb] = ra;
    else parent[rb] = ra, rank[ra]++;
    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> population(n + 1);
        for (int i = 1; i <= n; i++) cin >> population[i];
        vector<Edge> edges(m);
        for (int i = 0; i < m; i++) cin >> edges[i].u >> edges[i].v >> edges[i].cost;

        // 预处理所有包含城市1的子集的总人口
        int maxMask = 1 << n;
        vector<int> subsetPopulation(maxMask, 0);
        for (int mask = 0; mask < maxMask; mask++) {
            if (!(mask & 1)) continue; // 必须包含城市1（第0位）
            for (int i = 0; i < n; i++)
                if (mask & (1 << i)) subsetPopulation[mask] += population[i + 1];
        }

        int ans = 0;
        // 枚举所有包含城市1的子集
        for (int mask = 1; mask < maxMask; mask += 2) { // 保证第0位为1
            // 筛选出两端都在子集内的边
            vector<Edge> subsetEdges;
            for (const Edge& e : edges) {
                int u = e.u - 1, v = e.v - 1; // 转为0-based
                if ((mask >> u) & 1 && (mask >> v) & 1) subsetEdges.push_back(e);
            }
            sort(subsetEdges.begin(), subsetEdges.end());

            // Kruskal 求最小生成树花费
            vector<int> parent(n), rank(n, 0);
            for (int i = 0; i < n; i++) parent[i] = i;
            int cost = 0, connected = 0;
            int target = __builtin_popcount(mask) - 1; // 生成树应有 |S|-1 条边
            for (const Edge& e : subsetEdges) {
                if (unionSets(parent, rank, e.u - 1, e.v - 1)) {
                    cost += e.cost;
                    connected++;
                }
                if (connected == target) break; // 已形成生成树，提前退出
            }

            // 检查子集内所有城市是否都与首都连通
            int root = findParent(parent, 0); // 首都的根
            bool allConnected = true;
            for (int i = 0; i < n; i++) {
                if ((mask >> i) & 1 && findParent(parent, i) != root) {
                    allConnected = false;
                    break;
                }
            }

            // 如果全部连通且花费不超限，更新答案
            if (allConnected && cost <= k) ans = max(ans, subsetPopulation[mask]);
        }

        cout << ans << endl;
    }
    return 0;
}
