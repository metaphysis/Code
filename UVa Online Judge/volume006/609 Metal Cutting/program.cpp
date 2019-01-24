// Metal Cutting
// UVa ID: 609
// Verdict: Accepted
// Submission Date: 2019-01-24
// UVa Run Time: 0.800s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
};

typedef vector<point> polygon;

struct line
{
    int index;
    point p1, p2;
    double a, b, c;
    bool operator<(const line &u) const
    {
        return index < u.index;
    }
};

line getLine(int index, point p, point q)
{
    line u;
    u.index = index;
    u.a = q.y - p.y, u.b = p.x - q.x, u.c = p.y * (q.x - p.x) - p.x * (q.y - p.y);
    u.p1 = p, u.p2 = q;
    return u;
}

bool getIntersection(line p, line q, point &pi)
{
    if (fabs(p.a * q.b - q.a * p.b) < EPSILON) return false;  
    pi.x = (q.c * p.b - p.c * q.b) / (p.a * q.b - q.a * p.b);  
    pi.y = (q.c * p.a - p.c * q.a) / (p.b * q.a - q.b * p.a);  
    return true;
}

double getDist(point p1, point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

inline bool contains(point a, point b, point c, point d)
{
    int xup, xdown, yup, ydown;
    xup = xdown = yup = ydown = 0;
     
    double maxx = max(c.x, d.x), minx = min(c.x, d.x);
    if (a.x - maxx > -EPSILON || b.x - maxx > -EPSILON) xup = 1;
    if (a.x - minx < EPSILON || b.x - minx < EPSILON) xdown = 1;
 
    double maxy = max(c.y, d.y), miny = min(c.y, d.y);
    if (a.y - maxy > -EPSILON || b.y - maxy > -EPSILON) yup = 1;
    if (a.y - miny < EPSILON || b.y - miny < EPSILON) ydown = 1;
 
    return xup + xdown + yup + ydown == 4;
}

vector<line> sides, metal;
double cut(line u)
{
    point p;
    vector<point> ps;

    for (auto v : metal)
        if (getIntersection(u, v, p))
            ps.push_back(p);
            
    double cutted = 1e20;
    for (int i = 0; i < ps.size(); i++)
        for (int j = i + 1; j < ps.size(); j++)
            if (contains(ps[i], ps[j], u.p1, u.p2))
                cutted = min(cutted, getDist(ps[i], ps[j]));
            
    return cutted;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int p;
        double n, m, x, y;
        polygon pg;
        
        cin >> n >> m >> p;
        for (int i = 0; i < p; i++)
        {
            cin >> x >> y;
            pg.push_back(point(x, y));
        }

        sides.clear();
        for (int i = 0; i < p; i++)
            sides.push_back(getLine(i, pg[i], pg[(i + 1) % p]));
        sort(sides.begin(), sides.end());

        double minL = 1e20;
        do
        {
            metal.clear();
            metal.push_back(getLine(0, point(0, 0), point(0, m)));
            metal.push_back(getLine(1, point(0, m), point(n, m)));
            metal.push_back(getLine(2, point(n, m), point(n, 0)));
            metal.push_back(getLine(3, point(n, 0), point(0, 0)));

            double L = 0;
            for (int i = 0; i < p; i++)
            {
                L += cut(sides[i]);
                metal.push_back(sides[i]);
                if (L > minL) break;
            }
            minL = min(minL, L);
        } while (next_permutation(sides.begin(), sides.end()));

        if (cs > 1) cout << '\n';
        cout << "Minimum total length = " << fixed << setprecision(3) << minL << '\n';
    }

    return 0;
}
