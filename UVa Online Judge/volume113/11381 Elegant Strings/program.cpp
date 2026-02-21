// Elegant Strings
// UVa ID: 11381
// Verdict: Accepted
// Submission Date: 2026-02-10
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 205; // 拆点后最多 200 个点

struct Edge {
    int to, cap, cost, rev;
};

vector<Edge> graph[MAXN];
int dist[MAXN], prevv[MAXN], preve[MAXN];
bool inQueue[MAXN];

void addEdge(int from, int to, int cap, int cost) {
    graph[from].push_back({to, cap, cost, (int)graph[to].size()});
    graph[to].push_back({from, 0, -cost, (int)graph[from].size() - 1});
}

// 最小费用最大流
pair<int, int> minCostMaxFlow(int s, int t, int n) {
    int flow = 0, cost = 0;
    while (true) {
        fill(dist, dist + n, INF);
        fill(inQueue, inQueue + n, false);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        inQueue[s] = true;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            inQueue[v] = false;
            for (int i = 0; i < (int)graph[v].size(); ++i) {
                Edge &e = graph[v][i];
                if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                    dist[e.to] = dist[v] + e.cost;
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    if (!inQueue[e.to]) {
                        q.push(e.to);
                        inQueue[e.to] = true;
                    }
                }
            }
        }
        if (dist[t] == INF) break;
        int d = INF;
        for (int v = t; v != s; v = prevv[v]) {
            d = min(d, graph[prevv[v]][preve[v]].cap);
        }
        flow += d;
        cost += d * dist[t];
        for (int v = t; v != s; v = prevv[v]) {
            Edge &e = graph[prevv[v]][preve[v]];
            e.cap -= d;
            graph[v][e.rev].cap += d;
        }
    }
    return {flow, cost};
}

int main() {
    int testCases;
    cin >> testCases;
    while (testCases--) {
        string S, T;
        cin >> S >> T;
        int n = T.size();
        
        // 清理图
        for (int i = 0; i < MAXN; ++i) graph[i].clear();
        
        // 预处理优雅值
        int elegance[26][26] = {0};
        bool validPair[26][26] = {false};
        map<pair<char, char>, bool> appeared;
        for (int i = 0; i + 1 < (int)S.size(); ++i) {
            char a = S[i], b = S[i + 1];
            if (!appeared[{a, b}]) {
                appeared[{a, b}] = true;
                validPair[a - 'a'][b - 'a'] = true;
                elegance[a - 'a'][b - 'a'] = (i + 1) * (i + 1);
            }
        }
        
        // 拆点：i 对应出点，i+n 对应入点
        int src = 2 * n, sink = 2 * n + 1;
        int totalNodes = 2 * n + 2;
        
        // 源点到出点，入点到汇点
        for (int i = 0; i < n; ++i) {
            addEdge(src, i, 1, 0);
            addEdge(i + n, sink, 1, 0);
        }
        
        // 添加合法边
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (validPair[T[i] - 'a'][T[j] - 'a']) {
                    addEdge(i, j + n, 1, elegance[T[i] - 'a'][T[j] - 'a']);
                }
            }
        }
        
        // 运行最小费用最大流
        auto [maxFlow, minCost] = minCostMaxFlow(src, sink, totalNodes);
        int minPaths = n - maxFlow;
        
        cout << minPaths << " " << minCost << endl;
    }
    return 0;
}
