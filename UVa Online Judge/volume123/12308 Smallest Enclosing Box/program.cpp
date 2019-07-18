// Smallest Enclosing Box
// UVa ID: 12308
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7, PI = 2 * acos(0);

struct point3
{
    double x, y, z;
    point3 (double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
    point3 operator+(const point3 p) { return point3(x + p.x, y + p.y, z + p.z); }
    point3 operator-(const point3 p) { return point3(x - p.x, y - p.y, z - p.z); }
    point3 operator*(double k) { return point3(x * k, y * k, z * k); }
    point3 operator/(double k) { return point3(x / k, y / k, z / k); }
};

struct plane3
{
    point3 a, b, c;
    plane3 (point3 a = point3(0, 0, 0), point3 b = point3(0, 0, 0), point3 c = point3(0, 0, 0)): a(a), b(b), c(c) {}
    point3 operator[](int i)
    {
        if (i == 0) return a;
        if (i == 1) return b;
        if (i == 2) return c;
    }
};

bool zero(double x) { return fabs(x) < EPSILON; }

double norm(point3 p)
{
    return sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
}

point3 cross(point3 a, point3 b)
{
    point3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}

int dot(point3 a, point3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

int signedVolume(point3 p, point3 a, point3 b, point3 c)
{
    return dot(a - p, cross(b - p, c - p));
}

double signedArea(point3 a, point3 b, point3 c)
{
    return norm(cross(b - a, c - a));
}

point3 normalV(plane3 s)
{
    return cross(s.a - s.b, s.b - s.c);
}

double distOfPointToPlane(point3 p, plane3 s)
{
    return fabs(dot(normalV(s), p - s.a)) / norm(normalV(s));
}

double cos(plane3 u, plane3 v)
{
    return dot(normalV(u), normalV(v)) / norm(normalV(u)) / norm(normalV(v));
}

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
};

typedef vector<point> polygon;

double cross(point a, point b) { return a.x * b.y - a.y * b.x; }
double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double norm(point a) { return dot(a, a); }
double abs(point a) { return sqrt(norm(a)); }

double cp(point &a, point &b, point &c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool ccw(point &a, point &b, point &c)
{
    return cp(a, b, c) > EPSILON;
}

bool ccwOrCollinear(point &a, point &b, point &c)
{
    double cp1 = cp(a, b, c);
	return cp1 > EPSILON || fabs(cp1) <= EPSILON;
}

// Any three vertices are not collinear.
polygon andrewConvexHull(polygon &pg)
{
	polygon ch;
    sort(pg.begin(), pg.end());
	for (int i = 0; i < pg.size(); i++)
	{
		while (ch.size() >= 2 &&
		    ccwOrCollinear(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}
	for (int i = pg.size() - 1, upper = ch.size() + 1; i >= 0; i--)
	{
		while (ch.size() >= upper &&
		    ccwOrCollinear(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}
    ch.pop_back();
	return ch;
}

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

point3 rotatePoint(point3 p, point3 v, double theta)
{
    double r = theta;
    double c = cos(r);
    double s = sin(r);
    double x = (v.x * v.x * (1 - c) + c) * p.x + (v.x * v.y * (1 - c) - v.z * s) * p.y + (v.x * v.z * (1 - c) + v.y * s) * p.z;
    double y = (v.y * v.x * (1 - c) + v.z * s) * p.x + (v.y * v.y * (1 - c) + c) * p.y + (v.y * v.z * (1 - c) - v.x * s) * p.z;
    double z = (v.x * v.z * (1 - c) - v.y * s) * p.x + (v.y * v.z * (1 - c) + v.x * s) * p.y + (v.z * v.z * (1 - c) + c) * p.z;
    return point3(x, y, z);
}

bool isSamePoint(point3 a, point3 b)
{
    return zero(a.x - b.x) && zero(a.y - b.y) && zero(a.z - b.z);
}

pair<int, plane3> coincideEdge(plane3 u, plane3 v)
{
    double sv1 = signedVolume(v.a, u.a, u.b, u.c);
    double sv2 = signedVolume(v.b, u.a, u.b, u.c);
    double sv3 = signedVolume(v.c, u.a, u.b, u.c);
    if (zero(sv1) && zero(sv2) && zero(sv3)) return make_pair(0, plane3(point3(0, 0, 0), point3(0, 0, 0), point3(0, 0, 0)));
    point3 pa[3] = {u.a, u.b, u.c}, pb[3] = {v.a, v.b, v.c};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (isSamePoint(pa[i], pb[j]) && isSamePoint(pa[(i + 1) % 3], pb[(j + 2) % 3]))
                return make_pair(1, plane3(pa[i], pa[(i + 1) % 3], pa[(i + 2) % 3]));
    make_pair(0, plane3(point3(0, 0, 0), point3(0, 0, 0), point3(0, 0, 0)));
}

point3 getProjectedPoint(point3 p, plane3 u)
{
    point3 nv = normalV(u);
    double scale = (dot(nv, u.a) - dot(nv, p)) / norm(nv);
    return p + nv * scale;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    point3 psOn3D[16];

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> psOn3D[i].x >> psOn3D[i].y >> psOn3D[i].z;
        // Get 3D convex hull by brute force search.
        vector<plane3> faces;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                {
                    int left = 0, right = 0;
                    // Three points are not colinear.
                    if (zero(signedArea(psOn3D[i], psOn3D[j], psOn3D[k]))) continue;
                    for (int l = 0; l < n; l++)
                    {
                        if (l == i || l == j || l == k) continue;
                        double sv = signedVolume(psOn3D[l], psOn3D[i], psOn3D[j], psOn3D[k]);
                        if (zero(sv)) continue;
                        if (sv > 0) left++;
                        if (sv < 0) right++;
                        if (left * right > 0) break;
                    }
                    if (left == 0 || right == 0)
                        faces.push_back(plane3(psOn3D[i], psOn3D[j], psOn3D[k]));
                }
        // Try every face of 3D convex hull as surface of enclosing box.
        double V = 1e20;
        for (int ii = 0; ii < faces.size(); ii++)
            for (int jj = ii + 1; jj < faces.size(); jj++)
            {
                pair<int, plane3> r = coincideEdge(faces[ii], faces[jj]);
                if (r.first)
                {
                    point3 pp = getProjectedPoint(r.second.c, faces[jj]);
                    for (int kk = 0; kk <= 1000; kk++)
                    {
                        double H = 0;
                        point3 pr = r.second.c + (pp - r.second.c) * (1.0 * kk / 1000);
                        vector<point3> projection;
                        plane3 bottom = plane3(r.second.a, r.second.b, pr);
                        point3 nv = normalV(bottom);
                        for (int j = 0; j < faces.size(); j++)
                            for (int k = 0; k < 3; k++)
                            {
                                projection.push_back(getProjectedPoint(faces[j][k], bottom));
                                H = max(H, distOfPointToPlane(faces[j][k], bottom));
                            }
                        // Get projection of point on plane.
                        double cosv = cos(bottom, plane3(point3(0, 0, 0), point3(1, 0, 0), point3(0, 1, 0)));
                        vector<point> psOn2D;
                        for (int j = 0; j < projection.size(); j++)
                        {
                            point3 p = projection[j] - bottom.c;
                            if (zero(cosv)) psOn2D.push_back(point(p.z, p.y));
                            else psOn2D.push_back(point(p.x / cosv, p.y));
                        }
                        // Get 2D convex hull.
                        sort(psOn2D.begin(), psOn2D.end());
                        psOn2D.erase(unique(psOn2D.begin(), psOn2D.end()), psOn2D.end());
                        polygon pg = andrewConvexHull(psOn2D);
                        reverse(pg.begin(), pg.end());
                        pair<double, double> r = rotatingCalipers(pg);
                        V = min(V, r.first * H);
                    }
                }
            }
        cout << fixed << setprecision(2) << V << '\n';
    }

    return 0;
}
