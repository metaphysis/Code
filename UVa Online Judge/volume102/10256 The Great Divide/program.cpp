// The Great Divide
// UVa ID: 10256
// Verdict: Accepted
// Submission Date: 2023-04-29
// UVa Run Time: 0.080s
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
    sort(pg.begin(), pg.end());
    pg.erase(unique(pg.begin(), pg.end()), pg.end());

	polygon ch;
	if (pg.size() < 3) {
	    for (int i = 0; i < pg.size(); i++) ch.push_back(pg[i]);
	    return ch;
	}
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

struct segment {
    point p1, p2;
};

bool isIntersected(segment s1, segment s2) {
    double cp1 = cp(s1.p1, s1.p2, s2.p1), cp2 = cp(s1.p1, s1.p2, s2.p2);
    double cp3 = cp(s2.p1, s2.p2, s1.p1), cp4 = cp(s2.p1, s2.p2, s1.p2);
    return cp1 * cp2 < 0 && cp3 * cp4 < 0;
}

bool isPolygonIntersected(polygon pg1, polygon pg2) {
    int s1 = pg1.size(), s2 = pg2.size();
    for (int i = 0; i < s1; i++)
        if (isPointInPolygon(pg1[i], pg2))
            return true;
    for (int i = 0; i < s2; i++)
        if (isPointInPolygon(pg2[i], pg1))
            return true;
    for (int i = 0; i < s1; i++)
        for (int j = 0; j < s2; j++)
            if (isIntersected(segment{pg1[i], pg1[(i + 1) % s1]}, segment{pg2[j], pg2[(j + 1) % s2]}))
                return true;
    return false;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int M, C;
    while (cin >> M >> C, M) {
        polygon pg1, pg2;
        for (int i = 0, x, y; i < M; i++) {
            cin >> x >> y;
            pg1.push_back(point(x, y));
        }
        for (int i = 0, x, y; i < C; i++) {
            cin >> x >> y;
            pg2.push_back(point(x, y));
        }
        if (isPolygonIntersected(andrewConvexHull(pg1), andrewConvexHull(pg2))) cout << "No";
        else cout << "Yes";
        cout << '\n';
    }
    return 0;
}
