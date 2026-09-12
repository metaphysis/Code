#include <bits/stdc++.h>
using namespace std;

struct Line {
    long double m, b;
};

struct Node {
    Line ln;
    long double left;
};

bool sameSlope(const Line &a, const Line &b) {
    return fabsl(a.m - b.m) < 1e-14L;
}

long double crossX(const Line &a, const Line &b) {
    return (a.b - b.b) / (b.m - a.m);
}

vector<Node> makeHull(vector<Line> ls) {
    sort(ls.begin(), ls.end(), [](const Line &a, const Line &b) {
        if (a.m != b.m) return a.m < b.m;
        return a.b < b.b;
    });
    vector<Line> uni;
    for (const Line &cur : ls) {
        if (uni.empty() || !sameSlope(uni.back(), cur)) uni.push_back(cur);
        else if (cur.b > uni.back().b) uni.back() = cur;
    }
    vector<Node> hull;
    for (const Line &cur : uni) {
        if (hull.empty()) {
            hull.push_back({cur, -1e100L});
            continue;
        }
        long double pos = crossX(hull.back().ln, cur);
        while (hull.size() > 1 && pos <= hull.back().left) {
            hull.pop_back();
            pos = crossX(hull.back().ln, cur);
        }
        hull.push_back({cur, pos});
    }
    return hull;
}

long double calc(const Line &ln, long double x) {
    return ln.m * x * x / 2.0L + ln.b * x;
}

long double getArea(const vector<Node> &hull, long double xl, long double xu) {
    long double ans = 0;
    int sz = hull.size();
    for (int i = 0; i < sz; i++) {
        long double l = max(xl, hull[i].left);
        long double r = min(xu, i + 1 < sz ? hull[i + 1].left : 1e100L);
        if (l < r) ans += calc(hull[i].ln, r) - calc(hull[i].ln, l);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<Line> ls, neg;
        for (int i = 0; i < n; i++) {
            long double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (fabsl(x1 - x2) < 1e-14L) continue;
            long double m = (y2 - y1) / (x2 - x1);
            long double b = y1 - m * x1;
            ls.push_back({m, b});
            neg.push_back({-m, -b});
        }
        long double xl, xu;
        cin >> xl >> xu;
        if (xl > xu) swap(xl, xu);
        vector<Node> upHull = makeHull(ls);
        vector<Node> downHull = makeHull(neg);
        long double ans = getArea(upHull, xl, xu) + getArea(downHull, xl, xu);
        cout << fixed << setprecision(6) << (double)ans << '\n';
    }
    return 0;
}
