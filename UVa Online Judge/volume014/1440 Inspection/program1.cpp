// Inspection
// UVa ID: 1440
// Verdict: Accepted
// Submission Date: 2026-05-28
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210;
const int INF = 1e8;

struct Edge {
    int v, cap, nxt;
} edge[MAXN * MAXN];

int head[MAXN], tot;
int inDeg[MAXN], outDeg[MAXN];
int level[MAXN], cur[MAXN];
int n, S, T, SS, ST;

void init() {
    memset(head, -1, sizeof(head));
    memset(inDeg, 0, sizeof(inDeg));
    memset(outDeg, 0, sizeof(outDeg));
    tot = 0;
}

void addEdge(int u, int v, int cap) {
    edge[tot] = {v, cap, head[u]};
    head[u] = tot++;
    edge[tot] = {u, 0, head[v]};
    head[v] = tot++;
}

bool bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (level[v] == -1 && edge[i].cap > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int u, int t, int f) {
    if (u == t || f == 0) return f;
    int flow = 0;
    for (int &i = cur[u]; ~i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (level[v] == level[u] + 1 && edge[i].cap > 0) {
            int pushed = dfs(v, t, min(f, edge[i].cap));
            if (pushed) {
                edge[i].cap -= pushed;
                edge[i ^ 1].cap += pushed;
                flow += pushed;
                f -= pushed;
                if (f == 0) break;
            }
        }
    }
    return flow;
}

int dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        flow += dfs(s, t, INF);
    }
    return flow;
}

void dfsPath(int u) {
    for (int i = head[u]; ~i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (i & 1) continue;
        if (edge[i ^ 1].cap == 0) continue;
        if (v == S || v == T || v > n) continue;
        edge[i ^ 1].cap--;
        printf(" %d", v);
        dfsPath(v);
        break;
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        init();
        S = n + 1, T = n + 2, SS = n + 3, ST = n + 4;
        
        // 读入原图
        for (int i = 1; i <= n; i++) {
            int m; scanf("%d", &m);
            for (int j = 0; j < m; j++) {
                int v; scanf("%d", &v);
                outDeg[i]++;
                inDeg[v]++;
                addEdge(i, v, INF);
            }
        }
        
        // 添加源汇辅助边
        for (int i = 1; i <= n; i++) {
            if (!outDeg[i]) addEdge(i, T, INF);
            if (!inDeg[i]) addEdge(S, i, INF);
            int diff = inDeg[i] - outDeg[i];
            if (diff > 0) addEdge(SS, i, diff);
            else if (diff < 0) addEdge(i, ST, -diff);
        }
        
        // 第一次最大流
        dinic(SS, ST);
        
        // 添加 T->S 边
        addEdge(T, S, INF);
        
        // 第二次最大流
        int ans = dinic(SS, ST);
        
        printf("%d\n", ans);
        
        // 恢复每条边的下界流量
        for (int u = 1; u <= n; u++) {
            for (int i = head[u]; ~i; i = edge[i].nxt) {
                if (i & 1) continue;
                int v = edge[i].v;
                if (v == S || v == T) continue;
                edge[i ^ 1].cap++;
            }
        }
        
        // 输出路径
        for (int i = head[S]; ~i; i = edge[i].nxt) {
            if (i & 1) continue;
            while (edge[i ^ 1].cap) {
                edge[i ^ 1].cap--;
                int v = edge[i].v;
                printf("%d", v);
                dfsPath(v);
                printf("\n");
            }
        }
    }
    return 0;
}
