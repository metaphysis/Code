#include <bits/stdc++.h>
using namespace std;

const long long lim = 2000000000000000000LL;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long g = exgcd(b, a % b, x, y);
    long long t = x;
    x = y;
    y = t - a / b * y;
    return g;
}

bool mergeCrt(long long rem, long long len, long long &cur, long long &mod, bool &locked) {
    if (locked) return cur % len == rem;
    long long g = __gcd(mod, len), diff = rem - cur;
    if (diff % g != 0) return false;
    long long q = len / g, t = 0;
    if (q != 1) {
        long long x, y;
        exgcd((mod / g) % q, q, x, y);
        x = (x % q + q) % q;
        t = ((diff / g) % q + q) % q;
        t = (__int128)t * x % q;
    }
    __int128 newCur = (__int128)cur + (__int128)mod * t;
    __int128 newMod = (__int128)(mod / g) * len;
    if (newCur > lim) return false;
    cur = (long long)newCur;
    if (newMod > lim) {
        locked = true;
        mod = lim + 1;
    } else mod = (long long)newMod;
    return true;
}

long long solveCase(int m, int n, vector<int> &a) {
    int tot = m * n;
    vector<int> seq, nxt(tot), vis(tot), bel(tot), pos(tot);
    vector<vector<int>> cycles;
    for (int s = 0; s < m + n - 1; ++s) {
        int lo = max(0, s - n + 1), hi = min(m - 1, s);
        if (s % 2 == 0) {
            for (int r = hi; r >= lo; --r) seq.push_back(r * n + s - r);
        } else {
            for (int r = lo; r <= hi; ++r) seq.push_back(r * n + s - r);
        }
    }
    for (int i = 0; i < tot; ++i) nxt[seq[i]] = i;
    for (int i = 0; i < tot; ++i) {
        if (vis[i]) continue;
        int id = cycles.size(), u = i;
        vector<int> cyc;
        while (!vis[u]) {
            vis[u] = 1;
            bel[u] = id;
            pos[u] = cyc.size();
            cyc.push_back(u);
            u = nxt[u];
        }
        cycles.push_back(cyc);
    }
    long long cur = 0, mod = 1;
    bool locked = false;
    for (int id = 0; id < (int)cycles.size(); ++id) {
        vector<int> &cyc = cycles[id];
        int len = cyc.size();
        for (int u : cyc) {
            int tar = a[u] - 1;
            if (bel[tar] != id) return -1;
            long long rem = (pos[tar] - pos[u] + len) % len;
            if (!mergeCrt(rem, len, cur, mod, locked)) return -1;
        }
    }
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int m, n;
        cin >> m >> n;
        vector<int> a(m * n);
        for (int i = 0; i < m * n; ++i) cin >> a[i];
        cout << solveCase(m, n, a) << '\n';
    }
    return 0;
}
