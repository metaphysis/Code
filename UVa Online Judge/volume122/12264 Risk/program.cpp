// Risk
// UVa ID: 12264
// Verdict: Accepted
// Submission Date: 2026-02-23
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 10000;
const int MAXN = 205;

class Dinic {
private:
    struct Edge {
        int to, cap, flow, rev;
    };
    vector<Edge> adj[MAXN];
    int level[MAXN], cur[MAXN];
public:
    void clear() {
        for (int i = 0; i < MAXN; i++) adj[i].clear();
    }
    void addEdge(int u, int v, int cap) {
        adj[u].push_back({v, cap, 0, (int)adj[v].size()});
        adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
    }
    bool bfs(int s, int t) {
        memset(level, -1, sizeof(level));
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (level[e.to] < 0 && e.cap > e.flow) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }
    int dfs(int u, int t, int f) {
        if (u == t) return f;
        for (int &i = cur[u]; i < (int)adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (level[e.to] == level[u] + 1 && e.cap > e.flow) {
                int d = dfs(e.to, t, min(f, e.cap - e.flow));
                if (d > 0) {
                    e.flow += d;
                    adj[e.to][e.rev].flow -= d;
                    return d;
                }
            }
        }
        return 0;
    }
    int maxFlow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            memset(cur, 0, sizeof(cur));
            int f;
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> army(n + 1);
        int totalArmy = 0;
        for (int i = 1; i <= n; i++) {
            cin >> army[i];
            totalArmy += army[i];
        }
        vector<bool> isBorder(n + 1, false);
        vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
        for (int i = 1; i <= n; i++) {
            string line;
            cin >> line;
            for (int j = 1; j <= n; j++) {
                if (line[j - 1] == 'Y') {
                    adj[i][j] = true;
                    if (army[i] > 0 && army[j] == 0) isBorder[i] = true;
                }
            }
        }
        int borderCount = 0;
        for (int i = 1; i <= n; i++)
            if (isBorder[i]) borderCount++;
        int left = 1, right = totalArmy, ans = 0;
        while (left <= right) {
            int mid = (left + right) / 2;
            Dinic dinic;
            int s = 0, t = 2 * n + 1;
            for (int i = 1; i <= n; i++) {
                if (army[i] == 0) continue;
                dinic.addEdge(i + n, i, army[i]);
                if (isBorder[i]) {
                    dinic.addEdge(s, i + n, army[i]);
                    dinic.addEdge(i + n, t, mid);
                } else {
                    dinic.addEdge(s, i + n, army[i] - 1);
                }
            }
            for (int i = 1; i <= n; i++) {
                if (army[i] == 0) continue;
                for (int j = 1; j <= n; j++) {
                    if (i != j && adj[i][j] && army[j] > 0)
                        dinic.addEdge(i, j + n, INF);
                }
            }
            int flow = dinic.maxFlow(s, t);
            if (flow >= borderCount * mid) {
                ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
