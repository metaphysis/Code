// Return of the Jedi
// UVa ID: 10224
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

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

double getDistPL(point p, point p1, point p2)
{
	return fabs(cross(p2 - p1, p - p1) / abs(p2 - p1));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int T;
    double xluke, yluke, xewok, yewok;
    double xtree, ytree, dtree;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> T >> xluke >> yluke >> xewok >> yewok;
        point luke(xluke, yluke), ewok(xewok, yewok);
        double D = abs(ewok - luke);
        for (int i = 0; i < T; i++)
        {
            cin >> xtree >> ytree >> dtree;
            dtree /= 2.0;
            point C(xtree, ytree);
            double d = getDistPL(C, luke, ewok);
            cout << "dtree = " << dtree << " d = " << d << '\n';
            if (d < dtree)
            {
                double alpha = acos(d / dtree);
                D += dtree * 2.0 * alpha;
                D -= 2.0 * sqrt(dtree * dtree - d * d);
            }
        }
        if (cs > 1) cout << '\n';
        cout << fixed << setprecision(2) << D * 18.0 << '\n';
    }

    return 0;
}
