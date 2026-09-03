#include <bits/stdc++.h>
using namespace std;

const double Pi = acos(-1.0);
const double TwoPi = 2.0 * Pi;
const double Eps = 1e-12;

struct Interval {
    double l, r;
    Interval() {}
    Interval(double left, double right) : l(left), r(right) {}
};

bool cmpInterval(const Interval &a, const Interval &b) {
    if (fabs(a.l - b.l) > Eps) return a.l < b.l;
    return a.r < b.r;
}

vector<Interval> mergeIntervals(vector<Interval> intervals) {
    vector<Interval> result;
    if (intervals.empty()) return result;
    sort(intervals.begin(), intervals.end(), cmpInterval);
    result.push_back(intervals[0]);
    for (int i = 1; i < (int)intervals.size(); i++) {
        if (intervals[i].l <= result.back().r + Eps)
            result.back().r = max(result.back().r, intervals[i].r);
        else
            result.push_back(intervals[i]);
    }
    return result;
}

vector<Interval> buildSafeIntervals(int wallCount) {
    vector<Interval> walls;
    for (int i = 0; i < wallCount; i++) {
        double x, y;
        cin >> x >> y;
        if (x <= y) {
            walls.push_back(Interval(x, y));
        } else {
            walls.push_back(Interval(0.0, y));
            walls.push_back(Interval(x, TwoPi));
        }
    }
    walls = mergeIntervals(walls);
    vector<Interval> safe;
    double last = 0.0;
    for (const Interval &wall : walls) {
        if (wall.l > last + Eps)
            safe.push_back(Interval(last, wall.l));
        last = max(last, wall.r);
    }
    if (last < TwoPi - Eps)
        safe.push_back(Interval(last, TwoPi));
    return safe;
}

vector<Interval> expandIntervals(const vector<Interval> &source, double distance) {
    vector<Interval> expanded;
    for (const Interval &interval : source) {
        if (interval.r - interval.l + 2.0 * distance >= TwoPi - Eps) {
            expanded.clear();
            expanded.push_back(Interval(0.0, TwoPi));
            return expanded;
        }
        double left = interval.l - distance, right = interval.r + distance;
        while (left < 0.0) {
            left += TwoPi;
            right += TwoPi;
        }
        while (right > TwoPi) {
            left -= TwoPi;
            right -= TwoPi;
        }
        if (left >= 0.0 && right <= TwoPi) {
            expanded.push_back(Interval(left, right));
        } else if (left < 0.0) {
            expanded.push_back(Interval(0.0, right));
            expanded.push_back(Interval(left + TwoPi, TwoPi));
        } else {
            expanded.push_back(Interval(0.0, right - TwoPi));
            expanded.push_back(Interval(left, TwoPi));
        }
    }
    return mergeIntervals(expanded);
}

vector<Interval> intersectIntervals(const vector<Interval> &a, const vector<Interval> &b) {
    vector<Interval> result;
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        double left = max(a[i].l, b[j].l), right = min(a[i].r, b[j].r);
        if (left <= right + Eps)
            result.push_back(Interval(left, right));
        if (a[i].r < b[j].r)
            i++;
        else
            j++;
    }
    return mergeIntervals(result);
}

bool check(const vector<vector<Interval>> &safe, double p) {
    if (safe.empty() || safe[0].empty()) return false;
    vector<Interval> reachable = safe[0];
    double distance = TwoPi * p;
    for (int i = 1; i < (int)safe.size(); i++) {
        if (safe[i].empty()) return false;
        vector<Interval> expanded = expandIntervals(reachable, distance);
        reachable = intersectIntervals(expanded, safe[i]);
        if (reachable.empty()) return false;
    }
    return !reachable.empty();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int n;
        cin >> n;
        vector<vector<Interval>> safe(n);
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            safe[i] = buildSafeIntervals(k);
        }
        double left = 0.0, right = 0.5, answer;
        for (int i = 0; i < 60; i++) {
            double mid = (left + right) / 2.0;
            if (check(safe, mid)) {
                answer = mid;
                right = mid;
            }
            else
                left = mid;
        }
        cout << "Case #" << caseId << ": " << fixed << setprecision(4) << answer << '\n';
    }
    return 0;
}
