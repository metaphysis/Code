// Viva Confetti
// UVa ID: 1308
// Verdict: Accepted
// Submission Date: 2026-06-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-14;

int dcmp(double x) { return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
    double len() const { return sqrt(x * x + y * y); }
};

struct Circle {
    Point o;
    double r;
    Point point(double a) const { return Point(o.x + cos(a) * r, o.y + sin(a) * r); }
};

double norm(double a) {
    while (dcmp(a) < 0) a += 2 * PI;
    while (dcmp(a - 2 * PI) >= 0) a -= 2 * PI;
    return a;
}

vector<double> getAngles(const Circle& c1, const Circle& c2) {
    vector<double> r;
    double d = (c1.o - c2.o).len();
    if (dcmp(d) == 0 || dcmp(d - (c1.r + c2.r)) > 0 || dcmp(d - fabs(c1.r - c2.r)) < 0) return r;
    double a = atan2(c2.o.y - c1.o.y, c2.o.x - c1.o.x);
    double b = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    r.push_back(norm(a + b));
    r.push_back(norm(a - b));
    return r;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        vector<Circle> c(n + 1);
        for (int i = 1; i <= n; i++) scanf("%lf%lf%lf", &c[i].o.x, &c[i].o.y, &c[i].r);
        
        vector<vector<double>> rad(n + 1);
        for (int i = 1; i <= n; i++) {
            rad[i].push_back(0);
            for (int j = 1; j <= n; j++) if (i != j) {
                auto t = getAngles(c[i], c[j]);
                rad[i].insert(rad[i].end(), t.begin(), t.end());
            }
            sort(rad[i].begin(), rad[i].end());
            rad[i].erase(unique(rad[i].begin(), rad[i].end(), 
                [](double a, double b) { return dcmp(a - b) == 0; }), rad[i].end());
            if (rad[i].size() == 1) rad[i].push_back(2 * PI);
        }
        
        vector<bool> vis(n + 1, false);
        for (int i = 1; i <= n; i++) {
            int m = rad[i].size();
            for (int j = 0; j < m; j++) {
                double mid = (j ? rad[i][j] + rad[i][j-1] : rad[i][0] + rad[i][m-1] + 2 * PI) / 2;
                mid = norm(mid);
                Point p = c[i].point(mid);
                
                bool covered = false;
                for (int k = i + 1; k <= n; k++)
                    if (dcmp((p - c[k].o).len() - c[k].r) <= 0) { covered = true; break; }
                
                if (!covered) {
                    vis[i] = true;
                    for (int k = i - 1; k >= 1; k--)
                        if (dcmp((p - c[k].o).len() - c[k].r) <= 0) { vis[k] = true; break; }
                }
            }
        }
        
        printf("%d\n", count(vis.begin() + 1, vis.end(), true));
    }
    return 0;
}
