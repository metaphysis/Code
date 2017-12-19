// double version
struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double a) { return point(a * x, a * y); };
    point operator / (double a) { return point(x / a, y / a); };
};

double norm(point a)
{
	return a.x * a.x + a.y * a.y;
}

double area(point a, point b, point c)
{
    return 0.5 * fabs((c.y - a.y) * (b.x - a.x) - (b.y - a.y) * (c.x - a.x));
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

// int version
struct point {
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (int a) { return point(a * x, a * y); };
    point operator / (int a) { return point(x / a, y / a); };
};

int norm(point a)
{
	return a.x * a.x + a.y * a.y;
}

// Area of triangle multiply 2
int area(point a, point b, point c)
{
    return abs((c.y - a.y) * (b.x - a.x) - (b.y - a.y) * (c.x - a.x));
}

int dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

int cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}
