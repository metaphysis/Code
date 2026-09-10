#include <bits/stdc++.h>
using namespace std;

struct Point { double x, y; };

double dist(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

double dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

Point sub(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}

// 点 p 到线段 ab 的最短距离
double pointToSegment(const Point& p, const Point& a, const Point& b) {
    Point v = sub(b, a), w = sub(p, a);
    double t = dot(w, v) / dot(v, v); // 投影比例
    if (t < 0) return dist(p, a);
    if (t > 1) return dist(p, b);
    Point proj = {a.x + t * v.x, a.y + t * v.y};
    return dist(p, proj);
}

// 两条线段 ab 和 cd 之间的最短距离
double segmentDistance(const Point& a, const Point& b, const Point& c, const Point& d) {
    double ans = min({
        pointToSegment(a, c, d),
        pointToSegment(b, c, d),
        pointToSegment(c, a, b),
        pointToSegment(d, a, b)
    });
    return ans;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int ni;
        cin >> ni;
        vector<Point> inner(ni);
        for (int i = 0; i < ni; ++i) cin >> inner[i].x >> inner[i].y;
        int no;
        cin >> no;
        vector<Point> outer(no);
        for (int i = 0; i < no; ++i) cin >> outer[i].x >> outer[i].y;

        double minDist = 1e100;
        for (int i = 0; i < ni; ++i) {
            int iNext = (i + 1) % ni;
            for (int j = 0; j < no; ++j) {
                int jNext = (j + 1) % no;
                double d = segmentDistance(inner[i], inner[iNext], outer[j], outer[jNext]);
                if (d < minDist) minDist = d;
            }
        }

        cout << fixed << setprecision(10) << minDist / 2.0 << "\n";
    }
    return 0;
}
