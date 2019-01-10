// Metal Cutting
// UVa ID: 609
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};

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

typedef vector<point> polygon;

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

bool getIntersection(line p, line q, point &pi)
{
    if (fabs(p.a * q.b - q.a * p.b) < EPSILON) return false;  
    pi.x = (q.c * p.b - p.c * q.b) / (p.a * q.b - q.a * p.b);  
    pi.y = (q.c * p.a - p.c * q.a) / (p.b * q.a - q.b * p.a);  
    return true;
}

bool pointInBox(point a, point b, point p)
{
    double minx = min(a.x, b.x), maxx = max(a.x, b.x);
    double miny = min(a.y, b.y), maxy = max(a.y, b.y);
    return p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy;
}

double getDist(point p1, point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

bool isFront(point p1, point p2, point p3)
{
    return dot(p2 - p1, p3 - p1) > 0;
}

double front[12], rear[12], middle[12];
void prepare(int idx, point p1, point p2, double n, double m)
{
    point ps[4] = {point(0, 0), point(0, n), point(n, m), point(n, 0)};
    line u = getLine(p1, p2);
    for (int i = 0; i < 4; i++)
    {
        line v = getLine(ps[i], ps[(i + 1) % 4]);
        point pi;
        if (getIntersection(u, v, pi))
            if (pointInBox(ps[i], ps[(i + 1) % 4], pi))
            {
                if (isFront(p1, p2, pi))
                    front[idx] = getDist(p2, pi);
                else
                    rear[idx] = getDist(pi, p1);
            } 
    }
    middle[idx] = getDist(p1, p2);
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
        
        for (int i = 0; i < p; i++)
        {
            prepare(i, pg[i], pg[(i + 1) % p], n, m);
        }

        int bit[p] = {}, vertexCutted[p] = {};
        for (int i = 0; i < p; i++) bit[i] = i;
        
        double minL = 1e20;
        do
        {
            memset(vertexCutted, 0, sizeof(vertexCutted));
            double L = 0;
            for (int i = 0; i < p; i++)
            {
                int side = bit[i];
                L += middle[side];
                if (!vertexCutted[(side + 1) % p])
                {
                    L += front[side];
                    vertexCutted[(side + 1) % p] = 1;
                }
                if (!vertexCutted[side])
                {
                    L += rear[side];
                    vertexCutted[side] = 1;
                }
            }
            minL = min(minL, L);
        } while (next_permutation(bit, bit + p));

        if (cs > 1) cout << '\n';
        cout << "Minimum total length = " << fixed << setprecision(3) << minL << '\n';
    }

    return 0;
}
