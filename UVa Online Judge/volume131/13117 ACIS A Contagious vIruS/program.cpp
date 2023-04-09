// ACIS A Contagious vIruS
// UVa ID: 13117
// Verdict: Accetped
// Submission Date: 2023-04-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};
struct segment { point p1, p2; };
typedef segment line;

double norm(point a) { return a.x * a.x + a.y * a.y; }
double abs(point a) { return sqrt(norm(a)); }
double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double cross(point a, point b) { return a.x * b.y - a.y * b.x; }
double getDistPL(point p, line l) {
    return fabs(cross(l.p2 - l.p1, p - l.p1) / abs(l.p2 - l.p1));
}
double getDistPS(point p, segment s) {
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return abs(p - s.p1);
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return abs(p - s.p2);
    return getDistPL(p, s);
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string s;
    while (getline(cin, s)) {
        if (s.front() == '*') break;
        int n = stoi(s);
        point redis, ps[20];
        cin >> redis.x >> redis.y;
        for (int i = 0; i < n; i++) cin >> ps[i].x >> ps[i].y;
        double r = 100000;
        for (int i = 0; i < n; i++)
            r = min(r, getDistPS(redis, line{ps[i], ps[(i + 1) % n]}));
        cout << fixed << setprecision(3) << r << '\n';
        cin.ignore(256, '\n');
    }
    return 0;
}
