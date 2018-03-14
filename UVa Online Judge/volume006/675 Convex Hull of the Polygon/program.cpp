// Convex Hull of the Polygon
// UVa ID: 675
// Verdict: Accepted
// Submission Date: 2017-06-07
// UVa Run Time: 0.110s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
	int x, y;
	
	bool operator<(const point &p) const
	{
	    if (y != p.y) return y < p.y;
	    return x < p.x;
	}
	
	bool operator==(const point &p) const
	{
	    return x == p.x && y == p.y;
	}
};

const int MAX_VERTICES = 100005;

typedef vector<point> polygon;

// 叉积，判断点a，b，c组成的两条线段的转折方向。当叉积大于0，则形成一个右拐，
// 否则共线（cp = 0）或左拐（cp < 0）。
int cp(point &a, point &b, point &c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point &a, point &b, point &c)
{
	return cp(a, b, c) < 0;
}

// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point &a, point &b, point &c)
{
	return cp(a, b, c) > 0;
}

// 当三点共线时，返回true。
bool collinear(point &a, point &b, point &c)
{
	return cp(a, b, c) == 0;
}

bool ccwOrCollinear(point &a, point &b, point &c)
{
    return cp(a, b, c) >= 0;
}

double distanceOfPoint(point &a, point &b)
{
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

// Jarvis步进法求凸包。
polygon jarvisConvexHull(polygon &vertices)
{
    polygon pg;
	
	// 排序得到位置处于最左且最下的点，当有共线情况存在时，取y坐标最小的点。
	// 去除重复点。 
    sort(vertices.begin(), vertices.end());

    int current = 0;
    do
    {
        // 测试点current，next，i是否构成一个右转，或者共线。
        // 当构成右转时，说明点i比点next相对于current有更小的极角，应该将当前的
        // 待选凸包点更新为点i。当共线时，选择距离当前凸包点current更远的点。
        int next = 0;
        for (int i = 1; i < vertices.size(); i++)
            if (cw(vertices[current], vertices[next], vertices[i]) ||
                (collinear(vertices[current], vertices[next], vertices[i]) &&
                    (distanceOfPoint(vertices[current], vertices[i]) >
                        distanceOfPoint(vertices[current], vertices[next]))))
                next = i;
        
        // 将点next加入凸包。
        pg.push_back(vertices[next]);
        current = next;
    } while (current != 0);

    return pg;
}

// Andrew 凸包扫描算法。
polygon andrewConvexHull(polygon &vertices)
{
	sort(vertices.begin(), vertices.end());

	point ch[MAX_VERTICES];

	// 求上凸包。
	int top = 0;
	for (int i = 0; i < vertices.size(); i++)
	{
		while (top >= 2 && ccwOrCollinear(ch[top - 2], ch[top - 1], vertices[i]))
			top--;
		ch[top++] = vertices[i];
	}

	// 求下凸包。
	for (int i = vertices.size() - 1, upper = top + 1; i >= 0; i--)
	{
		while (top >= upper && ccwOrCollinear(ch[top - 2], ch[top - 1], vertices[i]))
			top--;
		ch[top++] = vertices[i];
	}

    polygon pg;
    
	for (int i = 0; i < top - 1; i++) pg.push_back(ch[i]);
		
	return pg;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    string separator;
    istringstream iss;
    int cases = 0;
    
    while (getline(cin, line), line.length() > 0)
    {
        polygon source, vertices;
        do
        {
            int x1 = 0, y1 = 0;
            iss.clear(); iss.str(line);
            iss >> x1 >> separator >> y1;
            vertices.push_back(point{x1, y1});
            source.push_back(point{x1, y1});
        }
        while (getline(cin, line), line.length() > 0);

        //polygon convexHull = jarvisConvexHull(vertices);

        //int start = -1;
        //for (int i = 0; i < source.size() && start == -1; i++)
        //    for (int j = 0; j < convexHull.size(); j++)
        //        if (source[i] == convexHull[j])
        //        {
        //            start = j;
        //            break;
        //        }

        //if (cases++ > 0) cout << '\n';
        //int total = convexHull.size();
        //for (int i = 0; i < total; i++)
        //{
        //    int j = (start + i) % total;
        //    cout << convexHull[j].x << ", " << convexHull[j].y << '\n';
        //}
        //cout << convexHull[start].x << ", " << convexHull[start].y << '\n';
        
        polygon convexHull = andrewConvexHull(vertices);

        int start = -1;
        for (int i = 0; i < source.size() && start == -1; i++)
            for (int j = 0; j < convexHull.size(); j++)
                if (source[i] == convexHull[j])
                {
                    start = j;
                    break;
                }

        if (cases++ > 0) cout << '\n';
        int total = convexHull.size();
        for (int i = 0; i < total; i++)
        {
            int j = (total + start - i) % total;
            cout << convexHull[j].x << ", " << convexHull[j].y << '\n';
        }
        cout << convexHull[start].x << ", " << convexHull[start].y << '\n';
    }
    
    return 0;
}
