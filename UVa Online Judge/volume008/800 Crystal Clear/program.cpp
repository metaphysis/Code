// Crystal Clear
// UVa ID: 800
// Verdict: Accepted
// Submission Date: 2018-12-28
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int OUT = 0, ON = 1, IN = 2;
const double EPSILON = 1e-7;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};

struct segment
{
    point p1, p2;
    segment (point p1 = point(0, 0), point p2 = point(0, 0)): p1(p1), p2(p2) {}
};

typedef vector<point> polygon;

double norm(point a)
{
	return a.x * a.x + a.y * a.y;
}

double abs(point a)
{
    return sqrt(norm(a));
}

double dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

double cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

double cp(point a, point b, point c)
{
	return cross(b - a, c - a);
}

int isPointInPolygon(point p, polygon &pg)
{
    bool in = false;
    for (int i = 0; i < pg.size(); i++)
    {
        point a = pg[i] - p, b = pg[(i + 1) % pg.size()] - p;
        if (abs(cross(a, b)) < EPSILON && dot(a, b) < EPSILON) return ON;
        if (a.y > b.y) swap(a, b);
        if (a.y < EPSILON && EPSILON < b.y && cross(a, b) > EPSILON) in = !in;
    }
    return in ? IN : OUT;
}

double getDistPL(point p, point p1, point p2)
{
	return fabs(cross(p2 - p1, p - p1) / abs(p2 - p1));
}

double getDistPS(point p, segment s)
{
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return abs(p - s.p1);
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return abs(p - s.p2);
    return getDistPL(p, s.p1, s.p2);
}

bool isDistSatisfied(point p, polygon &pg)
{
    for (int i = 0; i < pg.size(); i++)
        if (getDistPS(p, segment(pg[i], pg[(i + 1) % pg.size()])) < 0.5) return false;
    return true;
}

const double PI = 2 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    int xs[32], ys[32];
    while (cin >> n, n > 0)
    {
        polygon pg;
        int lowx = 500, lowy = 500, highx = -500, highy = -500;
        for (int i = 0; i < n; i++)
        {
            cin >> xs[i] >> ys[i];
            lowx = min(lowx, xs[i]), lowy = min(lowy, ys[i]);
            highx = max(highx, xs[i]), highy = max(highy, ys[i]);
            pg.push_back(point(xs[i], ys[i]));
        }
        
        int v = n - 2;
        for (int i = 0; i < n; i++)
        {
            int k = __gcd(abs(xs[i] - xs[(i + 1) % n]), abs(ys[i] - ys[(i + 1) % n]));
            if (k == 1) continue;
            int dx = (xs[(i + 1) % n] - xs[i]) / k, dy = (ys[(i + 1) % n] - ys[i]) / k;
            int nextx = xs[i], nexty = ys[i];
            point s(xs[i], ys[i]), e(xs[(i + 1) % n], ys[(i + 1) % n]);
            point back(xs[(i - 1 + n) % n], ys[(i - 1 + n) % n]), front(xs[(i + 2) % n], ys[(i + 2) % n]);
            for (int j = 1; j < k; j++)
            {
                nextx += dx, nexty += dy;
                if (cp(s, e, back) < 0) 
                    if (getDistPS(point(nextx, nexty), segment(s, back)) < 0.5) continue;
                if (cp(s, e, front) < 0)
                    if (getDistPS(point(nextx, nexty), segment(e, front)) < 0.5) continue;
                v += 1;
            }
        }
        for (int i = lowx; i <= highx; i++)
            for (int j = lowy; j <= highy; j++)
                if (isPointInPolygon(point(i, j), pg) == IN && isDistSatisfied(point(i, j), pg))
                    v += 2;
        double area = v * PI / 8;
        cout << "Shape " << ++cases << '\n';
        cout << "Insulating area = " << fixed << setprecision(3) << area << " cm^2" << '\n';
    }

    return 0;
}
