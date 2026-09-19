#include <bits/stdc++.h>
using namespace std;

bool hasAll(const array<int, 4> &cnt) {
    for (int k = 0; k < 4; k++) if (cnt[k] == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int n, m, nodeCount, timer = 0, answer = -1;
        cin >> n >> m;
        nodeCount = 2 * n * m;
        vector<string> grid(n);
        for (int i = 0; i < n; i++) cin >> grid[i];
        vector<vector<int>> graph(nodeCount);
        vector<int> border(nodeCount, 0), dfn(nodeCount, 0), low(nodeCount, 0), parent(nodeCount, -1), nextEdge(nodeCount, 0), dfsStack, component;
        vector<array<int, 4>> subCnt(nodeCount);
        vector<char> isClear(nodeCount, false);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int base = 2 * (i * m + j);
                bool isHorizontal = (i + j) % 2 == 0;
                for (int k = 0; k < 2; k++) {
                    int u = base + k;
                    isClear[u] = grid[i][2 * j + k] == '0';
                    if (i == 0 && (isHorizontal || k == 0)) border[u] |= 1;
                    if (i == n - 1 && (isHorizontal || k == 1)) border[u] |= 2;
                    if (j == 0 && (!isHorizontal || k == 0)) border[u] |= 4;
                    if (j == m - 1 && (!isHorizontal || k == 1)) border[u] |= 8;
                    for (int b = 0; b < 4; b++) subCnt[u][b] = (border[u] >> b) & 1;
                }
            }
        }
        auto addEdge = [&](int u, int v) {
            if (!isClear[u] || !isClear[v]) return;
            graph[u].push_back(v);
            graph[v].push_back(u);
        };
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int base = 2 * (i * m + j);
                bool isHorizontal = (i + j) % 2 == 0;
                addEdge(base, base + 1);
                if (j + 1 < m) {
                    int rightBase = base + 2;
                    if (isHorizontal) {
                        addEdge(base + 1, rightBase);
                        addEdge(base + 1, rightBase + 1);
                    } else {
                        addEdge(base, rightBase);
                        addEdge(base + 1, rightBase);
                    }
                }
                if (i + 1 < n) {
                    int downBase = base + 2 * m;
                    if (isHorizontal) {
                        addEdge(base, downBase);
                        addEdge(base + 1, downBase);
                    } else {
                        addEdge(base + 1, downBase);
                        addEdge(base + 1, downBase + 1);
                    }
                }
            }
        }
        for (int start = 0; start < nodeCount; start++) {
            if (!isClear[start] || dfn[start] != 0) continue;
            dfsStack.clear();
            component.clear();
            dfsStack.push_back(start);
            component.push_back(start);
            dfn[start] = low[start] = ++timer;
            while (!dfsStack.empty()) {
                int u = dfsStack.back();
                if (nextEdge[u] < static_cast<int>(graph[u].size())) {
                    int v = graph[u][nextEdge[u]++];
                    if (dfn[v] == 0) {
                        parent[v] = u;
                        dfn[v] = low[v] = ++timer;
                        dfsStack.push_back(v);
                        component.push_back(v);
                    } else if (v != parent[u]) low[u] = min(low[u], dfn[v]);
                } else {
                    dfsStack.pop_back();
                    if (parent[u] != -1) {
                        int p = parent[u];
                        low[p] = min(low[p], low[u]);
                        for (int k = 0; k < 4; k++) subCnt[p][k] += subCnt[u][k];
                    }
                }
            }
            if (!hasAll(subCnt[start])) continue;
            bool isMinimal = true;
            for (int u : component) {
                array<int, 4> restCnt = subCnt[start];
                for (int k = 0; k < 4; k++) restCnt[k] -= (border[u] >> k) & 1;
                for (int v : graph[u]) {
                    if (parent[v] != u || low[v] < dfn[u]) continue;
                    if (hasAll(subCnt[v])) {
                        isMinimal = false;
                        break;
                    }
                    for (int k = 0; k < 4; k++) restCnt[k] -= subCnt[v][k];
                }
                if (!isMinimal) break;
                if (hasAll(restCnt)) {
                    isMinimal = false;
                    break;
                }
            }
            if (isMinimal) answer = static_cast<int>(component.size());
            break;
        }
        if (answer == -1) cout << "NO MINIMAL CORRIDOR\n";
        else cout << answer << '\n';
    }
    return 0;
}
