// Chips Challenge
// UVa ID: 1104
// Verdict: Accepted
// Submission Date: 2025-11-21
// UVa Run Time: 0.430s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 45;
const int MAXV = 200;

struct Edge {
    int to, cap, cost, rev;
    Edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {}
};

vector<Edge> graph[MAXV];
int dist[MAXV], prevv[MAXV], preve[MAXV];
bool inQueue[MAXV];

void addEdge(int from, int to, int cap, int cost) {
    graph[from].emplace_back(to, cap, cost, graph[to].size());
    graph[to].emplace_back(from, 0, -cost, graph[from].size() - 1);
}

bool spfa(int s, int t) {
    memset(dist, 0x3f, sizeof(dist));
    memset(inQueue, 0, sizeof(inQueue));
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    inQueue[s] = true;
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inQueue[u] = false;
        for (int i = 0; i < graph[u].size(); i++) {
            Edge& e = graph[u][i];
            if (e.cap > 0 && dist[e.to] > dist[u] + e.cost) {
                dist[e.to] = dist[u] + e.cost;
                prevv[e.to] = u;
                preve[e.to] = i;
                if (!inQueue[e.to]) {
                    inQueue[e.to] = true;
                    q.push(e.to);
                }
            }
        }
    }
    return dist[t] < INF;
}

int minCostMaxFlow(int s, int t, int& cost) {
    int flow = 0;
    cost = 0;
    while (spfa(s, t)) {
        int f = INF;
        for (int v = t; v != s; v = prevv[v]) {
            f = min(f, graph[prevv[v]][preve[v]].cap);
        }
        flow += f;
        for (int v = t; v != s; v = prevv[v]) {
            Edge& e = graph[prevv[v]][preve[v]];
            e.cap -= f;
            graph[e.to][e.rev].cap += f;
            cost += f * e.cost;
        }
    }
    return flow;
}

int n, A, B;
char grid[MAXN][MAXN];

int main() {
    int caseNum = 1;
    while (cin >> n >> A >> B, n || A || B) {
        int totalPositions = 0;  // 总可用位置数（C和.）
        int originalC = 0;       // 原有C的数量
        int rowTotal[MAXN] = {0}; // 每行的总可用位置数
        int colTotal[MAXN] = {0}; // 每列的总可用位置数
        for (int i = 0; i < n; i++) {
            cin >> grid[i];
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'C' || grid[i][j] == '.') {
                    totalPositions++;
                    rowTotal[i]++;
                    colTotal[j]++;
                    originalC += (grid[i][j] == 'C');
                }
            }
        }
        int answer = -1;
        // 枚举每行/列的最大组件数 maxt
        for (int maxt = 0; maxt <= n; maxt++) {
            int s = 2 * n, t = 2 * n + 1;
            for (int i = 0; i <= t; i++) graph[i].clear();
            for (int i = 0; i < n; i++) {
                // 源点→行节点：容量 = 该行的总可用位置数
                addEdge(s, i, rowTotal[i], 0);
                // 行节点→对应列节点：容量 = maxt（行列相等约束 + 上界约束）
                addEdge(i, i + n, maxt, 0);
                // 列节点→汇点：容量 = 该列的总可用位置数
                addEdge(i + n, t, colTotal[i], 0);
                // 添加空位置的边：费用1表示不选择这个位置
                for (int j = 0; j < n; j++) {
                    if (grid[i][j] == '.') {
                        addEdge(i, j + n, 1, 1);
                    }
                }
            }
            int cost;
            int flow = minCostMaxFlow(s, t, cost);
            // 关键检查条件
            if (flow == totalPositions) {
                int totalComponents = flow - cost;  // 总组件数（原有+新增）
                if (totalComponents * A >= maxt * B) {
                    int newWidgets = totalComponents - originalC;  // 新增部件数
                    answer = max(answer, newWidgets);
                }
            }
        }
        cout << "Case " << caseNum++ << ": ";
        if (answer == -1) cout << "impossible" << endl;
        else cout << answer << endl;
    }
    return 0;
}
