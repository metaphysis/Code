// Smallest Enclosing Rectangle
// UVa ID: 12307
// Verdict: Accepted
// Submission Date: 2018-05-09
// UVa Run Time: 0.400s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-9;

struct point
{
    double x, y;
    point(double x = 0, double y = 0): x(x), y(y) {}
    point operator+(point i) { return point(x + i.x, y + i.y); };
    point operator-(point i) { return point(x - i.x, y - i.y); };
    point operator*(double k) { return point(x * k, y * k); };
    point operator/(double k) { return point(x / k, y / k); };
    bool operator<(const point &p) const
	{
	    if (fabs(y - p.y) > EPSILON) return y < p.y;
	    return x < p.x;
	}
	bool operator==(const point &p) const
	{
	    return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
	}
    double distTo(point i) { return sqrt(pow(x - i.x, 2) + pow(y - i.y, 2)); }
} pr;

typedef vector<point> polygon;

double cross(point a, point b) { return a.x * b.y - a.y * b.x; }
double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double norm(point a) { return dot(a, a); }
double abs(point a) { return sqrt(norm(a)); }
double cp(point a, point b, point c) { return cross(b - a, c - a);}

pair<double, double> rotatingCalipers(polygon pg)
{
    double minArea = 1e20, minLength = 1e20;
    pg.push_back(pg.front());
    for (int i = 0, j = 1, k, m, n = pg.size() - 1; i < n; i++)
    {
        while (dot(pg[i + 1] - pg[i], pg[j + 1] - pg[j]) > EPSILON)
            j = (j + 1) % n;
        if (!i) k = j;
        while (cross(pg[i + 1] - pg[i], pg[k + 1] - pg[k]) > EPSILON)
            k = (k + 1) % n;
        if (!i)  m = k;
        while (dot(pg[i + 1] - pg[i], pg[m + 1] - pg[m]) < -EPSILON)
            m = (m + 1) % n;
        double d = abs(pg[i + 1] - pg[i]);
        double height = fabs(cp(pg[i], pg[i + 1], pg[k])) / d;
        double width = dot(pg[i + 1] - pg[i], pg[j] - pg[m]) / d;
        minArea = min(minArea, width * height);
        minLength = min(minLength, (width + height) * 2);
    }
    return make_pair(minArea, minLength);
}

bool cw(point a, point b, point c) { return cp(a, b, c) < -EPSILON; }
bool ccw(point a, point b, point c) { return cp(a, b, c) > EPSILON; }
bool collinear(point a, point b, point c) { return fabs(cp(a, b, c)) <= EPSILON; }
bool cmpAngle(point &a, point &b)
{
    if (collinear(pr, a, b)) return pr.distTo(a) <= pr.distTo(b);
    return ccw(pr, a, b);
}

polygon grahamConvexHull(polygon &pg)
{
    polygon ch(pg);

	sort(ch.begin(), ch.end());
    ch.erase(unique(ch.begin(), ch.end()), ch.end());
    if (ch.size() < 3) return ch;

    pr = ch.front();
    sort(ch.begin() + 1, ch.end(), cmpAngle);
	ch.push_back(pr);

	int top = 2, next = 2, total = ch.size() - 1;
	while (next <= total)
	{
	    if (cw(ch[top - 2], ch[top - 1], ch[next])) top--;
	    else 
	    {
	        if (collinear(ch[top - 2], ch[top - 1], ch[next]))
	            ch[top - 1] = ch[next++];
	        else
	            ch[top++] = ch[next++];
        }
	}
	top--;
	ch.erase(ch.begin() + top, ch.end());

	return ch;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        polygon pg;
        double x, y;
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            pg.push_back(point(x, y));
        }
        polygon hull = grahamConvexHull(pg);
        pair<double, double> j = rotatingCalipers(hull);
        cout << fixed << setprecision(2) << j.first << ' ';
        cout << fixed << setprecision(2) << j.second << '\n';
    }

    return 0;
}
