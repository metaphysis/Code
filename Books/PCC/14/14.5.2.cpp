const double EPSILON = 1e-7;

struct point
{
	double x, y;
	
	bool operator<(const point &p) const
	{
	    if (fabs(x - p.x) > EPSILON) return x < p.x;
	    return y < p.y;
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

polygon jarvisConvexHull(polygon &pg)
{
    polygon ch;

    sort(pg.begin(), pg.end());
    pg.erase(unique(pg.begin(), pg.end()), pg.end());

    int current = 0;
    do
    {
        int next = 0;
        for (int i = 1; i < pg.size(); i++)
        {
            if (cw(pg[current], pg[next], pg[i]) ||
                (collinear(pg[current], pg[next], pg[i]) &&
                pg[current].distTo(pg[i]) > pg[current].distTo(pg[next])))
                next = i;
        }
        
        ch.push_back(pg[next]);
        current = next;
    } while (current != 0);
    
    return ch;
}
