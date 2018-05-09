// Squares
// UVa ID: 1453
// Verdict: Accepted
// Submission Date: 2018-05-08
// UVa Run Time: 0.220s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
	int x, y;
    point(int x = 0, int y = 0): x(x), y(y) {}
    point operator+(point i) { return point(x + i.x, y + i.y); };
    point operator-(point i) { return point(x - i.x, y - i.y); };
    point operator*(double k) { return point(x * k, y * k); };
    point operator/(double k) { return point(x / k, y / k); };
	bool operator<(const point &p) const
	{
	    if (y != p.y) return y < p.y;
	    return x < p.x;
	}
	bool operator==(const point &p) const { return x == p.x && y == p.y; }
	int distTo(const point &p) { return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y); }
} pr;

typedef vector<point> polygon;

int cross(point a, point b) { return a.x * b.y - a.y * b.x; }
int dot(point a, point b) { return a.x * b.x + a.y * b.y; }
int cp(point a, point b, point c) {	return cross(b - a, c - a); }
bool cw(point a, point b, point c) { return cp(a, b, c) < 0; }
bool ccw(point a, point b, point c) { return cp(a, b, c) > 0; }
bool collinear(point a, point b, point c) { return abs(cp(a, b, c)) == 0; }
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

int rotatingCalipers(polygon pg)
{
    int dist = 0;
    pg.push_back(pg.front());
    for (int i = 0, j = 1, n = pg.size() - 1; i < n; i++)
    {
        while (cross(pg[i + 1] - pg[i], pg[j + 1] - pg[j]) > 0)
            j = (j + 1) % n;
        dist = max(dist, max(pg[i].distTo(pg[j]), pg[i + 1].distTo(pg[j + 1])));
    }
    return dist;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, x, y, width;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        polygon pg;
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y >> width;
            pg.push_back(point(x, y));
            pg.push_back(point(x + width, y));
            pg.push_back(point(x, y + width));
            pg.push_back(point(x + width, y + width));
        }
        
        polygon hull = grahamConvexHull(pg);
        
        //int maxDist = 0;
        //for (int i = 0; i < hull.size(); i++)
        //    for (int j = i + 1; j < hull.size(); j++)
        //        maxDist = max(maxDist, hull[i].distTo(hull[j]));          
        //cout << maxDist << '\n';

        cout << rotatingCalipers(hull) << '\n';
    }

    return 0;
}
