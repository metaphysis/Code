// Myacm Triangles
// UVa ID: 10112
// Verdict: Accepted
// Submission Date: 2017-12-19
// UVa Run Time: 0.000s
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

struct point {
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (int a) { return point(a * x, a * y); };
    point operator / (int a) { return point(x / a, y / a); };
};

int area(point a, point b, point c)
{
    return abs((c.y - a.y) * (b.x - a.x) - (b.y - a.y) * (c.x - a.x));
}

int cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

// 叉积。
int cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	//return cross(b - a, c - a);
}

bool inSegment(point a, point b, point c)
{
    return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    char label;
    point vertices[20];

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> label;
            cin >> vertices[i].x >> vertices[i].y;
        }
        
        int maxArea = 0, maxi = 0, maxj = 1, maxk = 2;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                {
                    bool in = false;
                    for (int v = 0; v < n; v++)
                    {
                        if (v == i || v == j || v == k) continue;
                        int cp1 = cp(vertices[i], vertices[j], vertices[v]);
                        if (cp1 == 0 && inSegment(vertices[i], vertices[j], vertices[v]))
                        {
                            in = true;
                            break;
                        }
                        
                        int cp2 = cp(vertices[j], vertices[k], vertices[v]);
                        if (cp2 == 0 && inSegment(vertices[j], vertices[k], vertices[v]))
                        {
                            in = true;
                            break;
                        }
                        
                        int cp3 = cp(vertices[k], vertices[i], vertices[v]);
                        if (cp3 == 0 && inSegment(vertices[k], vertices[i], vertices[v]))
                        {
                            in = true;
                            break;
                        }
                        
                        if ((cp1 > 0 && cp2 > 0 && cp3 > 0) || (cp1 < 0 && cp2 < 0 && cp3 < 0))
                        {
                            in = true;
                            break;
                        }
                    }
                    if (!in)
                    {
                        int currentArea = area(vertices[i], vertices[j], vertices[k]);
                        if (currentArea > maxArea)
                        {
                            maxArea = currentArea;
                            maxi = i, maxj = j, maxk = k;
                        }
                    }
                }
                
        cout << (char)('A' + maxi) << (char)('A' + maxj) << (char)('A' + maxk) << '\n';
    }

    return 0;
}
