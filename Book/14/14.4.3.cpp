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
};

typedef vector<point> polygon;

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

// 三个凸包顶点不共线。
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

// 凸包顶点可共线。
polygon andrewConvexHull(polygon &pg)
{
	polygon ch;

    sort(pg.begin(), pg.end());
	for (int i = 0; i < pg.size(); i++)
	{
		while (ch.size() >= 2 &&
		    ccw(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}
	for (int i = pg.size() - 2, upper = ch.size() + 1; i >= 0; i--)
	{
		while (ch.size() >= upper &&
		    ccw(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}
    ch.pop_back();
    
	return ch;
}
