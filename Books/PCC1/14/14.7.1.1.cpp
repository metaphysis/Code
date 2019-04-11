const double EPSILON = 1e-7;

struct point {
    double x, y;
    bool operator==(const point &p) const {
        return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
    }
};

struct line {
    point a, b;
    bool contains(point p) { return pointInBox(p, a, b); }
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

bool collinear(point a, point b, point c)
{
    return fabs(cp(a, b, c)) <= EPSILON;
}

bool parallel(line p, line q)
{
    return fabs((p.a.x - p.b.x) * (q.a.y - q.b.y) -
        (q.a.x - q.b.x) * (p.a.y - p.b.y)) <= EPSILON;
}

point getIntersection(line p, line q)
{
    point p = p.a;
    double scale = 
        ((p.a.x - q.a.x) * (q.a.y - q.b.y) - (p.a.y - q.a.y) * (q.a.x - q.b.x)) /
        ((p.a.x - p.b.x) * (q.a.y - q.b.y) - (p.a.y - p.b.y) * (q.a.x - q.b.x));
    p.x += (p.b.x - p.a.x) * scale;
    p.y += (p.b.y - p.a.y) * scale;
    return p;
}

vector<polygon> halfPlaneIntersection(polygon pg, line cutline)
{
    polygon cutted;
    for (int i = 0; i < pg.size(); i++) {
        point p1 = pg[i], p2 = pg[(i + 1) % pg.size()];
        cutted.push_back(p1);
        line edge = line{p1, p2};
        if (parallel(edge, cutline)) continue;
        if (!collinear(cutline.a, cutline.b, p1)) {
            point p3 = getIntersection(edge, cutline);
            if (edge.contains(p3)) cutted.push_back(p3);
        }
    }
    cutted.erase(unique(cutted.begin(), cutted.end()), cutted.end());
    if (cutted.size() > 0 && cutted.front() == cutted.back()) cutted.pop_back();

    polygon leftHalf, rightHalf;
    for (auto v : cutted.vertices) {
        if (collinear(cutline.a, cutline.b, v)) {
            leftHalf.push_back(v);
            rightHalf.push_back(v);
        }
        else {
            if (cw(cutline.a, cutline.b, v))
                rightHalf.push_back(v);
            else
                leftHalf.push_back(v);
        }
    }

    vector<polygon> partitions;
    if (leftHalf.size() >= 3) partitions.push_back(leftHalf);
    if (rightHalf.size() >= 3) partitions.push_back(rightHalf);
    return partitions;
}
