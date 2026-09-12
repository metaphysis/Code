// Air Traffic Control
// UVa ID: 1037
// Verdict: Accepted
// Submission Date: 2026-08-02
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-5;

struct Point {
    double x, y;
    Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }
};

double norm(Point a) { return hypot(a.x, a.y); }

bool cmp(const Point &a, const Point &b) { return a.y > b.y + EPS || (a.y > b.y - EPS && a.x > b.x); }

bool center(Point a, Point b, Point c, Point &o) {
    double a1 = b.x - a.x, b1 = b.y - a.y;
    double c1 = (a.x * a.x + a.y * a.y - b.x * b.x - b.y * b.y) / 2;
    double a2 = c.x - a.x, b2 = c.y - a.y;
    double c2 = (a.x * a.x + a.y * a.y - c.x * c.x - c.y * c.y) / 2;
    double d = b1 * a2 - b2 * a1;
    if (fabs(d) < EPS) return false;
    o.y = (c2 * a1 - c1 * a2) / d;
    o.x = (c1 * b2 - c2 * b1) / d;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int NP, NC, tc = 0;
    while (cin >> NP >> NC && NP) {
        vector<Point> p(NP);
        for (auto &x : p) cin >> x.x >> x.y;
        sort(p.begin(), p.end(), cmp);
        vector<int> total(NP);
        bool possible = true;
        for (int z = 0; z < NC; z++) {
            int m;
            Point a, b;
            cin >> m >> a.x >> a.y >> b.x >> b.y;
            double bestR = -1;
            vector<int> best(NP);
            for (int t = 0; t < NP; t++) {
                Point o;
                if (!center(a, b, p[t], o)) continue;
                double r = norm(a - o);
                int in = 0, on = 0;
                vector<int> inside(NP), boundary(NP);
                for (int i = 0; i < NP; i++) {
                    double d = norm(p[i] - o);
                    if (d < r - EPS) inside[i] = 1, in++;
                    else if (d < r + EPS) boundary[i] = 1, on++;
                }
                if (in > m || in + on < m) continue;
                vector<int> cur = inside;
                int need = m - in;
                for (int i = 0; i < NP && need; i++)
                    if (boundary[i]) cur[i] = 1, need--;
                bool better = false;
                if (bestR < 0 || r < bestR - EPS) better = true;
                else if (r < bestR + EPS) {
                    for (int i = 0; i < NP; i++) {
                        if (cur[i] != best[i]) {
                            better = cur[i];
                            break;
                        }
                    }
                }
                if (better) {
                    bestR = r;
                    best = cur;
                }
            }
            if (bestR < 0) possible = false;
            else {
                for (int i = 0; i < NP; i++) total[i] += best[i];
            }
        }
        // 注意输出格式：间隔两个空格
        cout << "Trial " << ++tc << ":";
        if (!possible) {
            cout << "  Impossible\n\n";
            continue;
        }
        vector<int> answer(NC + 1);
        for (int x : total) answer[x]++;
        for (int i = 0; i <= NC; i++) cout << "  " << answer[i];
        cout << "\n\n";
    }
    return 0;
}
