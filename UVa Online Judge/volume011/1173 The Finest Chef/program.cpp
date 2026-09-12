#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap, cost;
};

int n, m, s, t;
vector<vector<Edge>> graph;

void addEdge(int from, int to, int cap, int cost) {
    Edge a = {to, (int)graph[to].size(), cap, cost};
    Edge b = {from, (int)graph[from].size(), 0, -cost};
    graph[from].push_back(a);
    graph[to].push_back(b);
}

pair<int, int> minCostFlow() {
    int flow = 0, cost = 0;
    const int inf = 1e9;
    while (flow < n) {
        vector<int> dis(graph.size(), inf), preV(graph.size(), -1), preE(graph.size(), -1);
        vector<bool> inQ(graph.size(), false);
        queue<int> que;
        dis[s] = 0;
        que.push(s);
        inQ[s] = true;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            inQ[u] = false;
            for (int i = 0; i < (int)graph[u].size(); i++)
                if (graph[u][i].cap > 0 && dis[graph[u][i].to] > dis[u] + graph[u][i].cost) {
                    dis[graph[u][i].to] = dis[u] + graph[u][i].cost;
                    preV[graph[u][i].to] = u;
                    preE[graph[u][i].to] = i;
                    if (!inQ[graph[u][i].to]) {
                        que.push(graph[u][i].to);
                        inQ[graph[u][i].to] = true;
                    }
                }
        }
        if (dis[t] == inf) break;
        int add = n - flow;
        for (int v = t; v != s; v = preV[v])
            add = min(add, graph[preV[v]][preE[v]].cap);
        for (int v = t; v != s; v = preV[v]) {
            Edge &e = graph[preV[v]][preE[v]];
            e.cap -= add;
            graph[v][e.rev].cap += add;
        }
        flow += add;
        cost += add * dis[t];
    }
    return {flow, cost};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases;
    cin >> cases;
    for (int cs = 0; cs < cases; cs++) {
        cin >> n >> m;
        int k;
        cin >> k;
        s = n + m;
        t = s + 1;
        graph.assign(t + 1, vector<Edge>());
        for (int i = 0; i < n; i++)
            addEdge(s, i, 1, 0);
        for (int i = 0; i < m; i++)
            addEdge(n + i, t, 1, 0);
        for (int i = 0; i < k; i++) {
            int chef, facility, time;
            cin >> chef >> facility >> time;
            addEdge(chef, n + facility, 1, time);
        }
        cout << minCostFlow().second << '\n';
        if (cs + 1 < cases)
            cout << '\n';
    }
    return 0;
}
