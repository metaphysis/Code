#include <bits/stdc++.h>
using namespace std;

bool isBoundary(long double value) {
    return fabsl(value - roundl(value)) < 1e-12L;
}

void addCross(vector<long double>& points, long double first, long double second, long double unit) {
    long double delta;
    long double t;
    long long left, right, index;
    delta = second - first;
    if (fabsl(delta) < 1e-18L)
        return;
    left = (long long)floorl(min(first, second) / unit) - 2;
    right = (long long)ceill(max(first, second) / unit) + 2;
    for (index = left; index <= right; index++) {
        t = (index * unit - first) / delta;
        if (t > 1e-12L && t < 1.0L - 1e-12L)
            points.push_back(t);
    }
}

long long countTriangle(int base, int height, long double x1, long double y1, long double x2, long double y2) {
    vector<long double> points;
    long double dx, dy, u1, u2, v1, v2, t, mid;
    long double x, y, a, b, c;
    long long ia, ib, ic;
    set<tuple<long long, long long, long long>> triangles;
    dx = x2 - x1;
    dy = y2 - y1;
    u1 = x1 - (long double)base * y1 / (2.0L * height);
    u2 = x2 - (long double)base * y2 / (2.0L * height);
    v1 = x1 + (long double)base * y1 / (2.0L * height);
    v2 = x2 + (long double)base * y2 / (2.0L * height);
    points.push_back(0.0L);
    points.push_back(1.0L);
    addCross(points, y1, y2, height);
    addCross(points, u1, u2, base);
    addCross(points, v1, v2, base);
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end(), [](long double first, long double second) {
        return fabsl(first - second) < 1e-12L;
    }), points.end());
    for (size_t index = 0; index + 1 < points.size(); index++) {
        mid = (points[index] + points[index + 1]) / 2.0L;
        x = x1 + dx * mid;
        y = y1 + dy * mid;
        a = y / height;
        b = (x - (long double)base * y / (2.0L * height)) / base;
        c = (x + (long double)base * y / (2.0L * height)) / base;
        if (isBoundary(a) || isBoundary(b) || isBoundary(c))
            continue;
        ia = (long long)floorl(a);
        ib = (long long)floorl(b);
        ic = (long long)floorl(c);
        triangles.insert(make_tuple(ia, ib, ic));
    }
    return (long long)triangles.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int base, height, x1, y1, x2, y2;
    while (cin >> base >> height >> x1 >> y1 >> x2 >> y2) {
        if (base == 0 && height == 0 && x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)
            break;
        cout << countTriangle(base, height, x1, y1, x2, y2) << '\n';
    }
    return 0;
}
