// Islands
// UVa ID: 889
// Verdict: Accepted
// Submission Date: 2018-12-28
// UVa Run Time: 0.130s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

struct segment {
    point p1, p2;
    segment (point p1 = point(0, 0), point p2 = point(0, 0)): p1(p1), p2(p2) {}
};

typedef segment line;
typedef vector<point> polygon;

double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double cross(point a, point b) { return a.x * b.y - b.x * a.y; }
double norm(point p) { return p.x * p.x + p.y * p.y; };
double abs(point p) { return sqrt(norm(p)); };

double getDistPL(point p, line l)
{
    return fabs(cross(l.p2 - l.p1, p - l.p1) / abs(l.p2 - l.p1));
}

double getDistPS(point p, segment s)
{
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return abs(p - s.p1);
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return abs(p - s.p2);
    return getDistPL(p, s);
}

double getDistSS(segment s1, segment s2)
{
	return min(min(getDistPS(s2.p1, s1), getDistPS(s2.p2, s1)),
	    min(getDistPS(s1.p1, s2), getDistPS(s1.p2, s2)));
}

const int MAXV = 110;

struct edge
{
    int u, v;
    double w;
    edge (int u = 0, int v = 0, double w = 0): u(u), v(v), w(w) {}
    bool operator<(const edge &e) const
    {
        return w < e.w;
    }
} edges[10240];

int parent[MAXV], ranks[MAXV], n, m;

void makeSet()
{
    for (int i = 0; i < n; i++) parent[i] = i, ranks[i] = 0;
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

bool unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
        return true;
    }
    return false;
}

double kruskal()
{
    double sum = 0;

    makeSet();
    sort(edges, edges + m);

    for (int i = 0; i < m; i++)
        if (unionSet(edges[i].u, edges[i].v))
            sum += edges[i].w;
    return sum;
}

double getDist(polygon &pg1, polygon &pg2)
{
    double d = 1e20;
    for (int i = 0; i < pg1.size(); i++)
        for (int j = 0; j < pg2.size(); j++)
            d = min(d, getDistSS(segment(pg1[i], pg1[(i + 1) % pg1.size()]), segment(pg2[j], pg2[(j + 1) % pg2.size()])));
    return d;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        vector<polygon> pgs(n);
        for (int i = 0; i < n; i++)
        {
            int v;
            cin >> v;
            double x, y;
            for (int j = 0; j < v; j++)
            {
                cin >> x >> y;
                pgs[i].push_back(point(x, y));
            }
        }
        
        m = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                edges[m++] = edge(i, j, getDist(pgs[i], pgs[j]));
                
        cout << "The minimal interconnect consists of " << n - 1;
        cout << " bridges with a total length of ";
        cout << fixed << setprecision(3) << kruskal() << '\n';
        
    }

    return 0;
}
