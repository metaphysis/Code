#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-10
#define INF 1e+30
#define MAXN 128

#define S_MUL 0.5f
#define S_LEN acos(-1)
#define T_CNT 20
#define E_CNT 30

struct Pt
{
	double x, y;
	Pt(double a = 0, double b = 0): x(a), y(b) {}
	Pt operator-(const Pt &a) const
	{
		return Pt(x - a.x, y - a.y);
	}
	Pt operator+(const Pt &a) const
	{
		return Pt(x + a.x, y + a.y);
	}
	Pt operator*(const double a) const
	{
		return Pt(x * a, y * a);
	}
	Pt operator/(const double a) const
	{
		return Pt(x / a, y / a);
	}
	bool operator==(const Pt &a) const
	{
		return fabs(x - a.x) < EPS && fabs(y - a.y) < EPS;
	}
	bool operator<(const Pt &a) const
	{
		if (fabs(x - a.x) > EPS)
			return x < a.x;
		if (fabs(y - a.y) > EPS)
			return y < a.y;
		return false;
	}
	double length()
	{
		return hypot(x, y);
	}
	void read()
	{
		scanf("%lf %lf", &x, &y);
	}
};

struct Pt3D
{
	double x, y, z;
	Pt3D(double a = 0, double b = 0, double c = 0)
			: x(a), y(b), z(c)
	{
	}
	Pt3D operator-(const Pt3D &a) const
	{
		return Pt3D(x - a.x, y - a.y, z - a.z);
	}
	Pt3D operator+(const Pt3D &a) const
	{
		return Pt3D(x + a.x, y + a.y, z + a.z);
	}
	Pt3D operator*(const double a) const
	{
		return Pt3D(x * a, y * a, z * a);
	}
	bool operator==(const Pt3D &a) const
	{
		return fabs(x - a.x) < EPS && fabs(y - a.y) < EPS && fabs(z - a.z) < EPS;
	}
	bool operator<(const Pt3D &a) const
	{
		if (fabs(x - a.x) > EPS)
		{
			return x < a.x;
		}
		if (fabs(y - a.y) > EPS)
		{
			return y < a.y;
		}
		if (fabs(z - a.z) > EPS)
		{
			return z < a.z;
		}
		return false;
	}
	double dot(Pt3D &a)
	{
		return x * a.x + y * a.y + z * a.z;
	}
	double length()
	{
		return sqrt(x * x + y * y + z * z);
	}
	void read()
	{
		scanf("%lf%lf%lf", &x, &y, &z);
	}
};

