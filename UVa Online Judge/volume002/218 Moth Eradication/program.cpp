// Moth Eradication
// UVa ID: 218
// Verdict: Accepted
// Submission Date: 2016-04-30
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

const int EPSILON = 1E-7;

struct point
{
	double x, y;
};

point lowerLeftPoint;

// 叉积。
double crossProduct(point a, point b, point c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 从点 a 向点 b 望去，点 c 位于线段 ab 的右侧，返回 true。
bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) > EPSILON;
}
// 从点 a 向点 b 望去，点 c 位于线段 ab 的左侧时，返回 true。
bool ccw(point a, point b, point c)
{
	return crossProduct(a, b, c) < -EPSILON;
}

// 当三点共线时，返回true。
bool collinear(point a, point b, point c)
{
	return fabs(crossProduct(a, b, c)) <= EPSILON;
}

// 判断是否向左转或共线。
bool ccwOrCollinear(point a, point b, point c)
{
	return ccw(a, b, c) || collinear(a, b, c);
}

// Andrew 凸包扫描算法的预排序，按 y 坐标排序。
bool lowerLeft(point a, point b)
{
	return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y);
}

// 比较两点是否相同。
bool cmpPoint(point first, point second)
{
    return first.x == second.x && first.y == second.y;
}

// 两点距离的平方值。
double distanceToLowerLeftPoint(point p)
{
    return pow(lowerLeftPoint.x - p.x, 2) + pow(lowerLeftPoint.y - p.y, 2);
}

// 按相对于参考点的极角大小进行排序。
bool smallerAngle(point first, point second)
{
    if (collinear(lowerLeftPoint, first, second))
        return distanceToLowerLeftPoint(first) <= distanceToLowerLeftPoint(second);
    return ccw(lowerLeftPoint, first, second);
}

// Graham 凸包扫描算法。
void grahamConvexHull(vector <point> &vertices, vector <point> &hull)
{
	// 按横坐标和纵坐标排序。
	sort(vertices.begin(), vertices.end(), lowerLeft);

    // 移除重复点。
    vertices.erase(unique(vertices.begin(), vertices.end(), cmpPoint), vertices.end());

    if (vertices.size() <= 2)
    {
        vertices.push_back(vertices[0]);
        for (int i = 0; i < vertices.size(); i++)
            hull.push_back(vertices[i]);
        return;
    }
    
    // 按极角排序。
    lowerLeftPoint = vertices[0];
    
    sort(vertices.begin() + 1, vertices.end(), smallerAngle);

    // 将初始的两点放入凸包。
	int i = 2;
	hull.push_back(vertices[0]);
	hull.push_back(vertices[1]);
	
	// 设置哨兵元素，将最低最左点设置为最后一个元素以便扫描时能回到参考点。
	vertices.push_back(lowerLeftPoint);
	
	while (i <= vertices.size() - 1)
	{
	    if (cw(hull[hull.size() - 2], hull.back(), vertices[i]))
	        hull.erase(hull.end() - 1);
	    else
	        hull.push_back(vertices[i++]);
	}
}

double distances(point a, point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int n, cases = 0;
    
    while (cin >> n, n)
    {
        vector <point> vertices;
        for (int i = 1; i <= n; i++)
        {
            point a;
            cin >> a.x >> a.y;
            vertices.push_back(a);
        }
        
        vector <point> hull;
        grahamConvexHull(vertices, hull);
        reverse(hull.begin(), hull.end());
        
        if (cases++)
            cout << endl;
        cout << "Region #" << cases << ":" << endl;
        
        double length = 0.0;
        cout << "(" << fixed << setprecision(1) << hull[0].x << "," << fixed << hull[0].y << ")";
        for (int i = 1; i < hull.size(); i++)
        {
            cout << "-(" << fixed << setprecision(1) << hull[i].x << "," << fixed << hull[i].y << ")";
            length += distances(hull[i], hull[i - 1]);
        }
        cout << endl;
        cout << "Perimeter length = " << fixed << setprecision(2) << length << endl;
    }
    
    return 0;
}
