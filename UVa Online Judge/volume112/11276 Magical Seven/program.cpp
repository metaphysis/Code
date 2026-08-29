#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int MOD = 10000;

namespace PerfectMatch {
    const int T = 70;
    int a[T][T], b[T][T], c[T][T], d[T], e[T], p[128], t;
    void dfs(int k) {
        if (k & 64) {
            int v = (k ^ 64) << 1;
            if (p[v] < 0) p[v] = t++, dfs(v);
            a[p[k]][p[v]] = b[p[k]][p[v]] = 1;
            if (~k & 1) {
                if (p[v |= 3] < 0) p[v] = t++, dfs(v);
                b[p[k]][p[v]] = 1;
            }
        } else {
            int v = k << 1 | 1;
            if (p[v] < 0) p[v] = t++, dfs(v);
            a[p[k]][p[v]] = b[p[k]][p[v]] = 1;
        }
    }
    void mul(const int (&A)[T][T], const int (&B)[T][T], int (&C)[T][T]) {
        memset(C, 0, sizeof(C));
        for (int i = 0; i < t; ++i) for (int k = 0; k < t; ++k) if (A[i][k]) for (int j = 0; j < t; ++j) if (B[k][j])
            C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    }
    void powMat(ULL n) {
        memcpy(c, a, sizeof(a));
        while (n) {
            if (n & 1) {
                memcpy(e, d, sizeof(d));
                for (int i = 0; i < t; ++i) {
                    d[i] = 0;
                    for (int k = 0; k < t; ++k) if (e[k]) d[i] = (d[i] + e[k] * c[k][i]) % MOD;
                }
            }
            if (n == 1) return;
            memcpy(b, c, sizeof(c)); mul(b, b, c); n >>= 1;
        }
    }
    int solve(ULL n) {
        if (n == 1) return a[0][0];
        for (int i = 0; i < t; ++i) d[i] = !i;
        powMat(n);
        return d[0];
    }
    void init() {
        memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b)); memset(p, -1, sizeof(p));
        p[127] = 0; t = 1; dfs(127);
        for (int i = 1; i < 7; ++i) { memcpy(c, a, sizeof(a)); mul(c, b, a); }
    }
}

namespace Hamilton {
    const int T = 319, E = 261;
    int m[7][T][T], a[T][T], x[4][E][E], d[E], e[E], p[65536], t, s;
    bool vis[7][T];
    int r_t_l(int k, int i) {
        for (int c = 1; i < 16; i += 2) {
            int v = (k >> i) & 3;
            if (v == 1) ++c;
            else if (v == 2 && --c == 0) return k ^ (3 << i);
        }
        return k;
    }
    int l_t_r(int k, int i) {
        for (int c = 1; i >= 0; i -= 2) {
            int v = (k >> i) & 3;
            if (v == 2) ++c;
            else if (v == 1 && --c == 0) return k ^ (3 << i);
        }
        return k;
    }
    int roll(int v, int dir) { return dir ? v : v << 2; }
#define ADD_TRANS(k, i, j, v) \
    if (p[v] < 0) p[v] = t++; \
    if (!vis[j][p[v]]) vis[j][p[v]] = true, dfs(v, j); \
    m[i][p[k]][p[v]] = 1
    void dfs(int k, int i) {
        int l = (k >> (i << 1)) & 3, u = (k >> ((i + 1) << 1)) & 3, j = (i < 6) ? i + 1 : 0;
        if (!l && !u) {
            if (!j) return;
            int v = k | (9 << (i << 1)); ADD_TRANS(k, i, j, v);
        } else if (!l || !u) {
            int w = k ^ (l << (i << 1)) ^ (u << ((i + 1) << 1));
            int v = roll(w | ((l + u) << (i << 1)), j); ADD_TRANS(k, i, j, v);
            if (!j) return;
            v = roll(w | ((l + u) << ((i + 1) << 1)), j); ADD_TRANS(k, i, j, v);
        } else if (l == 2 && u == 1) {
            int v = roll(k ^ (6 << (i << 1)), j); ADD_TRANS(k, i, j, v);
        } else if (l == 1 && u == 1) {
            int v = roll(r_t_l(k ^ (5 << (i << 1)), (i << 1) + 4), j); ADD_TRANS(k, i, j, v);
        } else if (l == 2 && u == 2) {
            int v = roll(l_t_r(k ^ (10 << (i << 1)), (i << 1) - 2), j); ADD_TRANS(k, i, j, v);
        }
    }
#undef ADD_TRANS
    void mul(const int (&A)[T][T], const int (&B)[T][T], int (&C)[T][T]) {
        memset(C, 0, sizeof(C));
        for (int i = 0; i < t; ++i) for (int k = 0; k < t; ++k) if (A[i][k]) for (int j = 0; j < t; ++j) if (B[k][j])
            C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    }
    void mul(const int (&A)[E][E], const int (&B)[E][E], int (&C)[E][E]) {
        memset(C, 0, sizeof(C));
        for (int i = 0; i < E; ++i) for (int k = 0; k < E; ++k) if (A[i][k]) for (int j = 0; j < E; ++j) if (B[k][j])
            C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    }
    void mul(const int (&A)[E], const int (&B)[E][E], int (&C)[E]) {
        memset(C, 0, sizeof(C));
        for (int i = 0; i < E; ++i) for (int k = 0; k < E; ++k) if (A[k]) C[i] = (C[i] + A[k] * B[k][i]) % MOD;
    }
    void powMat(ULL n) {
        memcpy(x[2], x[1], sizeof(x[1]));
        while (n) {
            if (n & 1) { memcpy(e, d, sizeof(d)); mul(e, x[2], d); }
            if (n == 1) return;
            memcpy(x[3], x[2], sizeof(x[2])); mul(x[3], x[3], x[2]); n >>= 1;
        }
    }
    int solve(ULL n) {
        for (int i = 0; i < E; ++i) d[i] = !i;
        if (n > 1) powMat(n - 1);
        memcpy(e, d, sizeof(d)); mul(e, x[0], d);
        return d[s];
    }
    void init() {
        memset(m, 0, sizeof(m)); memset(vis, 0, sizeof(vis)); memset(p, -1, sizeof(p));
        p[0] = 0; t = 1; vis[0][0] = true; dfs(0, 0); s = p[36864];
        for (int i = 1; i < 6; ++i) { memcpy(a, m[0], sizeof(a)); mul(a, m[i], m[0]); }
        memcpy(a, m[0], sizeof(a)); mul(a, m[6], m[1]);
        memset(p, -1, sizeof(p));
        for (int i = 0, k = 0; i < t; ++i) for (int j = 0; j < t; ++j) if (m[0][i][j] || m[0][j][i] || m[1][i][j] || m[1][j][i]) { p[i] = k++; break; }
        for (int i = 0; i < t; ++i) if (p[i] >= 0) for (int j = 0; j < t; ++j) if (p[j] >= 0) {
            x[0][p[i]][p[j]] = m[0][i][j];
            x[1][p[i]][p[j]] = m[1][i][j];
        }
        s = p[s];
    }
}