int cmp_zero(double v)
{
	if (fabs(v) > EPS)
	{
		return v > 0 ? 1 : -1;
	}
	return 0;
}
double dot(Pt a, Pt b)
{
	return a.x * b.x + a.y * b.y;
}
double cross(Pt o, Pt a, Pt b)
{
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
double cross2(Pt a, Pt b)
{
	return a.x * b.y - a.y * b.x;
}
int btw(Pt a, Pt b, Pt c)
{
	return dot(c - a, b - a) >= -EPS && dot(c - b, a - b) >= -EPS;
}
int on_seg(Pt a, Pt b, Pt c)
{
	return btw(a, b, c) && fabs(cross(a, b, c)) < EPS;
}
double dist(Pt a, Pt b)
{
	return hypot(a.x - b.x, a.y - b.y);
}

struct Seg
{
	Pt s, e;
	int label;
	Seg(Pt a = Pt(), Pt b = Pt(), int l = 0): s(a), e(b), label(l) {}
	bool operator!=(const Seg &other) const
	{
		return !((s == other.s && e == other.e) || (e == other.s && s == other.e));
	}
};

int intersect(Pt as, Pt at, Pt bs, Pt bt)
{
	return cmp_zero(cross(as, at, bs) * cross(as, at, bt)) <= 0 &&
				 cmp_zero(cross(bs, bt, as) * cross(bs, bt, at)) <= 0;
}
Pt get_intersect(Seg a, Seg b)
{
	Pt u = a.s - b.s;
	double t = cross2(b.e - b.s, u) / cross2(a.e - a.s, b.e - b.s);
	return a.s + (a.e - a.s) * t;
}
double get_angle(Pt va, Pt vb)
{// seg, !vect
	return acos(dot(va, vb) / va.length() / vb.length());
}
Pt rot_rad(Pt a, double rad)
{
	double x, y;
	x = a.x * cos(rad) - a.y * sin(rad);
	y = a.x * sin(rad) + a.y * cos(rad);
	return Pt(x, y);
}

int in_poly(Pt p[], int n, Pt q)
{
	int i, j, cnt = 0;
	for (i = 0, j = n - 1; i < n; j = i++)
	{
		if (on_seg(p[i], p[j], q))
		{
			return 1;
		}
		if (p[i].y > q.y != p[j].y > q.y &&
				q.x < (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x)
		{
			cnt++;
		}
	}
	return cnt & 1;
}

double rand_dbl()
{
	return (rand() % 32767) / 32767.0f;
}

Pt3D rot_vect_3d(Pt3D nVec, double dx, double dy, double dz)
{
	Pt3D v = nVec;
	// rot x-axis
	v = Pt3D(v.x, v.y * cos(dx) - v.z * sin(dx), v.y * sin(dx) + v.z * cos(dx));
	// rot y-axis
	v = Pt3D(v.x * cos(dy) + v.z * sin(dy), v.y, -v.x * sin(dy) + v.z * cos(dy));
	// rot z-axis
	v = Pt3D(v.x * cos(dz) - v.y * sin(dz), v.x * sin(dz) + v.y * cos(dz), v.z);
	return v;
}

int monotone(int n, Pt p[], Pt ch[])
{
	sort(p, p + n);
	int i, m = 0, t;
	for (i = 0; i < n; i++)
	{
		while (m >= 2 && cross(ch[m - 2], ch[m - 1], p[i]) <= 0)
		{
			m--;
		}
		ch[m++] = p[i];
	}
	for (i = n - 1, t = m + 1; i >= 0; i--)
	{
		while (m >= t && cross(ch[m - 2], ch[m - 1], p[i]) <= 0)
		{
			m--;
		}
		ch[m++] = p[i];
	}
	return m - 1;
}

double small_rect(int n, Pt p[])
{
	int l = 1, r = 1, u = 1;
	double area = INF, per = INF;
	for (int i = 0; i < n; i++)
	{
		Pt edge = (p[(i + 1) % n] - p[i]) / dist(p[(i + 1) % n], p[i]);
		while (dot(edge, p[r % n] - p[i]) < dot(edge, p[(r + 1) % n] - p[i]))
		{
			r++;
		}
		while (u < r || cross2(edge, p[u % n] - p[i]) < cross2(edge, p[(u + 1) % n] - p[i]))
		{
			u++;
		}
		while (l < u || dot(edge, p[l % n] - p[i]) > dot(edge, p[(l + 1) % n] - p[i]))
		{
			l++;
		}
		double w = dot(edge, p[r % n] - p[i]) - dot(edge, p[l % n] - p[i]);
		double h = fabs(cross2(p[i] - p[u % n], p[(i + 1) % n] - p[u % n]) / dist(p[i], p[(i + 1) % n]));
		area = min(area, w * h);
		per = min(per, (w + h) * 2);
	}
	return area;
}

double compute_min_vol(Pt3D nVec, Pt3D D[], int N)
{
	double mn, mx, height;
	Pt3D pD[MAXN], pVec;
	Pt p2D[MAXN];
	mn = mx = nVec.dot(D[0]);
	for (int i = 0; i < N; i++)
	{
		double t = nVec.dot(D[i]);
		mn = min(mn, t), mx = max(mx, t);
	}
	height = (mx - mn) / nVec.length();
	for (int i = 0; i < N; i++)
	{// ax + by + cz - mn = 0
		double t = (nVec.dot(D[i]) - mn) / (nVec.x * nVec.x + nVec.y * nVec.y + nVec.z * nVec.z);
		pD[i] = Pt3D(D[i].x - t * nVec.x, D[i].y - t * nVec.y, D[i].z - t * nVec.z);
	}
	double dx, dy, dz, dx2, dy2, dz2;
	dx = 0, dy = 0;
	dz = -acos(nVec.x / sqrt(nVec.x * nVec.x + nVec.y * nVec.y));
	if (nVec.y < 0)
	{
		dz = -dz;
	}
	pVec = rot_vect_3d(nVec, dx, dy, dz);
	dx2 = 0, dz2 = 0;
	dy2 = -acos(pVec.z / sqrt(pVec.x * pVec.x + pVec.z * pVec.z));
	for (int i = 0; i < N; i++)
	{
		Pt3D pVec;
		pVec = rot_vect_3d(pD[i], dx, dy, dz);
		pVec = rot_vect_3d(pVec, dx2, dy2, dz2);
		p2D[i] = Pt(pVec.x, pVec.y);
	}
	Pt ch[MAXN];
	int M = monotone(N, p2D, ch);
	double area = small_rect(M, ch);
	return height * area;
}

void test(Pt3D v)
{
	double dx, dy, dz;
	Pt3D p;
	dx = 0, dy = 0;
	dz = -acos(v.x / sqrt(v.x * v.x + v.y * v.y));
	if (v.y < 0)
	{
		dz = -dz;
	}
	p = rot_vect_3d(v, dx, dy, dz);
	dx = 0, dz = 0;
	dy = -acos(p.z / sqrt(p.x * p.x + p.z * p.z));
	p = rot_vect_3d(p, dx, dy, dz);
	printf("%lf %lf %lf\n", p.x, p.y, p.z);
	printf("%lf %lf\n", v.length(), p.length());
}

double anneal(Pt3D D[], int N)
{
	double step = S_LEN;// deg
	Pt3D nVec[E_CNT];
	double val[E_CNT];
	for (int i = 0; i < E_CNT; i++)
	{
		double x, y, z;
		do
		{
			x = rand_dbl() - 0.5;
			y = rand_dbl() - 0.5;
			z = rand_dbl() - 0.5;
			if (x || y || z)
				break;
		} while (true);
		nVec[i] = Pt3D(x, y, z);
		val[i] = compute_min_vol(nVec[i], D, N);
	}
	for (int it = 0; it < 20; it++)
	{
		for (int i = 0; i < E_CNT; i++)
		{
			for (int j = 0; j < T_CNT; j++)
			{
				double dx, dy, dz, tmp_val;
				Pt3D rVec;
				dx = rand_dbl() * 2 * step - step;
				dy = rand_dbl() * 2 * step - step;
				dz = rand_dbl() * 2 * step - step;
				rVec = rot_vect_3d(nVec[i], dx, dy, dz);
				tmp_val = compute_min_vol(rVec, D, N);
				if (tmp_val < val[i])
				{
					val[i] = tmp_val, nVec[i] = rVec;
				}
			}
		}
		step *= S_MUL;
	}
	double ret = val[0];
	for (int i = 0; i < E_CNT; i++)
	{
		ret = min(ret, val[i]);
	}
	printf("%.2lf\n", ret);
}

int main()
{
	int N;
	Pt3D D[MAXN];
	while (scanf("%d", &N) == 1 && N)
	{
		for (int i = 0; i < N; i++)
		{
			D[i].read();
		}
		anneal(D, N);
	}
	return 0;
}
