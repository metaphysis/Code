struct circle { point c; double r; };
pair<point, point> getIntersection(line l, circle c)
{
    point pr = project(c.c, l);
    e = (l.p2 – l.p1) / abs(l.p2 – l.p1);
    double base = sqrt(c.r * c.r – norm(pr – c.c));
    return make_pair(pr + e * base, pr – e * base);
}
