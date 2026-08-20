#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
int n, k, fullMask;
vector<double> xs, ys;
vector<int> memo;

bool canCover(double r) {
    vector<int> masks;
    auto addMask = [&](double cx, double cy) {
        int mask = 0;
        for (int i = 0; i < n; i++) {
            double dx = xs[i] - cx, dy = ys[i] - cy;
            if (dx * dx + dy * dy <= r * r + eps) mask |= 1 << i;
        }
        masks.push_back(mask);
    };
    for (int i = 0; i < n; i++) addMask(xs[i], ys[i]);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dx = xs[j] - xs[i], dy = ys[j] - ys[i];
            double d = hypot(dx, dy);
            if (d > 2.0 * r + eps) continue;
            double mx = (xs[i] + xs[j]) / 2.0, my = (ys[i] + ys[j]) / 2.0;
            double h = sqrt(max(0.0, r * r - d * d / 4.0));
            double ux = -dy / d, uy = dx / d;
            addMask(mx + ux * h, my + uy * h);
            addMask(mx - ux * h, my - uy * h);
        }
    }
    sort(masks.begin(), masks.end());
    masks.erase(unique(masks.begin(), masks.end()), masks.end());
    vector<vector<int>> choices(n);
    for (int mask : masks)
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) choices[i].push_back(mask);
    memo.assign(1 << n, k + 1);
    function<bool(int, int)> dfs = [&](int covered, int used) {
        if (covered == fullMask) return true;
        if (used == k || used >= memo[covered]) return false;
        memo[covered] = used;
        int p = 0;
        while (covered >> p & 1) p++;
        for (int mask : choices[p])
            if (dfs(covered | mask, used + 1)) return true;
        return false;
    };
    return dfs(0, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cin >> n >> k;
        xs.resize(n);
        ys.resize(n);
        for (int i = 0; i < n; i++) cin >> xs[i] >> ys[i];
        fullMask = (1 << n) - 1;
        double lo = 0.0, hi = 15000.0;
        for (int it = 0; it < 45; it++) {
            double mid = (lo + hi) / 2.0;
            if (canCover(mid)) hi = mid;
            else lo = mid;
        }
        cout << fixed << setprecision(2);
        cout << "Case " << tc << ": " << hi + 1e-8 << '\n';
    }
    return 0;
}
