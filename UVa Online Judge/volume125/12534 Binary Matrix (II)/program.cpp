#include <bits/stdc++.h>
using namespace std;

const int maxNode = 90, maxEdge = 4005, inf = 1000000000;

struct Edge {
    int to, cap, cost, next;
};

struct MinCostFlow {
    int nodeCnt, edgeCnt, src, snk, maxFlow, minCost;
    int head[maxNode], cur[maxNode], dis[maxNode];
    bool vis[maxNode];
    Edge edge[maxEdge];

    void init(int n) {
        nodeCnt = n;
        edgeCnt = 0;
        memset(head, -1, sizeof(head));
    }

    void addEdge(int u, int v, int cap, int cost) {
        edge[edgeCnt] = {v, cap, cost, head[u]};
        head[u] = edgeCnt++;
        edge[edgeCnt] = {u, 0, -cost, head[v]};
        head[v] = edgeCnt++;
    }

    void spfa() {
        queue<int> que;
        for (int i = 0; i <= nodeCnt; i++) {
            dis[i] = inf;
            vis[i] = false;
        }
        dis[snk] = 0;
        que.push(snk);
        vis[snk] = true;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            vis[u] = false;
            for (int i = head[u]; i != -1; i = edge[i].next) {
                int v = edge[i].to;
                if (edge[i ^ 1].cap == 0 || dis[v] <= dis[u] - edge[i].cost) continue;
                dis[v] = dis[u] - edge[i].cost;
                if (!vis[v]) {
                    vis[v] = true;
                    que.push(v);
                }
            }
        }
    }

    bool modify() {
        int delta = inf;
        for (int u = 0; u <= nodeCnt; u++) {
            if (!vis[u]) continue;
            for (int i = head[u]; i != -1; i = edge[i].next) {
                int v = edge[i].to;
                if (edge[i].cap > 0 && !vis[v]) delta = min(delta, dis[v] - dis[u] + edge[i].cost);
            }
        }
        if (delta == inf) return false;
        for (int i = 0; i <= nodeCnt; i++) {
            if (vis[i]) {
                vis[i] = false;
                dis[i] += delta;
                cur[i] = head[i];
            }
        }
        return true;
    }

    int augment(int u, int flow) {
        if (u == snk) {
            maxFlow += flow;
            minCost += dis[src] * flow;
            return flow;
        }
        vis[u] = true;
        for (int &i = cur[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if (edge[i].cap == 0 || vis[v] || dis[u] != dis[v] + edge[i].cost) continue;
            int delta = augment(v, min(flow, edge[i].cap));
            if (delta > 0) {
                edge[i].cap -= delta;
                edge[i ^ 1].cap += delta;
                return delta;
            }
        }
        return 0;
    }

    pair<int, int> solve(int s, int t) {
        src = s;
        snk = t;
        maxFlow = 0;
        minCost = 0;
        spfa();
        for (int i = 0; i <= nodeCnt; i++) cur[i] = head[i];
        do {
            while (augment(src, inf) > 0) memset(vis, false, sizeof(vis));
        } while (modify());
        return {maxFlow, minCost};
    }
};

int r, c;
char mat[45][45];
MinCostFlow mcf;

void buildGraph(int rowCap, int colCap) {
    int src = r + c + 1, snk = r + c + 2;
    mcf.init(snk);
    for (int i = 1; i <= r; i++) {
        mcf.addEdge(src, i, rowCap, 0);
        for (int j = 1; j <= c; j++) mcf.addEdge(i, r + j, 1, mat[i][j] == '1' ? -1 : 1);
    }
    for (int j = 1; j <= c; j++) mcf.addEdge(r + j, snk, colCap, 0);
}

int main() {
    int test;
    scanf("%d", &test);
    for (int tc = 1; tc <= test; tc++) {
        int oneCnt = 0, ans = inf;
        scanf("%d%d", &r, &c);
        for (int i = 1; i <= r; i++) scanf("%s", mat[i] + 1);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) oneCnt += mat[i][j] == '1';
        }
        for (int rowCap = 0; rowCap <= c; rowCap++) {
            if ((rowCap * r) % c != 0) continue;
            int colCap = rowCap * r / c;
            buildGraph(rowCap, colCap);
            pair<int, int> res = mcf.solve(r + c + 1, r + c + 2);
            if (res.first == rowCap * r) ans = min(ans, oneCnt + res.second);
        }
        printf("Case %d: %d\n", tc, ans);
    }
    return 0;
}
