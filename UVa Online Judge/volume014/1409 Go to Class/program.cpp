#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

struct Gap {
    long long left, right;
};

bool samePoint(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

int addPoint(vector<Point> &points, const Point &point) {
    for (int i = 0; i < (int)points.size(); i++)
        if (samePoint(points[i], point))
            return i;
    points.push_back(point);
    return (int)points.size() - 1;
}

bool hasOpenXInterval(long double x0, long double dx, long double left, long double right, long double &low, long double &high) {
    const long double eps = 1e-12L;
    if (fabsl(dx) < eps) {
        if (x0 <= left + eps || x0 >= right - eps)
            return false;
        low = 0.0L;
        high = 1.0L;
        return true;
    }
    long double t1 = (left - x0) / dx, t2 = (right - x0) / dx;
    if (t1 > t2)
        swap(t1, t2);
    low = max((long double)0.0L, t1);
    high = min((long double)1.0L, t2);
    return low < high - eps;
}

bool isVisible(const Point &a, const Point &b, const vector<Gap> &xGaps, const vector<Gap> &yGaps) {
    const long double eps = 1e-12L;
    long double x0 = a.x, y0 = a.y, dx = b.x - a.x, dy = b.y - a.y;
    for (const Gap &xGap : xGaps) {
        long double low, high;
        if (!hasOpenXInterval(x0, dx, xGap.left, xGap.right, low, high))
            continue;
        long double y1 = y0 + dy * low, y2 = y0 + dy * high;
        long double yLow = min(y1, y2), yHigh = max(y1, y2);
        int left = 0, right = (int)yGaps.size();
        while (left < right) {
            int middle = (left + right) / 2;
            if ((long double)yGaps[middle].right <= yLow + eps)
                left = middle + 1;
            else
                right = middle;
        }
        if (left < (int)yGaps.size() && (long double)yGaps[left].left < yHigh - eps)
            return false;
    }
    return true;
}

int solve() {
    int n, m, caseId = 1;
    while (cin >> n >> m && (n != 0 || m != 0)) {
        long long sx, sy, tx, ty;
        cin >> sx >> sy >> tx >> ty;
        vector<long long> yRoad(2 * n), xRoad(2 * m);
        for (long long &value : yRoad)
            cin >> value;
        for (long long &value : xRoad)
            cin >> value;
        vector<Gap> xGaps, yGaps;
        for (int i = 0; i + 1 < m; i++)
            if (xRoad[2 * i + 1] < xRoad[2 * i + 2])
                xGaps.push_back({xRoad[2 * i + 1], xRoad[2 * i + 2]});
        for (int i = 0; i + 1 < n; i++)
            if (yRoad[2 * i + 1] < yRoad[2 * i + 2])
                yGaps.push_back({yRoad[2 * i + 1], yRoad[2 * i + 2]});
        vector<Point> points;
        int start = addPoint(points, {sx, sy}), target = addPoint(points, {tx, ty});
        addPoint(points, {xRoad.front(), yRoad.front()});
        addPoint(points, {xRoad.front(), yRoad.back()});
        addPoint(points, {xRoad.back(), yRoad.front()});
        addPoint(points, {xRoad.back(), yRoad.back()});
        for (const Gap &xGap : xGaps)
            for (const Gap &yGap : yGaps) {
                addPoint(points, {xGap.left, yGap.left});
                addPoint(points, {xGap.left, yGap.right});
                addPoint(points, {xGap.right, yGap.left});
                addPoint(points, {xGap.right, yGap.right});
            }
        int nodeCount = (int)points.size();
        const double inf = numeric_limits<double>::infinity();
        vector<double> dist(nodeCount, inf);
        vector<bool> used(nodeCount, false);
        dist[start] = 0.0;
        for (int step = 0; step < nodeCount; step++) {
            int current = -1;
            for (int i = 0; i < nodeCount; i++)
                if (!used[i] && (current == -1 || dist[i] < dist[current]))
                    current = i;
            if (current == -1 || dist[current] == inf)
                break;
            used[current] = true;
            for (int next = 0; next < nodeCount; next++) {
                if (used[next] || current == next)
                    continue;
                if (!isVisible(points[current], points[next], xGaps, yGaps))
                    continue;
                long double dx = points[current].x - points[next].x, dy = points[current].y - points[next].y;
                double edge = (double)sqrtl(dx * dx + dy * dy);
                dist[next] = min(dist[next], dist[current] + edge);
            }
        }
        cout << fixed << setprecision(4) << "Case " << caseId++ << ": " << dist[target] << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
