double getDistPL(point p, line l)
{
	return fabs(cross(l.p2 - p.p1, p - l.p1) / abs(l.p2 - l.p1));
}

double getDistPL(point p, point p1, point p2)
{
	return fabs(cross(p2 - p1, p - p1) / abs(p2 - p1));
}
