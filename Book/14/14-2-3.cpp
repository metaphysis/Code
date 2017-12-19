// double version
const double EPSILON = 1e-7;

// 叉积。
double cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	//return cross(b - a, c - a);
}

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point a, point b, point c)
{
	return cp(a, b, c) < -EPSILON;
}
// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point a, point b, point c)
{
	return cp(a, b, c) > EPSILON;
}

bool collinear(point a, point b, point c)
{
    return fabs(cp(a, b, c)) < EPSILON;
}

bool cwOrCollinear(point a, point b, point c)
{
    return cw(a, b, c) || collinear(a, b, c);
}

bool ccwOrCollinear(point a, point b, point c)
{
    return ccw(a, b, c) || collinear(a, b, c);
}

// int version
// 叉积。
int cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	//return cross(b - a, c - a);
}

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point a, point b, point c)
{
	return cp(a, b, c) < 0;
}
// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point a, point b, point c)
{
	return cp(a, b, c) > 0;
}

bool collinear(point a, point b, point c)
{
    return abs(cp(a, b, c)) == 0;
}

bool cwOrCollinear(point a, point b, point c)
{
    return cw(a, b, c) || collinear(a, b, c);
}

bool ccwOrCollinear(point a, point b, point c)
{
    return ccw(a, b, c) || collinear(a, b, c);
}
