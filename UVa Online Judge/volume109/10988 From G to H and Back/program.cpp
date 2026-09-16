#include <bits/stdc++.h>
using namespace std;

class LineGraphChecker {
private:
    int n, root;
    vector<vector<char>> adj, covered;
    vector<int> belongCount, component, rootNeighbors, bipartiteColor, componentFlip;
    vector<vector<int> > cliques, complementComponents;

private:
    bool isAdjacent(int u, int v) const { return adj[u][v] != 0; }

    bool isCovered(int u, int v) const { return covered[u][v] != 0; }

    // 判断 clique 是否可以作为一个新的 Krausz 完全子图
    bool canAddClique(const vector<int>& clique) const {
        if (clique.empty()) return false;
        // 每个顶点最多属于两个完全子图
        for (int v : clique)
            if (belongCount[v] >= 2)
                return false;
        // clique 必须是完全子图，并且其中的边不能已经被覆盖
        for (int i = 0; i < (int)clique.size(); i++) {
            for (int j = i + 1; j < (int)clique.size(); j++) {
                int u = clique[i], v = clique[j];
                if (!isAdjacent(u, v)) return false;
                if (isCovered(u, v)) return false;
            }
        }
        return true;
    }

    void addCliqueWithoutCheck(const vector<int>& clique) {
        for (int v : clique) belongCount[v]++;
        for (int i = 0; i < (int)clique.size(); i++) {
            for (int j = i + 1; j < (int)clique.size(); j++) {
                int u = clique[i];
                int v = clique[j];
                covered[u][v] = covered[v][u] = 1;
            }
        }
        cliques.push_back(clique);
    }

    void removeClique(const vector<int>& clique) {
        for (int v : clique) belongCount[v]--;
        for (int i = 0; i < (int)clique.size(); i++) {
            for (int j = i + 1; j < (int)clique.size(); j++) {
                int u = clique[i];
                int v = clique[j];
                covered[u][v] = covered[v][u] = 0;
            }
        }
    }

    bool allEdgesCovered() const {
        for (int i = 0; i < (int)component.size(); i++) {
            for (int j = i + 1; j < (int)component.size(); j++) {
                int u = component[i];
                int v = component[j];
                if (adj[u][v] && !covered[u][v]) return false;
            }
        }
        return true;
    }

    // 根据一个已经确定的完全子图，继续强制构造其他完全子图
    bool propagate() {
        int cliqueIndex = 0;
        while (cliqueIndex < (int)cliques.size()) {
            // 必须复制，不能使用引用
            vector<int> currentClique = cliques[cliqueIndex];
            for (int u : currentClique) {
                vector<int> remaining;
                // 找出 u 的所有尚未覆盖的邻边
                for (int v : component) {
                    if (v == u) continue;
                    if (adj[u][v] && !covered[u][v]) remaining.push_back(v);
                }
                if (remaining.empty()) continue;
                // u 已经属于两个团，不可能再加入新的团
                if (belongCount[u] >= 2) return false;
                vector<int> nextClique;
                nextClique.push_back(u);
                for (int v : remaining) nextClique.push_back(v);
                // Krausz 划分中，u 的所有剩余边必须同时属于 u 的另一个完全子图，因此 remaining 必须整体成团
                if (!canAddClique(nextClique)) return false;
                addCliqueWithoutCheck(nextClique);
            }
            cliqueIndex++;
        }
        return allEdgesCovered();
    }

    // 根据当前选定的 root 邻域两团划分，尝试完成整个连通分量
    bool tryCurrentPartition() {
        covered.assign(n, vector<char>(n, 0));
        belongCount.assign(n, 0);
        cliques.clear();
        vector<int> firstClique;
        vector<int> secondClique;
        firstClique.push_back(root);
        for (int v : rootNeighbors) {
            // 同一个补图连通分量内部的颜色由：bipartiteColor[v] XOR componentFlip[v] 决定
            int side = bipartiteColor[v] ^ componentFlip[v];
            if (side == 0) firstClique.push_back(v);
            else secondClique.push_back(v);
        }
        // root 可以只属于一个团，也可以属于两个团
        if (!secondClique.empty()) {
            vector<int> clique2;
            clique2.push_back(root);
            for (int v : secondClique) clique2.push_back(v);
            if (!canAddClique(firstClique)) return false;
            addCliqueWithoutCheck(firstClique);
            if (!canAddClique(clique2)) return false;
            addCliqueWithoutCheck(clique2);
        } else {
            if (!canAddClique(firstClique)) return false;
            addCliqueWithoutCheck(firstClique);
        }
        return propagate();
    }

