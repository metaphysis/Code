#include <bits/stdc++.h>
using namespace std;

const double inf = 1e100;

double getDist(int a, int b, const vector<int> &x, const vector<int> &y, const vector<int> &z) {
    double dx = x[a] - x[b], dy = y[a] - y[b], dz = z[a] - z[b];
    return sqrt(dx * dx + dy * dy + dz * dz);
}

double solveCase(int n, const vector<int> &x, const vector<int> &y, const vector<int> &z, const vector<int> &k, const vector<vector<int>> &adj) {
    int low = max(z[0], z[n - 1]);
    double ans = inf;
    vector<int> hs;
    for (int i = 0; i < n; i++)
        if (z[i] >= low) hs.push_back(z[i]);
    sort(hs.begin(), hs.end());
    hs.erase(unique(hs.begin(), hs.end()), hs.end());
    for (int h : hs) {
        vector<int> id(n, -1), holes;
        vector<vector<int>> nodes;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (z[i] > h || id[i] != -1) continue;
            queue<int> q;
            vector<int> cur;
            int sum = 0;
            q.push(i);
            id[i] = cnt;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                cur.push_back(u);
                sum += k[u];
                for (int v : adj[u])
                    if (z[v] <= h && id[v] == -1) {
                        id[v] = cnt;
                        q.push(v);
                    }
            }
            nodes.push_back(cur);
            holes.push_back(sum);
            cnt++;
        }
        int cs = id[0], ct = id[n - 1];
        if (cs == -1 || ct == -1) continue;
        if (cs == ct) {
            ans = min(ans, holes[cs] * 0.5);
            continue;
        }
        if (holes[cs] == 0 || holes[ct] == 0) continue;
        vector<vector<double>> cost(cnt, vector<double>(cnt, inf));
        for (int i = 0; i < n; i++) {
            if (z[i] > h || k[i] == 0) continue;
            for (int j = i + 1; j < n; j++) {
                if (z[j] > h || k[j] == 0 || id[i] == id[j]) continue;
                double d = getDist(i, j, x, y, z) - 1.0;
                int a = id[i], b = id[j];
                cost[a][b] = min(cost[a][b], d);
                cost[b][a] = min(cost[b][a], d);
            }
        }
        vector<double> dis(cnt, inf);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        dis[cs] = holes[cs] * 0.5;
        pq.push(make_pair(dis[cs], cs));
        while (!pq.empty()) {
            double du = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (du != dis[u]) continue;
            if (u != cs && holes[u] < 2) continue;
            for (int v = 0; v < cnt; v++) {
                if (v == cs || holes[v] == 0 || cost[u][v] >= inf) continue;
                double nd = du + cost[u][v] + holes[v] * 0.5;
                if (nd < dis[v]) {
                    dis[v] = nd;
                    pq.push(make_pair(nd, v));
                }
            }
        }
        ans = min(ans, dis[ct]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, tc = 0;
    while (cin >> n >> m) {
        vector<int> x(n), y(n), z(n), k(n);
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> z[i] >> k[i];
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        double ans = solveCase(n, x, y, z, k, adj);
        cout << "Case " << ++tc << ": ";
        if (ans >= inf / 2) cout << "impossible\n";
        else cout << fixed << setprecision(4) << ans + 1e-9 << '\n';
    }
    return 0;
}
