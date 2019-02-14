// Tangents
// UVa ID: 10674
// Verdict: Accepted
// Submission Date: 2019-02-14
// UVa Run Time: 0.000s
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

struct circle { point c; double r; };
double atan2(point p) { return atan2(p.y, p.x); }
point polar(double d, double t) { return point(d * cos(t), d * sin(t)); }

bool equal(double x, double y)
{
    return fabs(x - y) <= EPSILON;
}

struct R
{
    point p1, p2;
    double L;
    R (point p1 = point(0, 0), point p2 = point(0, 0), double L = 0): p1(p1), p2(p2), L(L) {}
    bool operator<(const R &r) const
    {
        if (equal(p1.x, r.p1.x)) return p1.y < r.p1.y;
        return p1.x < r.p1.x;
    }
};

vector<R> Rs;

void print()
{
    sort(Rs.begin(), Rs.end());
    cout << Rs.size() << '\n';
    for (int i = 0; i < Rs.size(); i++)
    {
        cout << fixed << setprecision(5) << Rs[i].p1.x << ' ' << Rs[i].p1.y;
        cout << ' ' << Rs[i].p2.x << ' ' << Rs[i].p2.y << ' ' << Rs[i].L << '\n';
    }
}

double D;
circle cc1, cc2;

void addInscribe()
{
    point dc = cc2.c - cc1.c;
    double t = atan2(dc);
    point p1 = cc1.c + polar(cc1.r, t);
    Rs.push_back(R(p1, p1, 0));
}

void addIntersect()
{
    double L = sqrt(D * D - pow(cc1.r - cc2.r, 2));
    double A = acos((cc1.r * cc1.r + D * D - L * L - cc2.r * cc2.r) / (2 * cc1.r * D));
    point dc = cc2.c - cc1.c;
    double t = atan2(dc);
    point p1 = cc1.c + polar(cc1.r, t + A);
    point p2 = cc1.c + polar(cc1.r, t - A);

    A = acos((cc2.r * cc2.r + D * D - L * L - cc1.r * cc1.r) / (2 * cc2.r * D));
    dc = cc1.c - cc2.c;
    t = atan2(dc);
    point p3 = cc2.c + polar(cc2.r, t + A);
    point p4 = cc2.c + polar(cc2.r, t - A);

    Rs.push_back(R(p1, p4, L));
    Rs.push_back(R(p2, p3, L));
}

void addDisjoint()
{
    double L = sqrt(D * D - pow(cc1.r + cc2.r, 2));
    double A = asin(L / D);
    point dc = cc2.c - cc1.c;
    double t = atan2(dc);
    point p1 = cc1.c + polar(cc1.r, t + A);
    point p2 = cc1.c + polar(cc1.r, t - A);

    dc = cc1.c - cc2.c;
    t = atan2(dc);
    point p3 = cc2.c + polar(cc2.r, t + A);
    point p4 = cc2.c + polar(cc2.r, t - A);

    Rs.push_back(R(p1, p3, L));
    Rs.push_back(R(p2, p4, L));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> cc1.c.x >> cc1.c.y >> cc1.r >> cc2.c.x >> cc2.c.y >> cc2.r)
    {
        if (fabs(cc1.r) <= EPSILON) break;

        // Coincidence.
        if (equal(cc1.c.x, cc2.c.x) && equal(cc1.c.y, cc2.c.y) && equal(cc1.r, cc2.r))
        {
            cout << "-1\n";
            continue;
        }
        
        D = abs(cc1.c - cc2.c);

        // Inclusion.
        if (max(cc1.r, cc2.r) > D + min(cc1.r, cc2.r))
        {
            cout << "0\n";
            continue;
        }

        Rs.clear();

        // Inscribe.
        if (fabs(D - fabs(cc1.r - cc2.r)) <= EPSILON)
        {
            if (cc1.r < cc2.r) swap(cc1, cc2);
            addInscribe();
        }
        // Intersect.
        else if (D < cc1.r + cc2.r)
        {
            addIntersect();
        }
        // Circumscribe.
        else if (fabs(D - cc1.r - cc2.r) <= EPSILON)
        {
            addInscribe();
            addIntersect();
        }
        // Disjoint.
        else if (D > cc1.r + cc2.r)
        {
            addIntersect();
            addDisjoint();
        }
        print();
    }

    return 0;
}
