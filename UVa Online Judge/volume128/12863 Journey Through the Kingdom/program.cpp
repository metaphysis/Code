#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);
int r, c, n, s, base;
vector<int> val, rr, cc;
vector<long long> dis;

int getId(int x, int y) {
    return x * base + y;
}

void relax(int id, long long d, priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> &pq) {
    if (d < dis[id]) {
        dis[id] = d;
        pq.push({d, id});
    }
}

void addRect(int x1, int x2, int y1, int y2, long long d, priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> &pq) {
    for (int l = x1 + s, u = x2 + s + 1; l < u; l >>= 1, u >>= 1) {
        if (l & 1) {
            for (int a = y1 + s, b = y2 + s + 1; a < b; a >>= 1, b >>= 1) {
                if (a & 1) relax(getId(l, a++), d, pq);
                if (b & 1) relax(getId(l, --b), d, pq);
            }
            l++;
        }
        if (u & 1) {
            --u;
            for (int a = y1 + s, b = y2 + s + 1; a < b; a >>= 1, b >>= 1) {
                if (a & 1) relax(getId(u, a++), d, pq);
                if (b & 1) relax(getId(u, --b), d, pq);
            }
        }
    }
}

long long dijkstra(int sx, int sy, int tx, int ty) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    fill(dis.begin(), dis.end(), inf);
    int st = getId(s + sx, s + sy), ed = getId(s + tx, s + ty);
    relax(st, 0, pq);
    while (!pq.empty()) {
        long long d = pq.top().first;
        int id = pq.top().second;
        pq.pop();
        if (d != dis[id]) continue;
        if (id == ed) return d;
        int x = id / base, y = id % base;
        if (y < s) {
            relax(getId(x, y << 1), d, pq);
            relax(getId(x, y << 1 | 1), d, pq);
        } else if (x < s) {
            relax(getId(x << 1, y), d, pq);
            relax(getId(x << 1 | 1, y), d, pq);
        } else {
            int i = x - s, j = y - s;
            if (i >= r || j >= c) continue;
            int p = i * c + j;
            int x1 = max(0, i - rr[p]), x2 = min(r - 1, i + rr[p]);
            int y1 = max(0, j - cc[p]), y2 = min(c - 1, j + cc[p]);
            addRect(x1, x2, y1, y2, d + val[p], pq);
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> r >> c >> n) {
        s = 1;
        while (s < max(r, c)) s <<= 1;
        base = s << 1;
        int cnt = r * c;
        val.resize(cnt);
        rr.resize(cnt);
        cc.resize(cnt);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) cin >> val[i * c + j];
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) cin >> rr[i * c + j];
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) cin >> cc[i * c + j];
        vector<pair<int, int>> path(n);
        for (int i = 0; i < n; i++) {
            cin >> path[i].first >> path[i].second;
            path[i].first--;
            path[i].second--;
        }
        dis.assign(base * base, inf);
        for (int i = 0; i + 1 < n; i++) {
            if (i) cout << ' ';
            cout << dijkstra(path[i].first, path[i].second, path[i + 1].first, path[i + 1].second);
        }
        cout << '\n';
    }
    return 0;
}
