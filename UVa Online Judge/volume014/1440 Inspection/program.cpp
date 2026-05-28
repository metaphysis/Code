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
const int INF = 0x3f3f3f3f;

struct Edge {
    int v, cap, nxt;
} edge[MAXN * MAXN];

int head[MAXN], tot;
int dis[MAXN], cur[MAXN], pre[MAXN], gap[MAXN];
int inDeg[MAXN], outDeg[MAXN];
int n, S, T, SS, ST;

void addEdge(int u, int v, int cap) {
    edge[tot] = {v, cap, head[u]};
    head[u] = tot++;
    edge[tot] = {u, 0, head[v]};
    head[v] = tot++;
}

void bfs(int t) {
    memset(dis, INF, sizeof(dis));
    memset(gap, 0, sizeof(gap));
    memcpy(cur, head, sizeof(cur));
    queue<int> q;
    q.push(t);
    dis[t] = 0;
    gap[0] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (dis[v] == INF) {
                dis[v] = dis[u] + 1;
                gap[dis[v]]++;
                q.push(v);
            }
        }
    }
}

int ISAP(int s, int t, int nodeCnt) {
    bfs(t);
    int u = pre[s] = s;
    int flow = 0;
    while (dis[s] < nodeCnt) {
        if (u == t) {
            int aug = INF;
            int idx = -1;
            for (int i = s; i != t; i = edge[cur[i]].v) {
                if (aug > edge[cur[i]].cap) {
                    aug = edge[cur[i]].cap;
                    idx = i;
                }
            }
            for (int i = s; i != t; i = edge[cur[i]].v) {
                edge[cur[i]].cap -= aug;
                edge[cur[i] ^ 1].cap += aug;
            }
            flow += aug;
            u = idx;
        }
        int i;
        for (i = cur[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (edge[i].cap && dis[v] + 1 == dis[u]) {
                cur[u] = i;
                pre[v] = u;
                u = v;
                break;
            }
        }
        if (i == -1) {
            if (--gap[dis[u]] == 0) break;
            int md = nodeCnt;
            for (int i = head[u]; ~i; i = edge[i].nxt) {
                if (edge[i].cap && dis[edge[i].v] < md) {
                    md = dis[edge[i].v];
                    cur[u] = i;
                }
            }
            dis[u] = md + 1;
            gap[dis[u]]++;
            u = pre[u];
        }
    }
    return flow;
}

void init() {
    memset(head, -1, sizeof(head));
    memset(inDeg, 0, sizeof(inDeg));
    memset(outDeg, 0, sizeof(outDeg));
    tot = 0;
}

void dfsPath(int u) {
    for (int i = head[u]; ~i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (i & 1) continue;
        if (!edge[i ^ 1].cap) continue;
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
        ISAP(SS, ST, ST + 1);
        
        // 添加 T->S 边
        addEdge(T, S, INF);
        
        // 第二次最大流，得到最小路径数
        int ans = ISAP(SS, ST, ST + 1);
        
        printf("%d\n", ans);
        
        // 构造路径
        // 恢复每条边的下界流量
        for (int u = 1; u <= n; u++) {
            for (int i = head[u]; ~i; i = edge[i].nxt) {
                if (i & 1) continue;
                int v = edge[i].v;
                if (v == S || v == T) continue;
                edge[i ^ 1].cap++;
            }
        }
        
        // 从 S 出发找所有路径
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
