#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

struct Tri {
    int a, b, c;
    long long x, y, z;
};

long long getSqrt(__int128 val) {
    long long res = sqrt((long double)val);
    while ((__int128)res * res > val) --res;
    while ((__int128)(res + 1) * (res + 1) <= val) ++res;
    return res;
}

Pt getPt(Pt a, Pt b, long long u, long long v, long long w) {
    long long dx = b.x - a.x, dy = b.y - a.y, sum = u + w - v;
    __int128 del = (__int128)4 * u * w - (__int128)sum * sum;
    long long rt = getSqrt(del);
    __int128 den = (__int128)2 * u;
    Pt res;
    res.x = a.x + (long long)(((__int128)sum * dx - (__int128)rt * dy) / den);
    res.y = a.y + (long long)(((__int128)sum * dy + (__int128)rt * dx) / den);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m && n != 0) {
        vector<Tri> tri(n);
        vector<vector<int> > adj(m + 1);
        for (int i = 0; i < n; ++i) {
            cin >> tri[i].a >> tri[i].b >> tri[i].c >> tri[i].x >> tri[i].y >> tri[i].z;
            adj[tri[i].a].push_back(i);
            adj[tri[i].b].push_back(i);
            adj[tri[i].c].push_back(i);
        }
        vector<Pt> pos(m + 1);
        vector<bool> vis(m + 1, false);
        queue<int> que;
        auto addPt = [&](int id, Pt val) {
            if (vis[id]) return;
            vis[id] = true;
            pos[id] = val;
            que.push(id);
        };
        if (m >= 1) addPt(1, {0, 0});
        if (m >= 2) addPt(2, {0, 1});
        if (m >= 3) addPt(3, {1, 0});
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            for (int id : adj[cur]) {
                Tri now = tri[id];
                int cnt = vis[now.a] + vis[now.b] + vis[now.c];
                if (cnt != 2) continue;
                if (!vis[now.c]) addPt(now.c, getPt(pos[now.a], pos[now.b], now.x, now.y, now.z));
                else if (!vis[now.a]) addPt(now.a, getPt(pos[now.b], pos[now.c], now.y, now.z, now.x));
                else if (!vis[now.b]) addPt(now.b, getPt(pos[now.c], pos[now.a], now.z, now.x, now.y));
            }
        }
        for (int i = 1; i <= m; ++i)
            cout << pos[i].x << ' ' << pos[i].y << '\n';
    }
    return 0;
}
