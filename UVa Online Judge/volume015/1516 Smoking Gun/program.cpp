#include <bits/stdc++.h>
using namespace std;

const long double Inf = 1e100L, Eps = 1e-10L;

struct Edge {
    int u, v;
    long double w;
};

long double getDist(int u, int v, const vector<pair<int, int>> &pos) {
    long double dx = (long double)pos[u].first - pos[v].first, dy = (long double)pos[u].second - pos[v].second;
    return sqrtl(dx * dx + dy * dy);
}

void solve() {
    int n, m;
    cin >> n >> m;
    map<string, int> id;
    vector<string> name(n);
    vector<pair<int, int>> pos(n);
    vector<bool> shooter(n, false);
    vector<Edge> edges;
    vector<vector<long double>> dis(n, vector<long double>(n, Inf));
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> name[i] >> x >> y;
        id[name[i]] = i;
        pos[i] = {x, y};
        dis[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        string s1, s2, s3, tmp;
        cin >> s1 >> tmp >> s2 >> tmp >> tmp >> s3;
        int w = id[s1], u = id[s2], v = id[s3];
        long double cost = getDist(w, v, pos) - getDist(w, u, pos);
        shooter[u] = shooter[v] = true;
        edges.push_back({v, u, cost});
        dis[v][u] = min(dis[v][u], cost);
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dis[i][k] >= Inf / 2) continue;
            for (int j = 0; j < n; j++) {
                if (dis[k][j] >= Inf / 2) continue;
                if (dis[i][j] > dis[i][k] + dis[k][j]) dis[i][j] = dis[i][k] + dis[k][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (dis[i][i] < -Eps) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    for (const Edge &e : edges) {
        if (dis[e.v][e.u] < Inf / 2 && dis[e.v][e.u] + e.w <= Eps) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    vector<int> list;
    for (int i = 0; i < n; i++)
        if (shooter[i]) list.push_back(i);
    for (int i = 0; i < (int)list.size(); i++) {
        for (int j = i + 1; j < (int)list.size(); j++) {
            int u = list[i], v = list[j];
            bool uBeforeV = dis[v][u] <= Eps;
            bool vBeforeU = dis[u][v] <= Eps;
            if (!uBeforeV && !vBeforeU) {
                cout << "UNKNOWN\n";
                return;
            }
        }
    }
    sort(list.begin(), list.end(), [&](int u, int v) {
        return dis[v][u] <= Eps;
    });
    for (int i = 0; i < (int)list.size(); i++) {
        if (i > 0) cout << ' ';
        cout << name[list[i]];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
