// Paint the Roads
// UVa ID: 12092
// Verdict: Accepted
// Submission Date: 2026-02-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f;

struct MCMF {
    struct Edge {
        int to, cap, cost, rev;
    };
    int n;
    vector<vector<Edge>> g;
    vector<int> dist, preNode, preEdge;
    vector<bool> inq;
    
    MCMF(int n) : n(n) {
        g.resize(n);
        dist.resize(n);
        preNode.resize(n);
        preEdge.resize(n);
        inq.resize(n);
    }
    
    void addEdge(int from, int to, int cap, int cost) {
        g[from].push_back({to, cap, cost, (int)g[to].size()});
        g[to].push_back({from, 0, -cost, (int)g[from].size() - 1});
    }
    
    bool spfa(int s, int t, int &flow, int &cost) {
        fill(dist.begin(), dist.end(), INF);
        fill(inq.begin(), inq.end(), false);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        inq[s] = true;
        preNode[s] = -1;
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = false;
            for (int i = 0; i < (int)g[u].size(); i++) {
                Edge &e = g[u][i];
                if (e.cap > 0 && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    preNode[e.to] = u;
                    preEdge[e.to] = i;
                    if (!inq[e.to]) {
                        q.push(e.to);
                        inq[e.to] = true;
                    }
                }
            }
        }
        if (dist[t] == INF) return false;
        
        int f = INF;
        for (int v = t; v != s; v = preNode[v]) {
            int u = preNode[v];
            f = min(f, g[u][preEdge[v]].cap);
        }
        flow += f;
        cost += f * dist[t];
        for (int v = t; v != s; v = preNode[v]) {
            int u = preNode[v];
            Edge &e = g[u][preEdge[v]];
            e.cap -= f;
            g[e.to][e.rev].cap += f;
        }
        return true;
    }
    
    PII minCostMaxFlow(int s, int t) {
        int flow = 0, cost = 0;
        while (spfa(s, t, flow, cost));
        return {flow, cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int TT;
    cin >> TT;
    while (TT--) {
        int n, m, k;
        cin >> n >> m >> k;
        
        // 节点编号：
        // 0 ~ n-1: 左点 (出点)
        // n ~ 2n-1: 右点 (入点)
        // 2n: 源点 S
        // 2n+1: 汇点 T
        int S = 2 * n, T = 2 * n + 1;
        MCMF mcmf(2 * n + 2);
        
        // 源点到左点，容量 k，费用 0
        for (int i = 0; i < n; i++)
            mcmf.addEdge(S, i, k, 0);
        
        // 右点到汇点，容量 k，费用 0
        for (int i = 0; i < n; i++)
            mcmf.addEdge(i + n, T, k, 0);
        
        // 读入道路
        for (int i = 0; i < m; i++) {
            int f, t, d;
            cin >> f >> t >> d;
            // 左点 f 到右点 t+n，容量 1，费用 d
            mcmf.addEdge(f, t + n, 1, d);
        }
        
        PII r = mcmf.minCostMaxFlow(S, T);
        if (r.first == k * n) cout << r.second << '\n';
        else cout << -1 << '\n';
    }
    return 0;
}
