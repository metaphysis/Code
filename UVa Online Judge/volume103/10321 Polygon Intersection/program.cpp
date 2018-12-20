// Polygon Intersection
// UVa ID: 10321
// Verdict: Accepted
// Submission Date: 2018-12-20
// UVa Run Time: 0.000s
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
    bool operator<(const point &p) const
    {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator==(const point &p) const
    {
        return fabs(x - p.x) < EPSILON && fabs(y - p.y) < EPSILON;
    }
};

typedef vector<point> polygon;

bool pointInBox(point a, point b, point p)
{
    double minx = min(a.x, b.x), maxx = max(a.x, b.x);
    double miny = min(a.y, b.y), maxy = max(a.y, b.y);
    return p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy;
}

struct segment
{
    point p1, p2;
    segment (point p1 = point(0, 0), point p2 = point(0, 0)): p1(p1), p2(p2) {}
    bool contains(const point &p) { return pointInBox(p1, p2, p); }
};

struct line
{
    double a, b, c;
    line (double a = 0, double b = 0, double c = 0): a(a), b(b), c(c) {}
};

line getLine(double x1, double y1, double x2, double y2)
{
    return line(y2 - y1, x1 - x2, y1 * (x2 - x1) - x1 * (y2 - y1));
}

line getLine(point p, point q)
{
    return getLine(p.x, p.y, q.x, q.y);
}

point getIntersection(line p, line q)
{
    point pi;
    pi.x = (p.b * q.c - p.c * q.b) / (p.a * q.b - p.b * q.a);  
    pi.y = (p.a * q.c - p.c * q.a) / (p.b * q.a - p.a * q.b);
    return pi; 
}

double cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool isIntersected(segment s1, segment s2, point &pi)
{
    line p = getLine(s1.p1, s1.p2), q = getLine(s2.p1, s2.p2);

    if (fabs(p.a * q.b - q.a * p.b) < EPSILON)
    {
        if (fabs(cp(s1.p1, s1.p2, s2.p1)) < EPSILON)
            return s1.contains(s2.p1) || s1.contains(s2.p2);
        return false;
    }

	pi = getIntersection(p, q);
	return s1.contains(pi) && s2.contains(pi);
}

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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        if (n < 3) break;
        point p;
        polygon A, B;
        for (int i = 0; i < n; i++)
        {
            cin >> p.x >> p.y;
            A.push_back(p);
        }
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> p.x >> p.y;
            B.push_back(p);
        }
        
        vector<point> C;
        for (int i = 0; i < A.size(); i++)
            for (int j = 0; j < B.size(); j++)
            {
                segment s1(A[i], A[(i + 1) % A.size()]), s2(B[j], B[(j + 1) % B.size()]);
                point pi;
                if (isIntersected(s1, s2, pi)) C.push_back(pi);
            }
        for (int i = 0; i < A.size(); i++)
            if (isPointInPolygon(A[i], B))
                C.push_back(A[i]);
        for (int i = 0; i < B.size(); i++)
            if (isPointInPolygon(B[i], A))
                C.push_back(B[i]);
        sort(C.begin(), C.end());
        C.erase(unique(C.begin(), C.end()), C.end());
        cout << C.size() << '\n';
        for (auto p : C) cout << fixed << setprecision(2) << p.x << ' ' << p.y << '\n';
    }

    return 0;
}
