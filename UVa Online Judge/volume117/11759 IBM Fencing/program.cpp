// IBM Fencing
// UVa ID: 11759
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.600s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
};

double cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dist(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

double computePerimeter(const vector<Point>& pts) {
    double res = 0.0;
    int n = pts.size();
    for (int i = 0; i < n; ++i)
        res += dist(pts[i], pts[(i + 1) % n]);
    return res;
}

double computeSignedArea(const vector<Point>& pts) {
    double res = 0.0;
    int n = pts.size();
    for (int i = 0; i < n; ++i)
        res += pts[i].x * pts[(i + 1) % n].y - pts[i].y * pts[(i + 1) % n].x;
    return res * 0.5;
}

bool pointInConvexPolygon(const Point& p, const struct Polygon& poly);

struct Polygon {
    vector<Point> pts;
    double perimeter;
    double signedArea;
    double absArea;
    int depth;
};

bool pointInConvexPolygon(const Point& p, const Polygon& poly) {
    const vector<Point>& pts = poly.pts;
    int n = pts.size();
    if (n == 0) return false;
    double sign = (poly.signedArea > 0) ? 1.0 : -1.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        double cr = cross(pts[i], pts[j], p);
        if (sign * cr < -EPS) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(8);

    int N, caseNo = 1;
    while (cin >> N && N) {
        vector<Polygon> polys(N);
        for (int i = 0; i < N; ++i) {
            int M;
            cin >> M;
            polys[i].pts.resize(M);
            for (int j = 0; j < M; ++j)
                cin >> polys[i].pts[j].x >> polys[i].pts[j].y;
            polys[i].perimeter = computePerimeter(polys[i].pts);
            polys[i].signedArea = computeSignedArea(polys[i].pts);
            polys[i].absArea = fabs(polys[i].signedArea);
            polys[i].depth = 0;
        }

        // 按面积降序排序索引
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return polys[a].absArea > polys[b].absArea;
        });

        // 计算深度
        for (int i : idx) {
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                if (polys[j].absArea < polys[i].absArea - EPS) {
                    if (pointInConvexPolygon(polys[j].pts[0], polys[i])) {
                        polys[j].depth = max(polys[j].depth, polys[i].depth + 1);
                    }
                }
            }
        }

        int communities = 0;
        double steelLen = 0.0, woodLen = 0.0;
        for (int i = 0; i < N; ++i) {
            if (polys[i].depth == 0) ++communities;
            if (polys[i].depth % 2 == 0) steelLen += polys[i].perimeter;
            else woodLen += polys[i].perimeter;
        }

        double steelCost = steelLen * 100.0 / 1e6;
        double woodCost = woodLen * 50.0 / 1e6;

        cout << "Case " << caseNo << ":" << '\n';
        cout << "Total Number of Communities " << communities << '\n';
        cout << "Total Cost:" << '\n';
        cout << "Steel Fence: " << steelCost << " Million Yuan" << '\n';
        cout << "Wooden Fence: " << woodCost << " Million Yuan" << '\n';
        cout << '\n';

        ++caseNo;
    }

    return 0;
}