namespace CycleSubgraph {
    const int T = 112, E = 82;
    int a[T][T], b[T][T], c[T][T], d[T][T], x[E][E], y[E][E], z[E][E], e[E], f[E], p[256], t;
    void dfs(int k) {
        int l = k & 1, u = (k & 128) >> 7;
        if (l ^ u) {
            int w = (k ^ l ^ (u << 7)) << 1;
            int v = w | 2;
            if (p[v] < 0) p[v] = t++, dfs(v);
            b[p[k]][p[v]] = c[p[k]][p[v]] = 1;
            if (!l) a[p[k]][p[v]] = 1;
            v = w | 1;
            if (p[v] < 0) p[v] = t++, dfs(v);
            b[p[k]][p[v]] = 1;
            if (!l) a[p[k]][p[v]] = 1;
        } else if (l) {
            int v = (k ^ l ^ (u << 7)) << 1;
            if (p[v] < 0) p[v] = t++, dfs(v);
            a[p[k]][p[v]] = b[p[k]][p[v]] = c[p[k]][p[v]] = 1;
        } else {
            int v = k << 1 | 3;
            if (p[v] < 0) p[v] = t++, dfs(v);
            a[p[k]][p[v]] = b[p[k]][p[v]] = 1;
        }
    }
    void mul(const int (&A)[T][T], const int (&B)[T][T], int (&C)[T][T]) {
        memset(C, 0, sizeof(C));
        for (int i = 0; i < t; ++i) for (int k = 0; k < t; ++k) if (A[i][k]) for (int j = 0; j < t; ++j) if (B[k][j])
            C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    }
    void mul(const int (&A)[E][E], const int (&B)[E][E], int (&C)[E][E]) {
        memset(C, 0, sizeof(C));
        for (int i = 0; i < E; ++i) for (int k = 0; k < E; ++k) if (A[i][k]) for (int j = 0; j < E; ++j) if (B[k][j])
            C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    }
    void powMat(ULL n) {
        memcpy(y, x, sizeof(x));
        while (n) {
            if (n & 1) {
                memcpy(f, e, sizeof(e));
                for (int i = 0; i < E; ++i) {
                    e[i] = 0;
                    for (int k = 0; k < E; ++k) if (f[k]) e[i] = (e[i] + f[k] * y[k][i]) % MOD;
                }
            }
            if (n == 1) return;
            memcpy(z, y, sizeof(y)); mul(z, z, y); n >>= 1;
        }
    }
    int solve(ULL n) {
        if (n == 1) return a[0][0];
        for (int i = 0; i < t; ++i) e[i] = !i;
        powMat(n);
        return e[0];
    }
    void init() {
        memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b)); memset(p, -1, sizeof(p));
        p[0] = 0; t = 1; dfs(0);
        for (int i = 1; i < 6; ++i) { memcpy(d, a, sizeof(a)); mul(d, b, a); }
        memcpy(d, a, sizeof(a)); mul(d, c, a);
        memset(p, -1, sizeof(p));
        for (int i = 0, k = 0; i < t; ++i) for (int j = 0; j < t; ++j) if (a[i][j] || a[j][i]) { p[i] = k++; break; }
        for (int i = 0; i < t; ++i) if (p[i] >= 0) for (int j = 0; j < t; ++j) if (p[j] >= 0) x[p[i]][p[j]] = a[i][j];
    }
}

int solve(ULL n) {
    if (n & 1) return 0;
    return (PerfectMatch::solve(n) + Hamilton::solve(n) + CycleSubgraph::solve(n)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    PerfectMatch::init(); Hamilton::init(); CycleSubgraph::init();
    ULL n;
    while (cin >> n) cout << setw(4) << setfill('0') << solve(n) << '\n';
    return 0;
}
