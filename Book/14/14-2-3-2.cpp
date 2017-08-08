#include <iostream>
#include <cmath>

using namespace std;

const double EPSILON = 1E-7;

struct point
{
    double x, y;
};

// 叉积。
int crossProduct(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) < -EPSILON;
}
// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point a, point b, point c)
{
	return crossProduct(a, b, c) > EPSILON;
}

struct segment
{
    point p1, p2;

    bool contains(point &p)
    {
        return p.x >= min(p1.x, p2.x) && p.x <= max(p1.x, p2.x) &&
            p.y >= min(p1.y, p2.y) && p.y <= max(p1.y, p2.y);
    }
};

bool intersected(segment &s1, segment &s2)
{
    double cp1, cp2, cp3, cp4;

    cp1 = crossProduct(s1.p1, s1.p2, s2.p1);
    cp2 = crossProduct(s1.p1, s1.p2, s2.p2);
    cp3 = crossProduct(s2.p1, s2.p2, s1.p1);
    cp4 = crossProduct(s2.p1, s2.p2, s1.p2);
    
    if ((cp1 * cp2 < 0) && (cp3 * cp4) < 0) return true;
    if (fabs(cp1) <= EPSILON && s1.contains(s2.p1)) return true;
    if (fabs(cp2) <= EPSILON && s1.contains(s2.p2)) return true;
    if (fabs(cp3) <= EPSILON && s2.contains(s1.p1)) return true;
    if (fabs(cp4) <= EPSILON && s2.contains(s1.p2)) return true;
        
    return false;
}
    
int main(int argc, char* argv[])
{
    double x, y;
    segment s1, s2;
    
    while (cin >> x >> y)
    {
        s1.p1 = (point){x, y};
        cin >> x >> y;
        
        s1.p2 = (point){x, y};
        cin >> x >> y;
        
        s2.p1 = (point){x, y};
        cin >> x >> y;
        
        s2.p2 = (point){x, y};
        
        cout << (intersected(s1, s2) ? "Yes" : "No") << endl;
    }

    return 0;
}
