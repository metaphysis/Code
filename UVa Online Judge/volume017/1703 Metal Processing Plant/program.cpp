#include <bits/stdc++.h>
using namespace std;

int n, w, tim, cnt, px, py;
vector<long long> val;
vector<vector<long long> > dis;
vector<unsigned long long> ms;
vector<int> dfn, low, stk, ins, bel;

long long getPos(int id, int i, int k) {
    return ((long long)id * n + i) * w + k;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    stk.push_back(u);
    ins[u] = 1;
    int id = u < n ? px : py, row = u < n ? u : u - n, add = u < n ? n : 0;
    for (int k = 0; k < w; ++k) {
        unsigned long long now = ms[getPos(id, row, k)];
        while (now) {
            int b = __builtin_ctzll(now), v = k * 64 + b + add;
            now &= now - 1;
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (ins[v]) low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        while (true) {
            int v = stk.back();
            stk.pop_back();
            ins[v] = 0;
            bel[v] = cnt;
            if (v == u) break;
        }
        ++cnt;
    }
}

bool check(int x, int y) {
    int m = n * 2;
    px = x;
    py = y;
    tim = cnt = 0;
    dfn.assign(m, 0);
    low.assign(m, 0);
    ins.assign(m, 0);
    bel.assign(m, -1);
    stk.clear();
    for (int i = 0; i < m; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 0; i < n; ++i)
        if (bel[i] == bel[i + n]) return false;
    return true;
}

long long getInit() {
    long long ans = LLONG_MAX;
    for (int s = 0; s < n; ++s) {
        long long cur = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (i != s && j != s) cur = max(cur, dis[i][j]);
        ans = min(ans, cur);
    }
    return ans;
}

void buildMask() {
    int m = val.size();
    w = (n + 63) >> 6;
    ms.assign((long long)m * n * w, 0);
    for (int i = 0; i < n; ++i) {
        vector<pair<long long, int> > ord;
        vector<unsigned long long> cur(w, 0);
        for (int j = 0; j < n; ++j)
            if (i != j) {
                ord.push_back(make_pair(dis[i][j], j));
                cur[j >> 6] |= 1ULL << (j & 63);
            }
        sort(ord.begin(), ord.end());
        int p = 0;
        for (int k = 0; k < m; ++k) {
            while (p < n - 1 && ord[p].first <= val[k]) {
                int j = ord[p].second;
                cur[j >> 6] &= ~(1ULL << (j & 63));
                ++p;
            }
            for (int q = 0; q < w; ++q) ms[getPos(k, i, q)] = cur[q];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        dis.assign(n, vector<long long>(n, 0));
        val.clear();
        val.push_back(0);
        for (int i = 0; i < n - 1; ++i)
            for (int j = i + 1; j < n; ++j) {
                cin >> dis[i][j];
                dis[j][i] = dis[i][j];
                val.push_back(dis[i][j]);
            }
        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }
        sort(val.begin(), val.end());
        val.erase(unique(val.begin(), val.end()), val.end());
        buildMask();
        long long ans = getInit();
        int m = val.size();
        for (int i = 0; i < m; ++i) {
            long long x = val[i], lim = ans - x - 1;
            if (x * 2 >= ans) break;
            int r = upper_bound(val.begin() + i, val.end(), lim) - val.begin() - 1;
            if (r < i || !check(i, r)) continue;
            int l = i;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (check(i, mid)) r = mid;
                else l = mid + 1;
            }
            ans = min(ans, x + val[l]);
        }
        cout << ans << '\n';
    }
    return 0;
}
