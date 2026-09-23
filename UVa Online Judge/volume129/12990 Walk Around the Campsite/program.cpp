#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;

struct Point {
    double x, y;
    Point operator + (const Point &other) const { return {x + other.x, y + other.y}; }
    Point operator - (const Point &other) const { return {x - other.x, y - other.y}; }
    Point operator * (double value) const { return {x * value, y * value}; }
};

struct Fort {
    Point pos;
    double value;
};

double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

double cross(Point a, Point b, Point c) { return cross(b - a, c - a); }

double distanceOf(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

bool onSegment(Point a, Point b, Point p) {
    if (fabs(cross(a, b, p)) > eps) return false;
    return min(a.x, b.x) - eps <= p.x && p.x <= max(a.x, b.x) + eps &&
           min(a.y, b.y) - eps <= p.y && p.y <= max(a.y, b.y) + eps;
}

bool segmentsIntersect(Point a, Point b, Point c, Point d) {
    double c1 = cross(a, b, c), c2 = cross(a, b, d);
    double c3 = cross(c, d, a), c4 = cross(c, d, b);
    if (((c1 > eps && c2 < -eps) || (c1 < -eps && c2 > eps)) &&
        ((c3 > eps && c4 < -eps) || (c3 < -eps && c4 > eps)))
        return true;
    if (fabs(c1) <= eps && onSegment(a, b, c)) return true;
    if (fabs(c2) <= eps && onSegment(a, b, d)) return true;
    if (fabs(c3) <= eps && onSegment(c, d, a)) return true;
    if (fabs(c4) <= eps && onSegment(c, d, b)) return true;
    return false;
}

double polygonArea(const vector<Fort> &forts) {
    int n = forts.size();
    double area = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += forts[i].pos.x * forts[j].pos.y - forts[j].pos.x * forts[i].pos.y;
    }
    return area * 0.5;
}

bool isInsideCone(const vector<Fort> &forts, int index, int target, double direction) {
    int n = forts.size();
    int prev = (index - 1 + n) % n, next = (index + 1) % n;
    Point center = forts[index].pos;
    Point left = forts[prev].pos - center;
    Point right = forts[next].pos - center;
    Point move = forts[target].pos - center;
    double corner = cross(left, right) * direction;
    double first = cross(left, move) * direction;
    double second = cross(move, right) * direction;
    if (corner <= eps) return first <= eps && second <= eps;
    return first <= eps || second <= eps;
}

bool canWalk(const vector<Fort> &forts, int from, int to, double direction) {
    int n = forts.size();
    if (to == from + 1 || (from == 0 && to == n - 1)) return true;
    if (isInsideCone(forts, from, to, direction)) return false;
    Point a = forts[from].pos;
    Point b = forts[to].pos;
    for (int k = 0; k < n; ++k) {
        int next = (k + 1) % n;
        if (k == from || next == from || k == to || next == to) continue;
        if (segmentsIntersect(a, b, forts[k].pos, forts[next].pos)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; ++cs) {
        int n;
        cin >> n;
        vector<Fort> forts(n);
        for (int i = 0; i < n; ++i) cin >> forts[i].pos.x >> forts[i].pos.y >> forts[i].value;
        double direction = polygonArea(forts) >= 0.0 ? 1.0 : -1.0;
        vector<double> dp(n, -1e100);
        dp[0] = forts[0].value;
        for (int i = 0; i < n; ++i) {
            if (dp[i] < -1e90) continue;
            for (int j = i + 1; j < n; ++j) {
                if (!canWalk(forts, i, j, direction))
                    continue;
                double gain = forts[j].value - distanceOf(forts[i].pos, forts[j].pos);
                dp[j] = max(dp[j], dp[i] + gain);
            }
        }
        double answer = *max_element(dp.begin(), dp.end());
        cout << "Case #" << cs << ": ";
        cout << fixed << setprecision(4) << answer << '\n';
    }
    return 0;
}
