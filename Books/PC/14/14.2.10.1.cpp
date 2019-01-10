const int MAXV = 100;
const double EPSILON = 1E-7;

struct point
{
    double x, y;
};

struct segment
{
    point a, b;
};

struct polygon
{
    int number;
    point vertices[MAXV];
};

int cp(point a, point b, point c)
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

bool isSideAboveRay(segment ray, segment side)
{
    return side.p1.y >= ray.p1.y && side.p2.y >= ray.p1.y;
}

bool segmentsIntersect(segment ray, segment side)
{
    double cp1 = cp(ray.p1, ray.p2, side.p1), cp2 = cp(ray.p1, ray.p2, side.p2);
    double cp3 = cp(side.p1, side.p2, ray.p1), cp4 = cp(side.p1, side.p2, ray.p2);
    
    // 跨越式相交。
    if ((cp1 * cp2 < 0) && (cp3 * cp4 < 0)) return true;
        
    // 不相交。
    if ((cp1 * cp2 > 0) || (cp3 * cp4 > 0)) return false;   
        
	// 共线，不论是否重合，均判断为不相交。
    if ((fabs(cp1) <= EPSILON && fabs(cp2) <= EPSILON) ||
        (fabs(cp3) <= EPSILON && fabs(cp4) <= EPSILON))
        return false;
        
	// 相交于顶点，判断是否在射线上方。
    if (fabs(cp1) <= EPSILON || fabs(cp2) <= EPSILON ||
        fabs(cp3) <= EPSILON || fabs(cp4) <= EPSILON)
        return isSideAboveRay (ray, side);

    return false;
}

bool isPointInPolygon(point p, polygon pg)
{
    // 找到多边形顶点中位于最右边的点的横坐标。
    double rightX = pg.vertex[0].x;
    for (int i = 0; i < pg.vertexNumber; i++)
    {
        if (pg.vertex[i].x > rightX)
            rightX = pg.vertex[i].x;
    }
    
    int numberOfIntersection = 0;
    segment ray = (segment){ p, (point){ 2 * rightX, p.y }};
    for (int i = 0; i < pg.vertexNumber; i++)
    {
        segment side = (segment){ pg.vertex[i], pg.vertex[(i + 1) % pg.vertexNumber] };
        if (segmentsIntersect(ray, side))
            numberOfIntersection++;
    }

    // 测试交点个数奇偶性。
    return ((numberOfIntersection & 1) == 1);
}
