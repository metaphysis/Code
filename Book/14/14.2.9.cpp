double getDistSS(segment s1, segment s2)
{
	if (isIntersected(s1, s2)) return 0.0;
	return min(min(getDistPS(s2.p1, s1), getDistPS(s2.p2, s1)),
	    min(getDistPS(s1.p1, s2), getDistPS(s1.p2, s2)));
}
