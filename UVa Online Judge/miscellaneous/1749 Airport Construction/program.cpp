// Airport Construction
// UVa ID: 1749
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
	double x, y;
	
	bool operator<(const point &p) const
	{
	    if (fabs(x - p.x) > EPSILON) return x < p.x;
	    return y < p.y;
	}
	
	bool operator==(const point &p) const
	{
	    return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
	}
	
	double distTo(const point &p)
	{
	    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
	}
};

struct line
{
    double a, b, c;
};

typedef vector<point> polygon;

int n;
polygon pg;
        
// 叉积，判断点a，b，c组成的两条线段的转折方向。当叉积小于0，则形成一个右拐，
// 否则共线（cp = 0）或左拐（cp > 0）。
int crossProduct(point &a, point &b, point &c)
{
    double cp = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return (fabs(cp) < EPSILON) ? 0 : (cp > EPSILON ? 1 : -1);
}

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point &a, point &b, point &c)
{
	return crossProduct(a, b, c) < -EPSILON;
}
// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point &a, point &b, point &c)
{
	return crossProduct(a, b, c) > EPSILON;
}

// 当三点共线时，返回true。
bool collinear(point &a, point &b, point &c)
{
	return fabs(crossProduct(a, b, c)) <= EPSILON;
}

// 判断是否向左转或共线。
bool ccwOrCollinear(point &a, point &b, point &c)
{
	return ccw(a, b, c) || collinear(a, b, c);
}

bool cwOrCollinear(point &a, point &b, point &c)
{
	return cw(a, b, c) || collinear(a, b, c);
}

bool inBound(point &p1, point &p2, point &p3)
{
    return p3.x >= min(p1.x, p2.x) && p3.x <= max(p1.x, p2.x);
}

bool inside(point &p1, point &p2)
{
    
    for (int k = 0; k < n; k++)
    {
        int previous = (k - 1 + n) % n;
        int next = (k + 1) % n;

        if (collinear(p1, p2, pg[k]) && inBound(p1, p2, pg[k]))
        {
            if (cw(pg[k], pg[next], p1)) return false;
            if (ccw(pg[k], pg[previous], p1)) return false;
            if (cw(pg[k], pg[next], p2)) return false;
            if (ccw(pg[k], pg[previous], p2)) return false;
        }
        else
        {
            int cp1 = crossProduct(p1, p2, pg[k]);
            int cp2 = crossProduct(p1, p2, pg[next]);
            int cp3 = crossProduct(pg[k], pg[next], p1);
            int cp4 = crossProduct(pg[k], pg[next], p2);
            
            if (cp1 * cp2 < 0 && cp3 * cp4 < 0) return false;
        }
    }
    
    return true;
}

line pointsToLine(point &p1, point &p2)
{
    line lr;

    if (fabs(p1.x - p2.x) <= EPSILON)
    {
        lr.a = 1.0;
        lr.b = 0.0;
        lr.c = -p1.x;
    }
    else
    {
        lr.a = -(p1.y - p2.y) / (p1.x - p2.x);
        lr.b = 1.0;
        lr.c = -lr.a * p1.x - p1.y;
    }

    return lr;
}

point getIntersection(int i, int j, int k, int l)
{
    line l1 = pointsToLine(pg[i], pg[j]);
    line l2 = pointsToLine(pg[k], pg[l]);
    
    point pi;
    pi.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    if (fabs(l1.b) > EPSILON)
        pi.y = -(l1.a * pi.x + l1.c) / l1.b;
    else
        pi.y = -(l2.a * pi.x + l2.c) / l2.b;

    return pi;
}

double getDist(int i, int j)
{
    point leftEnd = pg[i], rightEnd = pg[j];
    
    if (leftEnd.x > rightEnd.x) swap(leftEnd, rightEnd);

    vector<point> leftChain;
    for (int k = 0; k < n; k++)
    {
        int next = (k + 1) % n;
        int cp1 = crossProduct(pg[i], pg[j], pg[k]);
        int cp2 = crossProduct(pg[i], pg[j], pg[next]);
        
        if (cp1 * cp2 < 0)
        {
            point pi = getIntersection(i, j, k, next);
            if (pi.x < leftEnd.x) leftChain.push_back(pi);
        }
        
        if (cp1 == 0 && pg[k].x < leftEnd.x) leftChain.push_back(pg[k]);
        if (cp2 == 0 && pg[next].x < leftEnd.x) leftChain.push_back(pg[next]);
    }
    
    sort(leftChain.begin(), leftChain.end());
    
    for (int k = leftChain.size() - 1; k >= 0; k--)
    {
        if (inside(leftChain[k], rightEnd)) break;
        leftEnd = leftChain[k];
    }
    
    vector<point> rightChain;
    for (int k = 0; k < n; k++)
    {
        int next = (k + 1) % n;
        int cp1 = crossProduct(pg[i], pg[j], pg[k]);
        int cp2 = crossProduct(pg[i], pg[j], pg[next]);
        
        if (cp1 * cp2 < 0)
        {
            point pi = getIntersection(i, j, k, next);
            if (pi.x > rightEnd.x) rightChain.push_back(pi);
        }
        
        if (cp1 == 0 && pg[k].x > rightEnd.x) rightChain.push_back(pg[k]);
        if (cp2 == 0 && pg[next].x > rightEnd.x) rightChain.push_back(pg[next]);
    }
    
    sort(rightChain.begin(), rightChain.end());
    
    for (int k = 0; k < rightChain.size(); k++)
    {
        if (inside(leftEnd, rightChain[k])) break;
        rightEnd = rightChain[k];
    }
    
    return leftEnd.distTo(rightEnd);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double x1, y1;

    while (cin >> n)
    {
        pg.clear();

        for (int i = 1; i <= n; i++)
        {
            cin >> x1 >> y1;
            pg.push_back(point{x1, y1});
        }
        
        double longest = 0.0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                if (fabs(pg[i].distTo(pg[j]) - longest) < EPSILON) continue;
                if (inside(pg[i], pg[j]))
                {
                    double dist = getDist(i, j);
                    if (dist > longest + EPSILON) longest = dist;
                }
            }
        
        cout << fixed << setprecision(9) << longest << '\n';
    }
    
    return 0;
}
