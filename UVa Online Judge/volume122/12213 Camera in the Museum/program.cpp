#include <bits/stdc++.h>
using namespace std;

const double Eps = 1e-6;

struct Point {
    double x, y;
};

Point subPoint(Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

Point addPoint(Point a, Point b) {
    return {a.x + b.x, a.y + b.y};
}

Point mulPoint(Point a, double k) {
    return {a.x * k, a.y * k};
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double length(Point a) {
    return hypot(a.x, a.y);
}

Point rotatePoint(Point a, double rad) {
    double cs = cos(rad), sn = sin(rad);
    return {a.x * cs - a.y * sn, a.x * sn + a.y * cs};
}

double getPos(Point p, double w, double h) {
    if (fabs(p.y) < Eps)
        return max(0.0, min(w, p.x));
    if (fabs(p.x - w) < Eps)
        return w + max(0.0, min(h, p.y));
    if (fabs(p.y - h) < Eps)
        return w + h + max(0.0, min(w, w - p.x));
    return w + h + w + max(0.0, min(h, h - p.y));
}

Point getBoundary(Point p, Point dir, double w, double h) {
    double tx = 1e100, ty = 1e100, t;
    if (dir.x > Eps)
        tx = (w - p.x) / dir.x;
    else if (dir.x < -Eps)
        tx = -p.x / dir.x;
    if (dir.y > Eps)
        ty = (h - p.y) / dir.y;
    else if (dir.y < -Eps)
        ty = -p.y / dir.y;
    t = min(tx, ty);
    Point q = addPoint(p, mulPoint(dir, t));
    if (fabs(q.x) < Eps)
        q.x = 0;
    if (fabs(q.x - w) < Eps)
        q.x = w;
    if (fabs(q.y) < Eps)
        q.y = 0;
    if (fabs(q.y - h) < Eps)
        q.y = h;
    return q;
}

void addInterval(vector<pair<double, double>> &seg, double left, double right, double pm) {
    if (left > right) {
        seg.push_back({left, right + pm});
        seg.push_back({left + pm, right + pm + pm});
    } else {
        seg.push_back({left, right});
        seg.push_back({left + pm, right + pm});
    }
}

int solveCase(double h, double w, double r, double cx, double cy, int n) {
    vector<pair<double, double>> seg;
    double pm = 2.0 * (w + h);
    Point center = {cx, cy};
    for (int i = 0; i < n; i++) {
        Point item, vec, dir0, dir1, bound0, bound1;
        double dis, ang, pos0, pos1;
        cin >> item.x >> item.y;
        vec = subPoint(center, item);
        dis = length(vec);
        ang = asin(r / dis);
        dir0 = rotatePoint(vec, ang);
        dir1 = rotatePoint(vec, -ang);
        bound0 = getBoundary(item, dir0, w, h);
        bound1 = getBoundary(item, dir1, w, h);
        pos0 = getPos(bound0, w, h);
        pos1 = getPos(bound1, w, h);
        addInterval(seg, pos0, pos1, pm);
    }
    sort(seg.begin(), seg.end());
    priority_queue<double, vector<double>, greater<double>> que;
    int ans = 0;
    for (int i = 0; i < static_cast<int>(seg.size()); i++) {
        while (!que.empty() && que.top() < seg[i].first - Eps)
            que.pop();
        que.push(seg[i].second);
        ans = max(ans, static_cast<int>(que.size()));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double h, w, r, cx, cy;
    int n, caseId = 1;
    while (cin >> h >> w >> r >> cx >> cy >> n) {
        if (h == 0 && w == 0 && r == 0 && cx == 0 && cy == 0 && n == 0)
            break;
        cout << "Case " << caseId++ << ": " << solveCase(h, w, r, cx, cy, n) << '\n';
    }
    return 0;
}
