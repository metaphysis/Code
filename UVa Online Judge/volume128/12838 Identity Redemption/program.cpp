#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

class WeightedMatching {
private:
    static const int maxSize = 105;
    int n, nodeCount, visitTime = 0;
    Edge graph[maxSize][maxSize] = {};
    long long label[maxSize] = {};
    int mate[maxSize] = {}, slack[maxSize] = {}, root[maxSize] = {};
    int parent[maxSize] = {}, state[maxSize] = {}, seen[maxSize] = {};
    int flowerFrom[maxSize][maxSize] = {};
    vector<int> flower[maxSize];
    queue<int> bfsQueue;

    long long edgeDelta(const Edge &edge) {
        return label[edge.u] + label[edge.v] - 2 * edge.w;
    }

    void updateSlack(int u, int x) {
        if (!slack[x] || edgeDelta(graph[u][x]) < edgeDelta(graph[slack[x]][x])) slack[x] = u;
    }

    void setSlack(int x) {
        slack[x] = 0;
        for (int u = 1; u <= n; ++u) {
            if (graph[u][x].w > 0 && root[u] != x && state[root[u]] == 0) updateSlack(u, x);
        }
    }

    void pushQueue(int x) {
        if (x <= n) bfsQueue.push(x);
        else for (int child : flower[x]) pushQueue(child);
    }

    void setRoot(int x, int newRoot) {
        root[x] = newRoot;
        if (x > n) for (int child : flower[x]) setRoot(child, newRoot);
    }

    int getPosition(int b, int x) {
        int pos = int(find(flower[b].begin(), flower[b].end(), x) - flower[b].begin());
        if (pos % 2 == 1) {
            reverse(flower[b].begin() + 1, flower[b].end());
            return int(flower[b].size()) - pos;
        }
        return pos;
    }

    void setMatch(int u, int v) {
        mate[u] = graph[u][v].v;
        if (u <= n) return;
        Edge edge = graph[u][v];
        int child = flowerFrom[u][edge.u], pos = getPosition(u, child);
        for (int i = 0; i < pos; ++i) setMatch(flower[u][i], flower[u][i ^ 1]);
        setMatch(child, v);
        rotate(flower[u].begin(), flower[u].begin() + pos, flower[u].end());
    }

    void augment(int u, int v) {
        int nextRoot = root[mate[u]];
        setMatch(u, v);
        if (!nextRoot) return;
        setMatch(nextRoot, root[parent[nextRoot]]);
        augment(root[parent[nextRoot]], nextRoot);
    }

    int getLca(int u, int v) {
        ++visitTime;
        while (u || v) {
            if (u) {
                if (seen[u] == visitTime) return u;
                seen[u] = visitTime;
                u = root[mate[u]];
                if (u) u = root[parent[u]];
            }
            swap(u, v);
        }
        return 0;
    }

    void addFlower(int u, int base, int v) {
        int b = n + 1;
        while (b <= nodeCount && root[b]) ++b;
        if (b > nodeCount) nodeCount = b;
        label[b] = 0;
        state[b] = 0;
        mate[b] = mate[base];
        flower[b].clear();
        flower[b].push_back(base);
        for (int x = u, y = 0; x != base; x = root[parent[y]]) {
            flower[b].push_back(x);
            y = root[mate[x]];
            flower[b].push_back(y);
            pushQueue(y);
        }
        reverse(flower[b].begin() + 1, flower[b].end());
        for (int x = v, y = 0; x != base; x = root[parent[y]]) {
            flower[b].push_back(x);
            y = root[mate[x]];
            flower[b].push_back(y);
            pushQueue(y);
        }
        setRoot(b, b);
        for (int x = 1; x <= nodeCount; ++x) {
            graph[b][x] = {b, x, 0};
            graph[x][b] = {x, b, 0};
        }
        for (int x = 1; x <= n; ++x) flowerFrom[b][x] = 0;
        for (int child : flower[b]) {
            for (int x = 1; x <= nodeCount; ++x) {
                if (graph[child][x].w == 0) continue;
                if (graph[b][x].w == 0 || edgeDelta(graph[child][x]) < edgeDelta(graph[b][x])) {
                    graph[b][x] = graph[child][x];
                    graph[x][b] = graph[x][child];
                }
            }
            for (int x = 1; x <= n; ++x) {
                if (flowerFrom[child][x]) flowerFrom[b][x] = child;
            }
        }
        setSlack(b);
    }

    void expandFlower(int b) {
        for (int child : flower[b]) setRoot(child, child);
        int entry = flowerFrom[b][graph[b][parent[b]].u], pos = getPosition(b, entry);
        for (int i = 0; i < pos; i += 2) {
            int x = flower[b][i], next = flower[b][i + 1];
            parent[x] = graph[next][x].u;
            state[x] = 1;
            state[next] = 0;
            slack[x] = 0;
            setSlack(next);
            pushQueue(next);
        }
        state[entry] = 1;
        parent[entry] = parent[b];
        for (int i = pos + 1; i < int(flower[b].size()); ++i) {
            int x = flower[b][i];
            state[x] = -1;
            setSlack(x);
        }
        root[b] = 0;
    }

