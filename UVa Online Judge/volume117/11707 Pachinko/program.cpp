#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

struct Seg {
    double x1, y1, x2, y2, lx, ly;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n != -1) {
        vector<Seg> seg(n);
        vector<double> pos = {-100.0, -10.0, 10.0, 100.0};
        for (int i = 0; i < n; i++) {
            cin >> seg[i].x1 >> seg[i].y1 >> seg[i].x2 >> seg[i].y2;
            if (seg[i].y1 < seg[i].y2) {
                seg[i].lx = seg[i].x1;
                seg[i].ly = seg[i].y1;
            } else {
                seg[i].lx = seg[i].x2;
                seg[i].ly = seg[i].y2;
            }
            pos.push_back(seg[i].x1);
            pos.push_back(seg[i].x2);
        }
        sort(pos.begin(), pos.end());
        pos.erase(unique(pos.begin(), pos.end(), [](double a, double b) {
            return fabs(a - b) < eps;
        }), pos.end());
        vector<double> test = pos;
        int m = pos.size();
        for (int i = 0; i + 1 < m; i++)
            if (pos[i + 1] - pos[i] > eps) test.push_back((pos[i] + pos[i + 1]) / 2.0);
        auto getHit = [&](double x, double lim) {
            int id = -1;
            double best = -1.0;
            for (int i = 0; i < n; i++) {
                if (x < seg[i].x1 - eps || x > seg[i].x2 + eps) continue;
                double y = seg[i].y1 + (seg[i].y2 - seg[i].y1) * (x - seg[i].x1) / (seg[i].x2 - seg[i].x1);
                if (y < lim - eps && y > best) {
                    best = y;
                    id = i;
                }
            }
            return id;
        };
        vector<int> nxt(n), state(n);
        for (int i = 0; i < n; i++) nxt[i] = getHit(seg[i].lx, seg[i].ly);
        function<bool(int)> dfs = [&](int u) {
            if (state[u] == 2) return true;
            if (state[u] == 3) return false;
            state[u] = 1;
            if (nxt[u] == -1) {
                if (seg[u].lx >= -10.0 - eps && seg[u].lx <= 10.0 + eps) state[u] = 2;
                else state[u] = 3;
            } else if (dfs(nxt[u])) state[u] = 2;
            else state[u] = 3;
            return state[u] == 2;
        };
        bool ok = false;
        for (double x : test) {
            if (x <= -100.0 + eps || x >= 100.0 - eps) continue;
            int id = getHit(x, 100.0);
            if (id == -1) {
                if (x >= -10.0 - eps && x <= 10.0 + eps) ok = true;
            } else if (dfs(id)) ok = true;
        }
        cout << (ok ? "yes" : "no") << '\n';
    }
    return 0;
}
