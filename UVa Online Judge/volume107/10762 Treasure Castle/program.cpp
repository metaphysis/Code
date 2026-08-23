#include <bits/stdc++.h>
using namespace std;
struct Point {
    int x, y;
};
struct Wall {
    int x1, y1, x2, y2;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, cas = 0;
    while (cin >> n && n) {
        vector<Point> p(n + 2);
        for (int i = 0; i < n; i++)
            cin >> p[i].x >> p[i].y;
        cin >> p[n].x >> p[n].y >> p[n + 1].x >> p[n + 1].y;
        vector<Wall> wall;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            wall.push_back({p[i].x, p[i].y, p[j].x, p[j].y});
        }
        vector<int> xs, ys;
        for (int i = 0; i < n + 2; i++) {
            xs.push_back(p[i].x);
            ys.push_back(p[i].y);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        int nx = xs.size(), ny = ys.size();
        vector<unsigned short> hp(ny * nx, 0), vp(nx * ny, 0);
        for (int iy = 0; iy < ny; iy++) {
            int y = ys[iy];
            vector<int> cross;
            vector<int> diff(nx + 1, 0);
            for (const Wall &w : wall) {
                if (w.x1 == w.x2) {
                    int low = min(w.y1, w.y2), high = max(w.y1, w.y2);
                    if (low < y && y <= high)
                        cross.push_back(w.x1);
                } else if (min(w.y1, w.y2) <= y && y <= max(w.y1, w.y2)) {
                    int l = lower_bound(xs.begin(), xs.end(), min(w.x1, w.x2)) - xs.begin();
                    int r = lower_bound(xs.begin(), xs.end(), max(w.x1, w.x2)) - xs.begin();
                    diff[l]++;
                    diff[r]--;
                }
            }
            sort(cross.begin(), cross.end());
            int parity = 0, at = 0, onWall = 0;
            for (int ix = 0; ix + 1 < nx; ix++) {
                while (at < (int)cross.size() && cross[at] <= xs[ix]) {
                    parity ^= 1;
                    at++;
                }
                onWall += diff[ix];
                bool ok = parity || onWall > 0;
                hp[iy * nx + ix + 1] = hp[iy * nx + ix] + (ok ? 0 : 1);
            }
        }
        for (int ix = 0; ix < nx; ix++) {
            int x = xs[ix];
            vector<int> cross;
            vector<int> diff(ny + 1, 0);
            for (const Wall &w : wall) {
                if (w.y1 == w.y2) {
                    int low = min(w.x1, w.x2), high = max(w.x1, w.x2);
                    if (low < x && x <= high)
                        cross.push_back(w.y1);
                } else if (min(w.x1, w.x2) <= x && x <= max(w.x1, w.x2)) {
                    int l = lower_bound(ys.begin(), ys.end(), min(w.y1, w.y2)) - ys.begin();
                    int r = lower_bound(ys.begin(), ys.end(), max(w.y1, w.y2)) - ys.begin();
                    diff[l]++;
                    diff[r]--;
                }
            }
            sort(cross.begin(), cross.end());
            int parity = 0, at = 0, onWall = 0;
            for (int iy = 0; iy + 1 < ny; iy++) {
                while (at < (int)cross.size() && cross[at] <= ys[iy]) {
                    parity ^= 1;
                    at++;
                }
                onWall += diff[iy];
                bool ok = parity || onWall > 0;
                vp[ix * ny + iy + 1] = vp[ix * ny + iy] + (ok ? 0 : 1);
            }
        }
        auto hOk = [&](int y, int x1, int x2) {
            int iy = lower_bound(ys.begin(), ys.end(), y) - ys.begin();
            int a = lower_bound(xs.begin(), xs.end(), min(x1, x2)) - xs.begin();
            int b = lower_bound(xs.begin(), xs.end(), max(x1, x2)) - xs.begin();
            return hp[iy * nx + b] == hp[iy * nx + a];
        };
        auto vOk = [&](int x, int y1, int y2) {
            int ix = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
            int a = lower_bound(ys.begin(), ys.end(), min(y1, y2)) - ys.begin();
            int b = lower_bound(ys.begin(), ys.end(), max(y1, y2)) - ys.begin();
            return vp[ix * ny + b] == vp[ix * ny + a];
        };
        auto canGo = [&](const Point &a, const Point &b) {
            bool first = hOk(a.y, a.x, b.x) && vOk(b.x, a.y, b.y);
            bool second = vOk(a.x, a.y, b.y) && hOk(b.y, a.x, b.x);
            return first || second;
        };
        const int inf = 1e9;
        vector<int> dis(n + 2, inf);
        vector<char> used(n + 2, 0);
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
        dis[n] = 0;
        que.push({0, n});
        while (!que.empty()) {
            int d = que.top().first, u = que.top().second;
            que.pop();
            if (used[u])
                continue;
            used[u] = 1;
            for (int v = 0; v < n + 2; v++) {
                if (used[v] || !canGo(p[u], p[v]))
                    continue;
                int nd = d + abs(p[u].x - p[v].x) + abs(p[u].y - p[v].y);
                if (nd < dis[v]) {
                    dis[v] = nd;
                    que.push({nd, v});
                }
            }
        }
        cout << "Castle " << ++cas << ": " << dis[n + 1] << '\n';
    }
    return 0;
}
