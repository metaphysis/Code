// Points
// UVa ID: 11072
// Verdict: Accepted
// Submission Date: 2023-04-06
// UVa Run Time: 0.310s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

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
	bool operator<(const point &p) const {
	    if (fabs(y - p.y) > EPSILON) return y < p.y;
	    return x < p.x;
	}
	bool operator==(const point &p) const {
	    return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
	}
};

typedef vector<point> polygon;

double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double cross(point a, point b) { return a.x * b.y - a.y * b.x; }

double cp(point &a, point &b, point &c) {
	return cross(b - a, c - a);
}

bool ccw(point &a, point &b, point &c) {
    return cp(a, b, c) > EPSILON;
}

bool ccwOrCollinear(point &a, point &b, point &c) {
    double cp1 = cp(a, b, c);
	return cp1 > EPSILON || fabs(cp1) <= EPSILON;
}

polygon andrewConvexHull(polygon &pg) {
	polygon ch;
    sort(pg.begin(), pg.end());
	for (int i = 0; i < pg.size(); i++) {
		while (ch.size() >= 2 &&
		    ccwOrCollinear(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}
	for (int i = pg.size() - 1, upper = ch.size() + 1; i >= 0; i--)	{
		while (ch.size() >= upper &&
		    ccwOrCollinear(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}
    ch.pop_back();
	return ch;
}

const int OUT = 0, ON = 1, IN = 2;

int isPointInPolygon(point p, polygon &pg) {
    bool in = false;
    for (int i = 0; i < pg.size(); i++) {
        point a = pg[i] - p, b = pg[(i + 1) % pg.size()] - p;
        if (abs(cross(a, b)) < EPSILON && dot(a, b) < EPSILON) return ON;
        if (a.y > b.y) swap(a, b);
        if (a.y < EPSILON && EPSILON < b.y && cross(a, b) > EPSILON) in = !in;
    }
    return in ? IN : OUT;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int p, r;
    while (cin >> p) {
        polygon pg;
        for (int i = 0, x, y; i < p; i++) {
            cin >> x >> y;
            pg.push_back(point(x, y));
        }
        polygon ch = andrewConvexHull(pg);
        cin >> r;
        for (int i = 0, x, y; i < r; i++) {
            cin >> x >> y;
            if (isPointInPolygon(point(x, y), ch) == OUT) cout << "outside";
            else cout << "inside";
            cout << '\n';
        }
    }
    return 0;
}