    // 枚举 root 邻域补图各个连通分量的二分方向
    // 第一个连通分量固定方向，避免整体交换两种颜色造成重复
    bool enumeratePartitions(int index) {
        if (index == (int)complementComponents.size()) return tryCurrentPartition();
        const vector<int>& part = complementComponents[index];
        if (index == 0) {
            for (int v : part) componentFlip[v] = 0;
            return enumeratePartitions(index + 1);
        }
        for (int flip = 0; flip <= 1; flip++) {
            for (int v : part) componentFlip[v] = flip;
            if (enumeratePartitions(index + 1)) return true;
        }
        return false;
    }

    // 构造 root 邻域的补图，并检查是否二分
    bool buildRootPartition() {
        rootNeighbors.clear();
        complementComponents.clear();
        for (int v : component)
            if (v != root && adj[root][v])
                rootNeighbors.push_back(v);
        // 孤立点或只有一个点的分量可以直接接受
        if (rootNeighbors.empty()) return true;
        bipartiteColor.assign(n, -1);
        componentFlip.assign(n, 0);
        vector<char> visited(n, 0);
        for (int start : rootNeighbors) {
            if (visited[start]) continue;
            vector<int> current;
            queue<int> q;
            visited[start] = 1;
            bipartiteColor[start] = 0;
            q.push(start);
            bool bipartite = true;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                current.push_back(u);
                for (int v : rootNeighbors) {
                    if (u == v) continue;
                    // root 邻域补图中的边：原图中 u、v 不相邻
                    if (adj[u][v]) continue;
                    if (!visited[v]) {
                        visited[v] = 1;
                        bipartiteColor[v] = bipartiteColor[u] ^ 1;
                        q.push(v);
                    } else {
                        if (bipartiteColor[v] == bipartiteColor[u]) bipartite = false;
                    }
                }
            }
            if (!bipartite) return false;
            complementComponents.push_back(current);
        }
        return enumeratePartitions(0);
    }

    bool solveComponent(const vector<int>& vertices) {
        if (vertices.empty()) return true;
        if (vertices.size() == 1) return true;
        component = vertices;
        // 选取连通分量中的最小度数顶点作为 root
        root = component[0];
        int bestDegree = INT_MAX;
        for (int v : component) {
            int degree = 0;
            for (int u : component)
                if (adj[v][u])
                    degree++;
            if (degree < bestDegree) {
                bestDegree = degree;
                root = v;
            }
        }
        return buildRootPartition();
    }

public:
    explicit LineGraphChecker(const vector<vector<char>>& graph) : n((int)graph.size()), adj(graph) { }

    bool check() {
        vector<char> visited(n, 0);
        for (int start = 0; start < n; start++) {
            if (visited[start]) continue;
            vector<int> current;
            queue<int> q;
            visited[start] = 1;
            q.push(start);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                current.push_back(u);
                for (int v = 0; v < n; v++) {
                    if (adj[u][v] && !visited[v]) {
                        visited[v] = 1;
                        q.push(v);
                    }
                }
            }
            if (!solveComponent(current)) return false;
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int m, p;
        cin >> m >> p;
        vector<vector<char>> graph(m, vector<char>(m, 0));
        for (int i = 0; i < p; i++) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            graph[u][v] = graph[v][u] = 1;
        }
        LineGraphChecker checker(graph);
        cout << "Case #" << tc << ": " << (checker.check() ? "yes" : "no") << '\n';
    }
    return 0;
}
