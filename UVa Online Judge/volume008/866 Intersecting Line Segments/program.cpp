// Intersecting Line Segments
// UVa ID: 866
// Verdict: Accepted
// Submission Date: 2016-12-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
};

struct segment
{
    point start, end;
};

// 使用叉积来表示线段的相对方向。
double direction(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 包围盒测试。测试点p是否在线段ab上，不包括在端点上，但部分重合认为相交。
bool pointInBox(point p, point a, point b)
{
    return (p.x > min(a.x, b.x) && p.x < max(a.x, b.x) && p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y)) ||
        (p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) && p.y > min(a.y, b.y) && p.y < max(a.y, b.y));
}

// 根据设定的交点数规则判断射线与多边形的边是否相交。
bool isIntersected(segment ray, segment side)
{
    double d1, d2, d3, d4;
    
    d1 = direction(ray.start, ray.end, side.start);
    d2 = direction(ray.start, ray.end, side.end);
    d3 = direction(side.start, side.end, ray.start);
    d4 = direction(side.start, side.end, ray.end);
    
    // 跨越式相交。
    if ((d1 * d2 < 0) && (d3 * d4 < 0))
        return true;
    
    //cout << "d1 = " << d1 << " d2 = " << d2 << '\n';
    
    // 部分重叠也认为相交。
    if (d1 == 0 && d2 == 0 && (pointInBox(side.start, ray.start, ray.end) || pointInBox(side.end, ray.start, ray.end)))
        return true;
    
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        int N;
        cin >> N;

        vector<segment> segments;
        for (int i = 1; i <= N; i++)
        {
            segment s;
            cin >> s.start.x >> s.start.y >> s.end.x >> s.end.y;
            segments.push_back(s);
        }
        
        int total = segments.size();
        for (int i = 0; i < segments.size(); i++)
            for (int j = i + 1; j < segments.size(); j++)
                if (isIntersected(segments[i], segments[j]))
                    total += 2;
        cout << total << '\n';
    }
    
	return 0;
}
