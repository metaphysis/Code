// Concert Hall Scheduling
// UVa ID: 1317
// Verdict: Accepted
// Submission Date: 2026-01-22
// UVa Run Time: 0.610s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 2510;
const int MAXM = 600010;

struct Edge {
    int to, next, cap, cost;
} edges[MAXM * 2];

int head[MAXN], cnt;

void addEdge(int from, int to, int cap, int cost) {
    edges[cnt] = {to, head[from], cap, cost};
    head[from] = cnt++;
    edges[cnt] = {from, head[to], 0, -cost};
    head[to] = cnt++;
}

struct MinCostMaxFlow {
    int n, dist[MAXN], pre[MAXN], preEdge[MAXN];
    bool inQueue[MAXN];
    
    MinCostMaxFlow(int n) : n(n) {}
    
    bool spfa(int s, int t) {
        fill(dist, dist + n, INF);
        memset(inQueue, false, sizeof(inQueue));
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        inQueue[s] = true;
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inQueue[u] = false;
            for (int i = head[u]; ~i; i = edges[i].next) {
                int v = edges[i].to;
                if (edges[i].cap > 0 && dist[v] > dist[u] + edges[i].cost) {
                    dist[v] = dist[u] + edges[i].cost;
                    pre[v] = u;
                    preEdge[v] = i;
                    if (!inQueue[v]) {
                        q.push(v);
                        inQueue[v] = true;
                    }
                }
            }
        }
        return dist[t] < INF;
    }
    
    pair<int, int> minCostMaxFlow(int s, int t, int maxf) {
        int flow = 0, cost = 0;
        while (flow < maxf && spfa(s, t)) {
            int d = maxf - flow;
            for (int v = t; v != s; v = pre[v]) {
                d = min(d, edges[preEdge[v]].cap);
            }
            flow += d;
            cost += d * dist[t];
            for (int v = t; v != s; v = pre[v]) {
                int i = preEdge[v];
                edges[i].cap -= d;
                edges[i ^ 1].cap += d;
            }
        }
        return {flow, cost};
    }
};

struct Interval {
    int start, end, value;
    bool operator<(const Interval& other) const {
        return end < other.end;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n) {
        vector<Interval> itls(n);
        for (int i = 0; i < n; i++) {
            cin >> itls[i].start >> itls[i].end >> itls[i].value;
        }
        sort(itls.begin(), itls.end());
        // 节点编号：0:源点, 1:汇点, 2~2n+1:区间节点（拆点）
        int S = 0, T = 1;
        int offset = 2;
        int totalNodes = offset + 2 * n;
        memset(head, -1, sizeof(head));
        cnt = 0;
        MinCostMaxFlow mcmf(totalNodes);
        // 为每个区间添加拆点边
        for (int i = 0; i < n; i++) {
            int inNode = offset + 2 * i;
            int outNode = offset + 2 * i + 1;
            addEdge(inNode, outNode, 1, -itls[i].value);
            addEdge(S, inNode, 1, 0);
            addEdge(outNode, T, 1, 0);
        }
        // 添加区间之间的连接边
        for (int i = 0; i < n; i++) {
            int out = offset + 2 * i + 1;
            for (int j = i + 1; j < n; j++) {
                if (itls[i].end < itls[j].start) {
                    int in = offset + 2 * j;
                    addEdge(out, in, 1, 0);
                }
            }
        }
        auto result = mcmf.minCostMaxFlow(S, T, 2);
        int maxIncome = -result.second;
        cout << maxIncome << "\n";
    }
    return 0;
}
