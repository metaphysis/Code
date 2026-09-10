// Network Mess
// UVa ID: 1667
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n);
        sz.assign(n, 1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> data;
    int x;
    while (cin >> x) data.push_back(x);

    int pos = 0;

    while (pos < (int)data.size()) {
        int N = data[pos++];
        if (N == 0) break;

        vector<vector<double>> D;
        int readCnt = 0;

        // 兼容样例中最后一个对角线 0 可能被省略的格式
        for (int cand : {N * N, max(0, N * N - 1)}) {
            if (pos + cand > (int)data.size()) continue;

            D.assign(N, vector<double>(N, 0.0));
            for (int k = 0; k < cand; ++k) {
                int r = k / N;
                int c = k % N;
                D[r][c] = data[pos + k];
            }
            if (cand == N * N - 1) D[N - 1][N - 1] = 0.0;

            bool ok = true;
            for (int i = 0; i < N && ok; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (i == j) {
                        if (fabs(D[i][j]) > 1e-7) ok = false;
                    } else {
                        if (fabs(D[i][j] - D[j][i]) > 1e-7) ok = false;
                        if (D[i][j] < 1.5 || D[i][j] > 30.5) ok = false;
                    }
                }
            }
            if (ok) {
                readCnt = cand;
                break;
            }
        }

        if (readCnt == 0) {
            readCnt = N * N;
            D.assign(N, vector<double>(N, 0.0));
            for (int k = 0; k < readCnt && pos + k < (int)data.size(); ++k) {
                int r = k / N;
                int c = k % N;
                D[r][c] = data[pos + k];
            }
        }
        pos += readCnt;

        vector<vector<pair<int, double>>> adj;
        adj.resize(N);

        if (N == 2) {
            int d = (int)round(D[0][1]);
            for (int i = 0; i < d - 1; ++i) {
                if (i) cout << ' ';
                cout << 2;
            }
            cout << '\n';
            continue;
        }

        vector<int> nodes(N);
        iota(nodes.begin(), nodes.end(), 0);
        int m = N;

        while (m > 2) {
            vector<double> sum(m, 0.0);
            for (int idx = 0; idx < m; ++idx) {
                int i = nodes[idx];
                double s = 0.0;
                for (int jdx = 0; jdx < m; ++jdx)
                    s += D[i][nodes[jdx]];
                sum[idx] = s;
            }

            int bestI = nodes[0], bestJ = nodes[1];
            double bestQ = 1e100;

            for (int idx = 0; idx < m; ++idx) {
                for (int jdx = idx + 1; jdx < m; ++jdx) {
                    int i = nodes[idx];
                    int j = nodes[jdx];
                    double q = (double)(m - 2) * D[i][j] - sum[idx] - sum[jdx];
                    if (q < bestQ - 1e-9) {
                        bestQ = q;
                        bestI = i;
                        bestJ = j;
                    }
                }
            }

            int i = bestI, j = bestJ;
            double dij = D[i][j];

            int idxI = -1, idxJ = -1;
            for (int k = 0; k < m; ++k) {
                if (nodes[k] == i) idxI = k;
                if (nodes[k] == j) idxJ = k;
            }
            if (idxI > idxJ) swap(idxI, idxJ);

            double Si = sum[idxI];
            double Sj = sum[idxJ];

            double di = 0.5 * (dij + (Si - Sj) / (double)(m - 2));
            double dj = dij - di;

            if (di < 0 && di > -1e-7) di = 0.0;
            if (dj < 0 && dj > -1e-7) dj = 0.0;

            int u = (int)adj.size();
            adj.resize(u + 1);

            adj[u].push_back({i, di});
            adj[i].push_back({u, di});
            adj[u].push_back({j, dj});
            adj[j].push_back({u, dj});

            for (auto &row : D) row.resize(u + 1, 0.0);
            D.resize(u + 1, vector<double>(u + 1, 0.0));
            D[u][u] = 0.0;

            for (int k = 0; k < u; ++k) {
                if (k == i || k == j) continue;
                double val = (D[i][k] + D[j][k] - dij) * 0.5;
                if (val < 0 && val > -1e-7) val = 0.0;
                D[u][k] = D[k][u] = val;
            }

            nodes.erase(nodes.begin() + idxJ);
            nodes.erase(nodes.begin() + idxI);
            nodes.push_back(u);
            --m;
        }

        int a = nodes[0], b = nodes[1];
        double w = D[a][b];
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});

        int total = (int)adj.size();
        DSU dsu(total);

        vector<tuple<int, int, double>> edges;
        for (int u = 0; u < total; ++u) {
            for (auto &e : adj[u]) {
                if (e.first > u) edges.emplace_back(u, e.first, e.second);
            }
        }

        // 收缩长度为 0 的边
        for (auto &e : edges) {
            if (fabs(get<2>(e)) < 1e-7)
                dsu.unite(get<0>(e), get<1>(e));
        }

        vector<int> deg(total, 0);
        for (int v = 0; v < total; ++v)
            deg[dsu.find(v)] += (int)adj[v].size();

        for (auto &e : edges) {
            if (fabs(get<2>(e)) < 1e-7) {
                int r = dsu.find(get<0>(e));
                deg[r] -= 2;
            }
        }

        vector<char> hasInternal(total, 0);
        for (int v = N; v < total; ++v)
            hasInternal[dsu.find(v)] = 1;

        vector<int> ans;

        // 每条非零边中间插入度数为 2 的交换机
        for (auto &e : edges) {
            double len = get<2>(e);
            if (len > 1e-7) {
                int l = (int)round(len);
                if (l > 1)
                    for (int k = 0; k < l - 1; ++k)
                        ans.push_back(2);
            }
        }

        // 合并后的内部结点度数
        for (int r = 0; r < total; ++r) {
            if (dsu.find(r) == r && hasInternal[r] && deg[r] > 0)
                ans.push_back(deg[r]);
        }

        sort(ans.begin(), ans.end());

        for (size_t i = 0; i < ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
