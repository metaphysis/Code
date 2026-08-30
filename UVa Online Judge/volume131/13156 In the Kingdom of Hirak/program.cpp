#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;
const int MAXN = 50000;

long long fact[MAXN + 1], invfact[MAXN + 1];

long long modPow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; ++i) fact[i] = fact[i - 1] * i % MOD;
    invfact[MAXN] = modPow(fact[MAXN], MOD - 2);
    for (int i = MAXN; i >= 1; --i) invfact[i - 1] = invfact[i] * i % MOD;
}

struct Region {
    int n, m;
    vector<vector<int>> adj, radj;
};

vector<int> getSCCs(const Region& reg) {
    int n = reg.n;
    const auto& adj = reg.adj;
    const auto& radj = reg.radj;
    vector<int> vis(n + 1, 0), order;
    order.reserve(n);
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        vector<pair<int,int>> st;
        st.reserve(n);
        st.push_back({i, 0});
        vis[i] = 1;
        while (!st.empty()) {
            int u = st.back().first;
            int &idx = st.back().second;
            if (idx < (int)adj[u].size()) {
                int v = adj[u][idx++];
                if (!vis[v]) {
                    vis[v] = 1;
                    st.push_back({v, 0});
                }
            } else {
                order.push_back(u);
                st.pop_back();
            }
        }
    }
    vector<int> vis2(n + 1, 0), sizes;
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        if (vis2[u]) continue;
        vector<int> st;
        st.push_back(u);
        vis2[u] = 1;
        int sz = 0;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            ++sz;
            for (int w : radj[v]) {
                if (!vis2[w]) {
                    vis2[w] = 1;
                    st.push_back(w);
                }
            }
        }
        sizes.push_back(sz);
    }
    return sizes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    precompute();
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int R, K, a, b;
        cin >> R >> K >> a >> b;
        long long invB = modPow(b, MOD - 2);
        long long p = (long long)a * invB % MOD;
        long long q = (long long)(b - a) * invB % MOD;
        vector<Region> regions;
        regions.reserve(R);
        int maxN = 0;
        for (int i = 0; i < R; ++i) {
            Region reg;
            cin >> reg.n >> reg.m;
            maxN = max(maxN, reg.n);
            reg.adj.assign(reg.n + 1, {});
            reg.radj.assign(reg.n + 1, {});
            for (int j = 0; j < reg.m; ++j) {
                int u, v;
                cin >> u >> v;
                reg.adj[u].push_back(v);
                reg.radj[v].push_back(u);
            }
            regions.push_back(move(reg));
        }
        vector<long long> powP(maxN + 1), powQ(maxN + 1);
        powP[0] = powQ[0] = 1;
        for (int i = 1; i <= maxN; ++i) {
            powP[i] = powP[i - 1] * p % MOD;
            powQ[i] = powQ[i - 1] * q % MOD;
        }
        cout << "Case " << tc << ":\n";
        for (int y = 0; y < R; ++y) {
            const Region& reg = regions[y];
            vector<int> sizes = getSCCs(reg);
            long long ans = 0;
            for (int s : sizes) {
                if (s < K) {
                    ans = (ans + (long long)s * p) % MOD;
                } else {
                    int n1 = s - 1;
                    long long F = 0;
                    for (int x = 0; x < K; ++x) {
                        long long comb = fact[n1] * invfact[x] % MOD * invfact[n1 - x] % MOD;
                        long long term = comb * powP[x] % MOD * powQ[n1 - x] % MOD;
                        F += term;
                        if (F >= MOD) F -= MOD;
                    }
                    long long e = (long long)s * ((1 - q * F % MOD + MOD) % MOD) % MOD;
                    ans += e;
                    if (ans >= MOD) ans -= MOD;
                }
            }
            cout << "Region " << y + 1 << ": " << ans << "\n";
        }
    }
    return 0;
}
