// Frequency Hopping
// UVa ID: 11248
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.790s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <set>
#include <cstring>
#include <map>

using namespace std;

typedef long long ll;

struct Edge {
    int to, rev;
    ll cap, flow;
    int originalFrom, originalTo;
};

class Dinic {
private:
    int n;
    vector<vector<Edge>> graph;
    vector<int> level, ptr;

    bool bfs(int s, int t) {
        level.assign(n, -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty() && level[t] == -1) {
            int u = q.front();
            q.pop();
            for (Edge &e : graph[u]) {
                if (level[e.to] == -1 && e.flow < e.cap) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int u, int t, ll pushed) {
        if (u == t || pushed == 0) return pushed;
        for (int &cid = ptr[u]; cid < graph[u].size(); ++cid) {
            Edge &e = graph[u][cid];
            if (level[e.to] == level[u] + 1 && e.flow < e.cap) {
                ll tr = dfs(e.to, t, min(pushed, e.cap - e.flow));
                if (tr > 0) {
                    e.flow += tr;
                    graph[e.to][e.rev].flow -= tr;
                    return tr;
                }
            }
        }
        return 0;
    }

public:
    Dinic(int n) : n(n), graph(n), level(n), ptr(n) {}

    void addEdge(int from, int to, ll cap, int originalFrom, int originalTo) {
        graph[from].push_back({to, (int)graph[to].size(), cap, 0, originalFrom, originalTo});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0, 0, originalFrom, originalTo});
    }

    ll maxFlow(int s, int t) {
        ll totalFlow = 0;
        while (bfs(s, t)) {
            ptr.assign(n, 0);
            while (ll pushed = dfs(s, t, LLONG_MAX)) {
                totalFlow += pushed;
            }
        }
        return totalFlow;
    }

    void resetFlow() {
        for (int i = 0; i < n; i++) {
            for (Edge &e : graph[i]) {
                e.flow = 0;
            }
        }
    }

    vector<pair<int, int>> getMinCutEdges(int s) {
        vector<pair<int, int>> minCutEdges;
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (Edge &e : graph[u]) {
                if (!visited[e.to] && e.flow < e.cap) {
                    visited[e.to] = true;
                    q.push(e.to);
                }
            }
        }

        for (int u = 1; u < n; u++) {
            if (visited[u]) {
                for (Edge &e : graph[u]) {
                    if (e.cap > 0 && !visited[e.to] && e.originalFrom != -1) {
                        minCutEdges.push_back(make_pair(e.originalFrom, e.originalTo));
                    }
                }
            }
        }

        return minCutEdges;
    }

    void updateCapacity(int from, int to, ll newCap) {
        for (Edge &e : graph[from]) {
            if (e.to == to && e.cap > 0) {
                e.cap = newCap;
                return;
            }
        }
    }

    ll getCapacity(int from, int to) {
        for (Edge &e : graph[from]) {
            if (e.to == to && e.cap > 0) {
                return e.cap;
            }
        }
        return 0;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseNum = 1;
    int n, e;
    ll c;
    
    while (cin >> n >> e >> c, n != 0 || e != 0 || c != 0) {
        Dinic dinic(n + 1);
        
        map<pair<int, int>, ll> originalEdges;
        
        for (int i = 0; i < e; i++) {
            int b1, b2, fp;
            cin >> b1 >> b2 >> fp;
            dinic.addEdge(b1, b2, fp, b1, b2);
            originalEdges[make_pair(b1, b2)] = fp;
        }

        cout << "Case " << caseNum++ << ": ";
        
        ll maxFlow = dinic.maxFlow(1, n);
        
        if (maxFlow >= c) {
            cout << "possible\n";
            continue;
        }

        vector<pair<int, int>> minCutEdges = dinic.getMinCutEdges(1);
        set<pair<int, int>> options;

        for (auto &edge : minCutEdges) {
            int u = edge.first;
            int v = edge.second;
            ll originalCap = originalEdges[make_pair(u, v)];
            
            dinic.resetFlow();
            dinic.updateCapacity(u, v, originalCap + (c - maxFlow));
            ll newFlow = dinic.maxFlow(1, n);
            dinic.updateCapacity(u, v, originalCap);
            
            if (newFlow >= c) {
                options.insert(make_pair(u, v));
            }
        }

        if (!options.empty()) {
            cout << "possible option:";
            bool first = true;
            
            vector<pair<int, int>> sortedOptions(options.begin(), options.end());
            sort(sortedOptions.begin(), sortedOptions.end());
            
            for (auto &p : sortedOptions) {
                if (!first) cout << ",";
                cout << "(" << p.first << "," << p.second << ")";
                first = false;
            }
            cout << "\n";
        } else {
            cout << "not possible\n";
        }
    }

    return 0;
}
