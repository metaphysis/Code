// Double version.
const double EPSILON = 1e-7;

struct point
{
	double x, y;

	bool operator<(const point &p) const
	{
	    if (fabs(y - p.y) > EPSILON) return y < p.y;
	    return x < p.x;
	}

	bool operator==(const point &p) const
	{
	    return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
	}

	double distTo(const point &p)
	{
	    return pow(x - p.x, 2) + pow(y - p.y, 2);
	}
};

typedef vector<point> polygon;

point pr;

double cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cw(point a, point b, point c)
{
	return cp(a, b, c) < -EPSILON;
}

bool ccw(point a, point b, point c)
{
	return cp(a, b, c) > EPSILON;
}

bool collinear(point a, point b, point c)
{
	return fabs(cp(a, b, c)) <= EPSILON;
}

bool ccwOrCollinear(point a, point b, point c)
{
	return ccw(a, b, c) || collinear(a, b, c);
}

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
	ch.erase(ch.begin() + top, ch.end());

	return ch;
}

// Int version.
struct point
{
	int x, y;
    point(int x = 0, int y = 0): x(x), y(y) {}
	bool operator<(const point &p) const
	{
	    if (y != p.y) return y < p.y;
	    return x < p.x;
	}
	bool operator==(const point &p) const { return x == p.x && y == p.y; }
	int distTo(const point &p) { return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y); }
};

typedef vector<point> polygon;

point pr;

int cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cw(point a, point b, point c)
{
	return cp(a, b, c) < 0;
}

bool ccw(point a, point b, point c)
{
	return cp(a, b, c) > 0;
}

bool collinear(point a, point b, point c)
{
	return abs(cp(a, b, c)) == 0;
}

bool ccwOrCollinear(point a, point b, point c)
{
	return ccw(a, b, c) || collinear(a, b, c);
}

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
	ch.erase(ch.begin() + top, ch.end());

	return ch;
}
