#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
};

struct Gate {
    long double y, x1, x2;
};

long double getDist(Point a, Point b) {
    long double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void relaxState(int id, Point src, long double cost, int n, vector<Gate> &gates, vector<vector<long double>> &dp, long double &ans) {
    const long double inf = 1e100L, eps = 1e-18L;
    long double lo, hi, dy, l, r, t, bestT;
    int j;
    lo = -inf;
    hi = inf;
    for (j = id + 1; j < n; j++) {
        dy = src.y - gates[j].y;
        l = (gates[j].x1 - src.x) / dy;
        r = (gates[j].x2 - src.x) / dy;
        if (j == n - 1) {
            lo = max(lo, l);
            hi = min(hi, r);
            if (lo <= hi + eps) {
                bestT = max(lo, min(hi, 0.0L));
                ans = min(ans, cost + dy * sqrt(1.0L + bestT * bestT));
            }
            break;
        }
        if (l >= lo - eps && l <= hi + eps) {
            dp[j][0] = min(dp[j][0], cost + dy * sqrt(1.0L + l * l));
        }
        if (r >= lo - eps && r <= hi + eps) {
            dp[j][1] = min(dp[j][1], cost + dy * sqrt(1.0L + r * r));
        }
        lo = max(lo, l);
        hi = min(hi, r);
        if (lo > hi + eps) break;
    }
}

long double solveCase(int n, Point start, vector<Gate> &gates) {
    const long double inf = 1e100L;
    vector<vector<long double>> dp(n, vector<long double>(2, inf));
    long double ans;
    Point p;
    int i;
    ans = inf;
    relaxState(-1, start, 0.0L, n, gates, dp, ans);
    for (i = 0; i < n - 1; i++) {
        p = {gates[i].x1, gates[i].y};
        if (dp[i][0] < inf) relaxState(i, p, dp[i][0], n, gates, dp, ans);
        p = {gates[i].x2, gates[i].y};
        if (dp[i][1] < inf) relaxState(i, p, dp[i][1], n, gates, dp, ans);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, i;
    Point start;
    vector<Gate> gates;
    while (cin >> n && n) {
        cin >> start.x >> start.y;
        gates.resize(n);
        for (i = 0; i < n; i++)
            cin >> gates[i].y >> gates[i].x1 >> gates[i].x2;
        cout << fixed << setprecision(12) << solveCase(n, start, gates) << '\n';
    }
    return 0;
}
