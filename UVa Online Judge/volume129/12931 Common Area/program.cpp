// Common Area
// UVa ID: 12931
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;
const int OUT = 0, ON = 1, IN = 2;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
    bool operator==(const point &p) { return x == p.x && y == p.y; }
};

double dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

double cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

typedef vector<point> polygon;

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

int n1, n2;
polygon pg1, pg2;

// 判断两个多边形是否重合。
bool isSame()
{
    if (n1 != n2) return false;
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
        {
            bool same = true;
            for (int k = 0; k < n1; k++)
            {
                if (pg1[(i + k) % n1] == pg2[(j + k) % n2]) continue;
                same = false;
                break;
            }
            if (same) return true;
        }
    return false;    
}

double cp(point a, point b, point c)
{
	return cross(b - a, c - a);
}

// 判断两条线段是否跨越式相交。
bool isIntersected()
{
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
        {
            double cp1 = cp(pg1[i], pg1[(i + 1) % n1], pg2[j]), cp2 = cp(pg1[i], pg1[(i + 1) % n1], pg2[(j + 1) % n2]);
            double cp3 = cp(pg2[j], pg2[(j + 1) % n2], pg1[i]), cp4 = cp(pg2[j], pg2[(j + 1) % n2], pg1[(i + 1) % n1]);
            if ((cp1 * cp2 < 0) && (cp3 * cp4) < 0) return true;
        }
    return false;
}

// 判断某个多边形边的中点是否在另外一个多边形内。
bool isMidpointIn()
{
    for (int i = 0; i < n1; i++)
    {
        point mp = (pg1[i] + pg1[(i + 1) % n1]) / 2.0;
        if (isPointInPolygon(mp, pg2) == IN)
            return true;
    }
    for (int i = 0; i < n2; i++)
    {
        point mp = (pg2[i] + pg2[(i + 1) % n2]) / 2.0;
        if (isPointInPolygon(mp, pg1) == IN)
            return true;
    }
    return false;
}

int main(int argc, char *argv[])
{    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n1)
    {
        pg1.clear();
        pg2.clear();
        for (int i = 0, x, y; i < n1; i++)
        {
            cin >> x >> y;
            pg1.push_back(point(x, y));
        }
        cin >> n2;
        for (int i = 0, x, y; i < n2; i++)
        {
            cin >> x >> y;
            pg2.push_back(point(x, y));
        }
        bool overlapped = isSame() || isIntersected() || isMidpointIn() ;
        cout << "Case " << ++cases << ": " << (overlapped ? "Yes" : "No") << '\n';
    }

    return 0;
}
