const double EPSILON = 1E-7;

struct point { double x, y; };

typedef vector<point> polygon;

int cp(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool ccw(point a, point b, point c) { return cp(a, b, c) > EPSILON; }

bool isPointInPolygon(point p, polygon pg)
{
    bool in = true;
    for (int i = 0; i < pg.size() && in; i++)
        in &= ccw(pg[i], pg[(i + 1) % pg.size()], p)
    return in;
}
