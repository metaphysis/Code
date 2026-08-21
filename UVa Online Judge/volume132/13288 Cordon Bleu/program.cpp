#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long dis(const Point &a, const Point &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

long long hungarian(const vector<vector<long long>> &w) {
    int n = (int)w.size() - 1;
    const long long inf = (1LL << 60);
    vector<long long> u(n + 1), v(n + 1), minv(n + 1);
    vector<int> p(n + 1), way(n + 1);
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        fill(minv.begin(), minv.end(), inf);
        vector<bool> used(n + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            long long delta = inf;
            for (int j = 1; j <= n; j++) {
                if (used[j]) continue;
                long long cur = -w[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }
                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }
            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }
    long long ans = 0;
    for (int j = 1; j <= n; j++) ans += w[p[j]][j];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<Point> bottles(n + 1), couriers(m + 1);
        for (int i = 1; i <= n; i++) cin >> bottles[i].x >> bottles[i].y;
        for (int i = 1; i <= m; i++) cin >> couriers[i].x >> couriers[i].y;
        Point rest;
        cin >> rest.x >> rest.y;
        long long base = 0, maxEdge = -(1LL << 60);
        for (int i = 1; i <= n; i++) base += 2 * dis(bottles[i], rest);
        int k = max(n, m);
        vector<vector<long long>> w(k + 1, vector<long long>(k + 1, 0));
        if (n <= m) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    long long save = dis(bottles[i], rest) - dis(couriers[j], bottles[i]);
                    maxEdge = max(maxEdge, save);
                    w[i][j] = max(0LL, save);
                }
            }
        } else {
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    long long save = dis(bottles[j], rest) - dis(couriers[i], bottles[j]);
                    maxEdge = max(maxEdge, save);
                    w[i][j] = max(0LL, save);
                }
            }
        }
        long long best = hungarian(w);
        if (best == 0) best = maxEdge;
        cout << base - best << '\n';
    }
    return 0;
}
