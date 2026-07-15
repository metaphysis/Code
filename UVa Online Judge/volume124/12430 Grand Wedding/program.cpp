// Grand Wedding
// UVa ID: 12430
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 0.210s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

class DSU {
public:
    vector<int> parent, diff;
    DSU(int n) {
        parent.resize(n + 1);
        diff.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) {
            int p = parent[x];
            parent[x] = find(p);
            diff[x] ^= diff[p];
        }
        return parent[x];
    }
    bool unite(int u, int v) {
        int ru = find(u), rv = find(v);
        int du = diff[u], dv = diff[v];
        if (ru == rv) return (du ^ dv) == 1;
        parent[ru] = rv;
        diff[ru] = du ^ dv ^ 1;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<Edge> edges;
        int minSelf = INT_MAX;
        bool hasSelf = false;
        for (int i = 0; i < M; ++i) {
            int a, b, w;
            cin >> a >> b >> w;
            if (a == b) {
                hasSelf = true;
                minSelf = min(minSelf, w);
            } else {
                edges.push_back({a, b, w});
            }
        }
        int limit = hasSelf ? minSelf : INT_MAX;
        vector<Edge> valid;
        for (const auto& e : edges)
            if (e.w < limit) valid.push_back(e);
        if (valid.empty()) {
            if (hasSelf) cout << -1 << '\n';
            else cout << 0 << '\n';
            continue;
        }
        sort(valid.begin(), valid.end(), [](const Edge& x, const Edge& y) {
            return x.w < y.w;
        });
        DSU dsu(N);
        int cnt = 0;
        int ans = -1;
        int i = 0, m = valid.size();
        while (i < m) {
            int L = valid[i].w;
            if (cnt > 0) ans = L;
            int j = i;
            bool conflict = false;
            while (j < m && valid[j].w == L) {
                if (!dsu.unite(valid[j].u, valid[j].v)) {
                    conflict = true;
                    break;
                }
                ++j;
            }
            if (conflict) {
                cout << (ans == -1 ? -1 : ans) << '\n';
                break;
            }
            cnt += (j - i);
            i = j;
        }
        if (i == m) {
            if (hasSelf) cout << limit << '\n';
            else cout << 0 << '\n';
        }
    }
    return 0;
}
