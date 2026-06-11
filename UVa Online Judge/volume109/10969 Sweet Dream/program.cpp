// Sweet Dream
// UVa ID: 10969
// Verdict: Accepted
// Submission Date: 2026-06-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-10;

struct Circle { double x, y, r; };

double normAngle(double a) {
    while (a < 0) a += 2 * PI;
    while (a >= 2 * PI) a -= 2 * PI;
    return a;
}

vector<pair<double, double>> addInterval(vector<pair<double, double>> &intervals, double l, double r) {
    if (r - l > 2 * PI + EPS) {
        intervals.emplace_back(0, 2 * PI);
        return intervals;
    }
    l = normAngle(l);
    r = normAngle(r);
    if (l < r) intervals.emplace_back(l, r);
    else {
        intervals.emplace_back(l, 2 * PI);
        intervals.emplace_back(0, r);
    }
    return intervals;
}

double mergeAndGetCovered(vector<pair<double, double>> &intervals) {
    if (intervals.empty()) return 0.0;
    sort(intervals.begin(), intervals.end());
    double covered = 0.0;
    double curL = intervals[0].first, curR = intervals[0].second;
    for (size_t i = 1; i < intervals.size(); i++) {
        if (intervals[i].first <= curR + EPS) {
            curR = max(curR, intervals[i].second);
        } else {
            covered += curR - curL;
            curL = intervals[i].first;
            curR = intervals[i].second;
        }
    }
    covered += curR - curL;
    return covered;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        vector<Circle> c(N);
        for (int i = 0; i < N; i++) {
            scanf("%lf%lf%lf", &c[i].r, &c[i].x, &c[i].y);
        }

        double ans = 0.0;

        for (int i = 0; i < N; i++) {
            vector<pair<double, double>> blocked;

            for (int j = i + 1; j < N; j++) {
                double dx = c[j].x - c[i].x, dy = c[j].y - c[i].y;
                double d = sqrt(dx * dx + dy * dy);
                double R = c[i].r, r = c[j].r;

                if (d + R <= r + EPS) {
                    blocked.clear();
                    blocked.emplace_back(0, 2 * PI);
                    break;
                }
                if (d + r <= R + EPS || d >= R + r - EPS)
                    continue;

                double ang = atan2(dy, dx);
                double theta = acos((R * R + d * d - r * r) / (2 * R * d));
                addInterval(blocked, ang - theta, ang + theta);
            }

            double covered = mergeAndGetCovered(blocked);
            ans += (2 * PI - covered) * c[i].r;
        }

        printf("%.3lf\n", ans);
    }
    return 0;
}
