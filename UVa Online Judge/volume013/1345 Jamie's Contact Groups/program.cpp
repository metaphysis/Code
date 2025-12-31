// Jamie's Contact Groups
// UVa ID: 1345
// Verdict: Accepted
// Submission Date: 2025-12-30
// UVa Run Time: 0.060s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1505; // N <= 1000, M <= 500, 总节点数 N+M+2
int N, M;

struct Edge {
    int to, cap, rev;
};

vector<Edge> graph[MAXN];
int level[MAXN];
int iter[MAXN];

void addEdge(int from, int to, int cap) {
    graph[from].push_back({to, cap, (int)graph[to].size()});
    graph[to].push_back({from, 0, (int)graph[from].size() - 1});
}

// BFS 构建分层图
void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto &e : graph[v])
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
    }
}

// DFS 寻找增广路
int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < (int)graph[v].size(); i++) {
        Edge &e = graph[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

// Dinic 算法求最大流
int maxFlow(int s, int t) {
    int flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, INF)) > 0) flow += f;
    }
}

// 检查当限制最大组大小为 limit 时是否可行
bool check(int limit, const vector<vector<int>> &can) {
    // 清空图
    for (int i = 0; i < MAXN; i++) graph[i].clear();
    int s = N + M, t = s + 1;
    // 源点 -> 每个联系人，容量 1
    for (int i = 0; i < N; i++) addEdge(s, i, 1);
    // 每个联系人 -> 允许的组，容量 1
    for (int i = 0; i < N; i++)
        for (int g : can[i]) addEdge(i, N + g, 1);
    // 每个组 -> 汇点，容量 limit
    for (int i = 0; i < M; i++) addEdge(N + i, t, limit);
    int flow = maxFlow(s, t);
    return flow == N; // 是否所有人都分配成功
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> N >> M && (N || M)) {
        cin.ignore(); // 忽略第一行末尾的换行符
        vector<vector<int>> can(N); // can[i] 存储第 i 个联系人可以去的组
        for (int i = 0; i < N; i++) {
            string line;
            getline(cin, line);
            stringstream ss(line);
            string name;
            ss >> name; // 名字，本题不需要使用
            int g;
            while (ss >> g) can[i].push_back(g);
        }

        // 二分答案
        int left = 0, right = N, ans = N;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid, can)) {
                ans = mid;
                right = mid - 1;
            } else left = mid + 1;
        }
        cout << ans << "\n";
    }
    return 0;
}
