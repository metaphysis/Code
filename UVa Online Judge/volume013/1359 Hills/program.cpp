#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

struct Segment {
    Point a, b;
};

struct Line {
    long long a, b, c;
};

__int128 cross(Point a, Point b, Point c) {
    return (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
}

long long directionCross(const Segment &s1, const Segment &s2) {
    return (s1.b.x - s1.a.x) * (s2.b.y - s2.a.y) - (s1.b.y - s1.a.y) * (s2.b.x - s2.a.x);
}

bool isIntersect(const Segment &s1, const Segment &s2) {
    __int128 direction = cross(s1.a, s1.b, s2.a);
    __int128 reverseDirection = cross(s1.a, s1.b, s2.b);
    __int128 otherDirection = cross(s2.a, s2.b, s1.a);
    __int128 otherReverseDirection = cross(s2.a, s2.b, s1.b);
    if (directionCross(s1, s2) == 0) return false;
    bool first = (direction <= 0 && reverseDirection >= 0) || (direction >= 0 && reverseDirection <= 0);
    bool second = (otherDirection <= 0 && otherReverseDirection >= 0) || (otherDirection >= 0 && otherReverseDirection <= 0);
    return first && second;
}

long double getParameter(const Segment &s1, const Segment &s2) {
    long double dx1 = s1.b.x - s1.a.x, dy1 = s1.b.y - s1.a.y;
    long double dx2 = s2.b.x - s2.a.x, dy2 = s2.b.y - s2.a.y;
    long double dx = s2.a.x - s1.a.x, dy = s2.a.y - s1.a.y;
    long double denominator = dx1 * dy2 - dy1 * dx2;
    return (dx * dy2 - dy * dx2) / denominator;
}

Line getLine(const Segment &s) {
    Line line;
    line.a = s.a.y - s.b.y;
    line.b = s.b.x - s.a.x;
    line.c = s.a.x * s.b.y - s.b.x * s.a.y;
    return line;
}

bool isTriangle(const Line &l1, const Line &l2, const Line &l3) {
    __int128 value = (__int128)l1.a * (l2.b * l3.c - l2.c * l3.b)
                   - (__int128)l1.b * (l2.a * l3.c - l2.c * l3.a)
                   + (__int128)l1.c * (l2.a * l3.b - l2.b * l3.a);
    return value != 0;
}

bool hasBetween(const vector<long double> &values, long double left, long double right) {
    const long double eps = 1e-12L;
    if (left > right) swap(left, right);
    for (long double value : values)
        if (value > left + eps && value < right - eps) return true;
    return false;
}

int solve() {
    int n;
    cin >> n;
    vector<Segment> segments(n);
    for (int i = 0; i < n; i++)
        cin >> segments[i].a.x >> segments[i].a.y >> segments[i].b.x >> segments[i].b.y;
    vector<Line> lines(n);
    for (int i = 0; i < n; i++)
        lines[i] = getLine(segments[i]);
    vector<vector<bool>> connected(n, vector<bool>(n, false));
    vector<vector<long double>> parameters(n, vector<long double>(n, 0));
    vector<vector<long double>> orders(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!isIntersect(segments[i], segments[j])) continue;
            parameters[i][j] = getParameter(segments[i], segments[j]);
            parameters[j][i] = getParameter(segments[j], segments[i]);
            orders[i].push_back(parameters[i][j]);
            orders[j].push_back(parameters[j][i]);
            connected[i][j] = connected[j][i] = true;
        }
    }
    for (int i = 0; i < n; i++)
        sort(orders[i].begin(), orders[i].end());
    int answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!connected[i][j]) continue;
            for (int k = j + 1; k < n; k++) {
                if (!connected[i][k] || !connected[j][k]) continue;
                if (!isTriangle(lines[i], lines[j], lines[k])) continue;
                if (hasBetween(orders[i], parameters[i][j], parameters[i][k])) continue;
                if (hasBetween(orders[j], parameters[j][i], parameters[j][k])) continue;
                if (hasBetween(orders[k], parameters[k][i], parameters[k][j])) continue;
                answer++;
            }
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        if (caseId > 1) cout << '\n';
        cout << "Case " << caseId << ":\n";
        cout << solve() << '\n';
    }
    return 0;
}
