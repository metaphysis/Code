// Subway
// UVa ID: 10691
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

struct Interval {
    double l, r, theta, alpha;
};

double normAng(double a) {
    a = fmod(a, 2 * PI);
    if (a < 0) a += 2 * PI;
    return a;
}

bool coveredByS(double s, const Interval& in) {
    double delta = s - in.theta;
    delta = atan2(sin(delta), cos(delta));          // 归一化到 [-PI, PI]
    return fabs(delta) <= in.alpha + EPS;
}

int solveForS(double s, const vector<Interval>& intervals) {
    vector<pair<double, double>> segs;
    for (const auto& in : intervals) {
        if (coveredByS(s, in)) continue;
        // 将区间映射到 (s, s+2π) 内
        double l = in.l, r = in.r;
        long long k = (long long)ceil((s - l) / (2 * PI) - 1e-9);
        while (l + 2 * PI * k <= s + EPS) ++k;
        double l2 = l + 2 * PI * k;
        double r2 = r + 2 * PI * k;
        if (r2 <= s + EPS) {                        // 安全保护
            while (r2 <= s + EPS) { ++k; l2 += 2 * PI; r2 += 2 * PI; }
        }
        segs.push_back({l2, r2});
    }
    if (segs.empty()) return 1;                     // 仅靠 s 覆盖所有区间

    sort(segs.begin(), segs.end(),
         [](const pair<double,double>& a, const pair<double,double>& b) {
             return a.second < b.second;
         });

    int cnt = 0;
    double last = s;                                // 起点 s 作为一个已选点
    for (auto& p : segs) {
        if (p.first > last + EPS) {
            ++cnt;
            last = p.second;
        }
    }
    return 1 + cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    while (N--) {
        int n;
        double d;
        cin >> n >> d;

        vector<Interval> intervals;
        for (int i = 0; i < n; ++i) {
            double x, y;
            cin >> x >> y;
            double r = hypot(x, y);
            if (r <= d + EPS) continue;             // 原点已覆盖
            double theta = atan2(y, x);
            if (theta < 0) theta += 2 * PI;
            double alpha = asin(d / r);
            double l = theta - alpha;
            double rr = theta + alpha;
            intervals.push_back({l, rr, theta, alpha});
        }

        if (intervals.empty()) {
            cout << 0 << '\n';
            continue;
        }

        vector<double> candidates;
        for (const auto& in : intervals) {
            candidates.push_back(normAng(in.l));
            candidates.push_back(normAng(in.r));
        }
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end(),
            [](double a, double b) { return fabs(a - b) < EPS; }),
            candidates.end());

        int ans = (int)intervals.size();            // 上限
        for (double s : candidates) {
            int cur = solveForS(s, intervals);
            if (cur < ans) ans = cur;
        }
        cout << ans << '\n';
    }
    return 0;
}
