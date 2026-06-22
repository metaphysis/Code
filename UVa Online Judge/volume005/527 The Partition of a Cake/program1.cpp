// The partition of a cake
// UVa ID: 527
// Verdict: Accepted
// Submission Date: 2017-05-09
// UVa Run Time: 0.080s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
    double x, y;
    
    bool operator==(const point &p) const
    {
        return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
    }
};

struct line
{
    point a, b;

    bool contains(point p)
    {
        return p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) &&
            p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);
    }
};

typedef vector<point> polygon;

double crossProduct(point p1, point p2, point p3)
{
    return (p3.x - p1.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p3.y - p1.y);
}

bool cw(point p1, point p2, point p3)
{
    return crossProduct(p1, p2, p3) > EPSILON;
}

bool collinear(point p1, point p2, point p3)
{
    return fabs(crossProduct(p1, p2, p3)) <= EPSILON;
}

bool paralle(line line1, line line2)
{
    return fabs((line1.a.x - line1.b.x) * (line2.a.y - line2.b.y) -
        (line2.a.x - line2.b.x) * (line1.a.y - line1.b.y)) <= EPSILON;
}

point intersection(line line1, line line2)
{
    point p = line1.a;
    double scale = ((line1.a.x - line2.a.x) * (line2.a.y - line2.b.y) -
        (line1.a.y - line2.a.y) * (line2.a.x - line2.b.x)) /
        ((line1.a.x - line1.b.x) * (line2.a.y - line2.b.y) -
        (line1.a.y - line1.b.y) * (line2.a.x - line2.b.x));
    p.x += (line1.b.x - line1.a.x) * scale;
    p.y += (line1.b.y - line1.a.y) * scale;
    return p;
}

vector<polygon> halfPlaneIntersection(polygon pg, line cutline)
{
    polygon cutted;

    for (int i = 0; i < pg.size(); i++)
    {
        point p1 = pg[i];
        point p2 = pg[(i + 1) % pg.size()];

        cutted.push_back(p1);

        line edge = line{p1, p2};
        if (paralle(edge, cutline)) continue;

        if (!collinear(cutline.a, cutline.b, p1))
        {
            point p3 = intersection(edge, cutline);
            if (edge.contains(p3)) cutted.push_back(p3);
        }
    }

    cutted.erase(unique(cutted.begin(), cutted.end()), cutted.end());

    if (cutted.size() > 0 && cutted.front() == cutted.back())
        cutted.pop_back();

    polygon leftHalf, rightHalf;

    for (auto v : cutted)
    {
        if (collinear(cutline.a, cutline.b, v))
        {
            leftHalf.push_back(v);
            rightHalf.push_back(v);
        }
        else
        {
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, cuts;
    double x1, y1, x2, y2;

    vector<point> square
    {
        point{0, 0}, point{1000, 0}, point{1000, 1000}, point{0, 1000}
    };

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        vector<polygon> current, next;
        current.push_back(polygon{square});

        cin >> cuts;
        for (int i = 1; i <= cuts; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            line cutline = line{point {x1, y1}, point {x2, y2}};
            for (auto pg : current)
            {
                vector<polygon> partitions = halfPlaneIntersection(pg, cutline);
                for (auto partition : partitions) next.push_back(partition);
            }

            current.swap(next);
            next.clear();
        }

        cout << current.size() << '\n';
    }

    return 0;
}
