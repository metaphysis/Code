const double EPSILON = 1e-7;

struct point {
    double x, y;
};

struct circle {
    double x, y, r;
    double distTo(point a) { return sqrt(pow(x - a.x, 2) + pow(y - a.y, 2)); }
};

circle getCircleFromTriangle(point &a, point &b, point &c)
{
    double A1 = a.x - b.x, B1 = a.y - b.y;
    double A2 = c.x - b.x, B2 = c.y - b.y;
    double C1 = (a.x * a.x - b.x * b.x + a.y * a.y - b.y * b.y) / 2;
    double C2 = (c.x * c.x - b.x * b.x + c.y * c.y - b.y * b.y) / 2;

    circle cc;
    cc.x = (C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1);
    cc.y = (A1 * C2 - A2 * C1) / (A1 * B2 - A2 * B1);
    cc.r = cc.distTo(a);

    return cc;
}

double getMinCoverCircle(point v[], int n)
{
    random_shuffle(v, v + n);
    circle c;
    c.x = v[0].x, c.y = v[0].y, c.r = 0;

    for (int i = 1; i < n; i++)
        if (c.distTo(v[i]) >= c.r + EPSILON) {
            c.x = v[i].x, c.y = v[i].y, c.r = 0;
            for (int j = 0; j < i; j++)
                if (c.distTo(v[j]) >= c.r + EPSILON) {
                    c.x = (v[i].x + v[j].x) / 2, c.y = (v[i].y + v[j].y) / 2;
                    c.r = c.distTo(v[i]);
                    for (int k = 0; k < j; k++)
                        if (c.distTo(v[k]) >= c.r + EPSILON)
                            c = getCircleFromTriangle(v[i], v[j], v[k]);
                }
        }
    return c.r;
}
