// Water Falls
// UVa ID: 833
// Verdict: Accepted
// Submission Date: 2016-12-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

struct point
{
    int x, y;
};

struct segment
{
    point left, right, lower;
    int flag;

    bool operator<(const segment &s) const
    {
        return max(left.y, right.y) > max(s.left.y, s.right.y);
    }
};

// 叉积，判断点a，b，c组成的两条线段的转折方向。当叉积大于0，则形成一个右拐，
// 否则共线（cp = 0）或左拐（cp < 0）。
int crossProduct(const point &a, const point &b, const point &c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 从点a向点b望去，点c位于线段ab的左侧或在线段上，返回true。
bool ccw(const point &a, const point &b, const point &c)
{
	return crossProduct(a, b, c) <= 0;
}

bool pointOnSegment(const point &p, const segment &s)
{
    return p.x >= s.left.x && p.x <= s.right.x && ccw(s.left, s.right, p);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;
    
    point point1, point2, lower, point3;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        int NP;
        cin >> NP;

        vector<segment> segments;
        for (int i = 1; i <= NP; i++)
        {
            cin >> point1.x >> point1.y >> point2.x >> point2.y;
            if (point1.x > point2.x) swap(point1, point2);
            if (point1.y < point2.y) lower = point1;
            else lower = point2;
            segments.push_back((segment){point1, point2, lower, 0});
        }
        
        sort(segments.begin(), segments.end());
        
        int NS;
        cin >> NS;

        for (int i = 1; i <= NS; i++)
        {
            cin >> point3.x >> point3.y;

            while (true)
            {
                bool updated = false;
                for (int j = 0; j < segments.size(); j++)
                    if (segments[j].flag < i && pointOnSegment(point3, segments[j]))
                    {
                        point3 = segments[j].lower;
                        segments[j].flag = i;
                        updated = true;
                        break;
                    }
                if (!updated) break;
            }
            
            cout << point3.x << '\n';
        }

    }
    
	return 0;
}
