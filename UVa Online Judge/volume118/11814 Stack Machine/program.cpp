#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);

struct Node {
    long long dis;
    int x, y;
    bool operator < (const Node &other) const {
        return dis > other.dis;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m, q;
        cin >> n >> m >> q;
        static bool has[101][101][441];
        memset(has, 0, sizeof(has));
        vector<int> in[101][221], out[101][221];
        for (int i = 0; i < m; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            int id = z + 220;
            if (has[x][y][id]) continue;
            has[x][y][id] = true;
            if (z > 0) in[y][z].push_back(x);
            else out[x][-z].push_back(y);
        }
        static long long dis[101][101], cyc[101];
        static bool done[101][101];
        priority_queue<Node> pq;
        for (int i = 1; i <= n; i++) {
            cyc[i] = inf;
            for (int j = 1; j <= n; j++) {
                dis[i][j] = inf;
                done[i][j] = false;
            }
            dis[i][i] = 0;
            pq.push({0, i, i});
        }
        while (!pq.empty()) {
            Node cur = pq.top();
            pq.pop();
            int u = cur.x, v = cur.y;
            if (done[u][v] || cur.dis != dis[u][v]) continue;
            done[u][v] = true;
            for (int k = 1; k <= n; k++) {
                if (dis[v][k] < inf && cur.dis + dis[v][k] < dis[u][k]) {
                    dis[u][k] = cur.dis + dis[v][k];
                    pq.push({dis[u][k], u, k});
                }
                if (dis[k][u] < inf && dis[k][u] + cur.dis < dis[k][v]) {
                    dis[k][v] = dis[k][u] + cur.dis;
                    pq.push({dis[k][v], k, v});
                }
            }
            for (int h = 40; h <= 220; h++) {
                if (in[u][h].empty() || out[v][h].empty()) continue;
                for (int x : in[u][h]) {
                    for (int y : out[v][h]) {
                        long long nd = cur.dis + 2;
                        if (x == y) cyc[x] = min(cyc[x], nd);
                        if (nd < dis[x][y]) {
                            dis[x][y] = nd;
                            pq.push({nd, x, y});
                        }
                    }
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= n; k++) {
                if (i != k && dis[i][k] < inf && dis[k][i] < inf)
                    cyc[i] = min(cyc[i], dis[i][k] + dis[k][i]);
            }
        }
        while (q--) {
            int x, y;
            cin >> x >> y;
            long long ans = x == y ? cyc[x] : dis[x][y];
            if (ans == inf) cout << "impossible\n";
            else cout << ans << '\n';
        }
    }
    return 0;
}
