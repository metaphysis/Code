// Avoiding Overlaps
// UVa ID: 11601
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
};

double cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool pointInBox(point a, point b, point p)
{
    return (p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x)) &&
        (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y));
}

struct segment
{
    point p1, p2;
    segment (point p1 = point(0, 0), point p2 = point(0, 0)): p1(p1), p2(p2) {}
    bool contains(const point &p) { return pointInBox(p1, p2, p); }
};

bool isIntersected(segment &s1, segment &s2)
{
    double cp1 = cp(s1.p1, s1.p2, s2.p1), cp2 = cp(s1.p1, s1.p2, s2.p2);
    double cp3 = cp(s2.p1, s2.p2, s1.p1), cp4 = cp(s2.p1, s2.p2, s1.p2);

    if ((cp1 * cp2 < 0) && (cp3 * cp4) < 0) return true;
    if (fabs(cp1) <= EPSILON && s1.contains(s2.p1)) return true;
    if (fabs(cp2) <= EPSILON && s1.contains(s2.p2)) return true;
    if (fabs(cp3) <= EPSILON && s2.contains(s1.p1)) return true;
    if (fabs(cp4) <= EPSILON && s2.contains(s1.p2)) return true;

    return false;
}

struct rectangle
{
    int idx, lowx, lowy, upx, upy;
    bool operator<(const rectangle &r) const
    {
        if (lowx != r.lowx) return lowx < r.lowx;
        if (lowy != r.lowy) return lowy < r.lowy;
        if (upx != r.upx) return upx < r.upx;
        if (upy != r.upy) return upy < r.upy;
        return idx < r.idx;
    }
} rs[10010];

bool isOverlapped(rectangle &r1, rectangle &r2)
{
    segment s1(point(r1.lowx, r1.lowy), point(r1.upx, r1.upy));
    segment s2(point(r1.lowx, r1.upy), point(r1.upx, r1.lowy));
    segment s3(point(r1.lowx, r1.lowy), point(r1.upx, r1.lowy));
    segment s4(point(r1.upx, r1.lowy), point(r1.upx, r1.upy));
    segment s5(point(r1.upx, r1.upy), point(r1.lowx, r1.upy));
    segment s6(point(r1.lowx, r1.upy), point(r1.lowx, r1.lowy));
    if (isIntersected(s1, s3)) return true;
    if (isIntersected(s1, s4)) return true;
    if (isIntersected(s1, s5)) return true;
    if (isIntersected(s1, s6)) return true;
    if (isIntersected(s2, s3)) return true;
    if (isIntersected(s2, s4)) return true;
    if (isIntersected(s2, s5)) return true;
    if (isIntersected(s2, s6)) return true;
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, N;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            cin >> rs[i].lowx >> rs[i].lowy;
            cin >> rs[i].upx >> rs[i].upy;
            rs[i].idx = i;
        }
        stable_sort(rs, rs + N);
        vector<rectangle> drawed;
        for (int i = 0; i < N; i++)
        {
            if (drawed.size() > 0)
            {
                if (isOverlapped(drawed.back(), rs[i]))
                {
                    if (rs[i].idx > drawed.back().idx) continue;
                    else
                    {
                        while (drawed.size() > 0 && isOverlapped(drawed.back(), rs[i]))
                        {
                            if (rs[i].idx > drawed.back().idx) break;
                            drawed.pop_back();
                        }
                    }
                }
                else drawed.push_back(rs[i]);
            }
            else drawed.push_back(rs[i]);
        }
        int total = 0;
        for (auto r : rs) total += abs(r.lowx - r.upx) * abs(r.lowy - r.upy);
        cout << "Case " << cs << ": " << total << '\n';
    }

    return 0;
}
