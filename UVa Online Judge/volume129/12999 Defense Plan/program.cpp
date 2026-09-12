#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<Point> getHull(vector<Point> p) {
    sort(p.begin(), p.end(), [](const Point &a, const Point &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    vector<Point> q, low, up;
    for (const Point &v : p) {
        if (q.empty() || q.back().x != v.x || q.back().y != v.y) q.push_back(v);
    }
    for (const Point &v : q) {
        while (low.size() >= 2 && cross(low[low.size() - 2], low.back(), v) <= 0) low.pop_back();
        low.push_back(v);
    }
    for (int i = (int)q.size() - 1; i >= 0; i--) {
        while (up.size() >= 2 && cross(up[up.size() - 2], up.back(), q[i]) <= 0) up.pop_back();
        up.push_back(q[i]);
    }
    low.pop_back();
    up.pop_back();
    low.insert(low.end(), up.begin(), up.end());
    return low;
}

long long getArea2(const vector<Point> &p) {
    long long sum = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) sum += p[i].x * p[(i + 1) % n].y - p[i].y * p[(i + 1) % n].x;
    return llabs(sum);
}

long long solve(const vector<Point> &h, int k) {
    const long long neg = -(1LL << 60);
    long long ans = 0;
    int m = h.size();
    if (m <= k) return getArea2(h);
    for (int s = 0; s <= m - k; s++) {
        vector<vector<long long>> dp(k + 1, vector<long long>(m, neg));
        for (int j = s + 1; j < m; j++) dp[2][j] = 0;
        for (int cnt = 3; cnt <= k; cnt++) {
            for (int j = s + cnt - 1; j < m; j++) {
                for (int t = s + cnt - 2; t < j; t++) {
                    if (dp[cnt - 1][t] == neg) continue;
                    dp[cnt][j] = max(dp[cnt][j], dp[cnt - 1][t] + cross(h[s], h[t], h[j]));
                }
            }
        }
        for (int j = s + k - 1; j < m; j++) ans = max(ans, dp[k][j]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testNum;
    cin >> testNum;
    for (int tc = 1; tc <= testNum; tc++) {
        int p, n;
        cin >> p >> n;
        vector<Point> a(p);
        for (int i = 0; i < p; i++) cin >> a[i].x >> a[i].y;
        vector<Point> h = getHull(a);
        long long area2 = solve(h, n);
        cout << "Case " << tc << ": " << fixed << setprecision(3) << area2 / 2.0 << '\n';
    }
    return 0;
}