    bool processEdge(const Edge &edge) {
        int u = root[edge.u], v = root[edge.v];
        if (state[v] == -1) {
            int next = root[mate[v]];
            parent[v] = edge.u;
            state[v] = 1;
            slack[v] = slack[next] = 0;
            state[next] = 0;
            pushQueue(next);
        } else if (state[v] == 0) {
            int base = getLca(u, v);
            if (!base) {
                augment(u, v);
                augment(v, u);
                return true;
            }
            addFlower(u, base, v);
        }
        return false;
    }

    bool findAugmentingPath() {
        fill(state, state + maxSize, -1);
        fill(slack, slack + maxSize, 0);
        bfsQueue = queue<int>();
        for (int x = 1; x <= nodeCount; ++x) {
            if (root[x] == x && !mate[x]) {
                parent[x] = 0;
                state[x] = 0;
                pushQueue(x);
            }
        }
        if (bfsQueue.empty()) return false;
        while (true) {
            while (!bfsQueue.empty()) {
                int u = bfsQueue.front();
                bfsQueue.pop();
                if (state[root[u]] == 1) continue;
                for (int v = 1; v <= n; ++v) {
                    if (graph[u][v].w == 0 || root[u] == root[v]) continue;
                    if (edgeDelta(graph[u][v]) == 0) {
                        if (processEdge(graph[u][v])) return true;
                    } else updateSlack(u, root[v]);
                }
            }
            long long delta = numeric_limits<long long>::max();
            for (int u = 1; u <= n; ++u) {
                if (state[root[u]] == 0) delta = min(delta, label[u]);
            }
            for (int b = n + 1; b <= nodeCount; ++b) {
                if (root[b] == b && state[b] == 1) delta = min(delta, label[b] / 2);
            }
            for (int x = 1; x <= nodeCount; ++x) {
                if (root[x] != x || !slack[x]) continue;
                if (state[x] == -1) delta = min(delta, edgeDelta(graph[slack[x]][x]));
                else if (state[x] == 0) delta = min(delta, edgeDelta(graph[slack[x]][x]) / 2);
            }
            for (int u = 1; u <= n; ++u) {
                if (state[root[u]] == 0) {
                    if (label[u] == delta) return false;
                    label[u] -= delta;
                } else if (state[root[u]] == 1) label[u] += delta;
            }
            for (int b = n + 1; b <= nodeCount; ++b) {
                if (root[b] != b) continue;
                if (state[b] == 0) label[b] += 2 * delta;
                else if (state[b] == 1) label[b] -= 2 * delta;
            }
            bfsQueue = queue<int>();
            for (int x = 1; x <= nodeCount; ++x) {
                if (root[x] != x || !slack[x] || root[slack[x]] == x) continue;
                if (edgeDelta(graph[slack[x]][x]) == 0) {
                    if (processEdge(graph[slack[x]][x])) return true;
                }
            }
            for (int b = n + 1; b <= nodeCount; ++b) {
                if (root[b] == b && state[b] == 1 && label[b] == 0) expandFlower(b);
            }
        }
    }

public:
    explicit WeightedMatching(int vertexCount) : n(vertexCount), nodeCount(vertexCount) {
        for (int u = 1; u <= n; ++u) {
            root[u] = u;
            flowerFrom[u][u] = u;
            for (int v = 1; v <= n; ++v) graph[u][v] = {u, v, 0};
        }
    }

    void addEdge(int u, int v, long long weight) {
        graph[u][v] = {u, v, weight};
        graph[v][u] = {v, u, weight};
    }

    long long solve(long long baseWeight) {
        long long maxWeight = 0, totalCost = 0;
        for (int u = 1; u <= n; ++u) for (int v = 1; v <= n; ++v) maxWeight = max(maxWeight, graph[u][v].w);
        for (int u = 1; u <= n; ++u) label[u] = maxWeight;
        while (findAugmentingPath()) {}
        for (int u = 1; u <= n; ++u) {
            if (mate[u] > u) totalCost += baseWeight - graph[u][mate[u]].w;
        }
        return totalCost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        int n, m;
        cin >> n >> m;
        long long baseWeight = 1LL * (n / 2) * 1000000000 + 1;
        WeightedMatching solver(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            long long cost;
            cin >> u >> v >> cost;
            solver.addEdge(u, v, baseWeight - cost);
        }
        cout << "Case " << caseId << ": " << solver.solve(baseWeight) << '\n';
    }
    return 0;
}
