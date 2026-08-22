#include <bits/stdc++.h>
using namespace std;

const int maxV = 2005, maxE = 2005;
struct Edge {
    int to, id;
    Edge *next;
};
Edge edge[maxE * 2], *adj[maxV];
int edgeCnt;

void initEdge(int n) {
    edgeCnt = 0;
    for (int i = 0; i <= n; ++i) adj[i] = NULL;
}

void addEdge(int u, int v, int id) {
    Edge *p = &edge[edgeCnt++];
    p->to = v;
    p->id = id;
    p->next = adj[u];
    adj[u] = p;
}

struct Bridge {
    int dep[maxV], ban;
    bool vis[maxV], bridge[maxE];

    int dfs(int u, int p, int d) {
        vis[u] = true;
        dep[u] = d;
        int low = INT_MAX;
        for (Edge *e = adj[u]; e; e = e->next) {
            if (e->to == p || e->id == ban) continue;
            if (vis[e->to])
                low = min(low, dep[e->to]);
            else {
                int back = dfs(e->to, u, d + 1);
                if (back > d) bridge[e->id] = true;
                low = min(low, back);
            }
        }
        return low;
    }

    void findBridge(int n, int m, int banEdge) {
        ban = banEdge;
        memset(vis, 0, sizeof(vis));
        memset(bridge, 0, sizeof(bridge));
        for (int i = 1; i <= n; ++i)
            if (!vis[i]) dfs(i, -1, 0);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        int in[maxE][2];
        initEdge(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            in[i][0] = u;
            in[i][1] = v;
            addEdge(u, v, i);
            addEdge(v, u, i);
        }
        Bridge tool;
        tool.findBridge(n, m, -1);
        bool baseBridge[maxE], used[maxE];
        for (int i = 0; i < m; ++i) {
            baseBridge[i] = tool.bridge[i];
            used[i] = false;
        }
        int ansGcd = 0;
        for (int i = 0; i < m; ++i) {
            if (baseBridge[i] || used[i]) continue;
            used[i] = true;
            tool.findBridge(n, m, i);
            int len = 1;
            for (int j = 0; j < m; ++j)
                if (tool.bridge[j] && !baseBridge[j]) {
                    ++len;
                    used[j] = true;
                }
            ansGcd = __gcd(ansGcd, len);
            if (ansGcd == 1) break;
        }
        for (int i = 1; i <= ansGcd; ++i)
            if (ansGcd % i == 0)
                cout << i << (i == ansGcd ? '\n' : ' ');
    }
    return 0;
}
