struct point {
    double x, y;

    point (double x = 0, double y = 0): x(x), y(y) {}

    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double a) { return point(a * x, a * y); };
    point operator / (double a) { return point(x / a, y / a); };

    bool operator < (const point &p) const {
        return x != p.x ? x < p.x : y < p.y;
    }

    bool operator == (const point &p) const {
        return fabs(x - p.x) < EPSILON && fabs(y - p.y) < EPSILON;
    }
};

double nrom(point a)
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
