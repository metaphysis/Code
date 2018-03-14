// The Incredible Hull
// UVa ID: 596
// Verdict: Accepted
// Submission Date: 2016-08-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_VERTICES = 500;

struct point
{
	int x, y;
	
    bool operator<(const point& another) const
	{
	    if (x != another.x)
	        return x < another.x;
	    else
	        return y < another.y;
	}
	
	bool operator==(const point& another) const
	{
	    return x == another.x && y == another.y;
	}
};

struct polygon
{
	int vertexNumber;
	point vertex[MAX_VERTICES];
};

point vertex[MAX_VERTICES];
int vertexPerObject, vertexOfTotal = 0;

// 叉积，判断点a，b，c组成的两条线段的转折方向。当叉积大于0，则形成一个右拐，
// 否则共线（cp = 0）或左拐（cp < 0）。
int cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point a, point b, point c)
{
	return cp(a, b, c) < 0;
}

// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point a, point b, point c)
{
	return cp(a, b, c) > 0;
}

// 当三点共线时，返回true。
bool collinear(point a, point b, point c)
{
	return abs(cp(a, b, c)) == 0;
}

int distanceOfPoint(point a, point b)
{
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

// Jarvis步进法求凸包。
void jarvisConvexHull()
{
    polygon pg;
    pg.vertexNumber = 0;

	// 去掉重合点。
	// 得到位置处于最左的点，当有共线情况存在时，取y坐标最小的，该顶点定为凸包
	// 上的顶点。
	sort(vertex, vertex + vertexOfTotal);
	vertexOfTotal = unique(vertex, vertex + vertexOfTotal) - vertex;

    int current = 0, visited[MAX_VERTICES];
    memset(visited, 0, sizeof(visited));

    do
    {
        // 寻找凸包的下一个候选顶点。
        // 测试点current，next，i是否构成一个右转，或者共线。
        // 当构成右转时，说明点i比next相对于current有更小的极角，应该将
        // 当前的待选凸包点更新为点i。
        // 当共线时，因为题意要求输出共线的凸包顶点，故选择距离
        // 当前凸包点current更近的点。
        int next = 0;
        for (int i = 1; i < vertexOfTotal; i++)
        {
            if (!visited[i] &&
                (cw(vertex[current], vertex[next], vertex[i]) ||
                distanceOfPoint(vertex[current], vertex[next]) == 0 ||
                (collinear(vertex[current], vertex[next], vertex[i]) &&
                (distanceOfPoint(vertex[current], vertex[i]) <
                distanceOfPoint(vertex[current], vertex[next])))))
                next = i;
        }
        
        // 将点next加入凸包。
        pg.vertex[pg.vertexNumber++] = vertex[next];
        visited[next] = 1;
        current = next;
    } while (current != 0);
    
    int selected = 0;
    for (int i = 0; i < pg.vertexNumber; i++)
        if (pg.vertex[i].x > pg.vertex[selected].x ||
            (pg.vertex[i].x == pg.vertex[selected].x && pg.vertex[i].y < pg.vertex[selected].y))
            selected = i;
    
    for (int i = selected; i < pg.vertexNumber + selected; i++)
        cout << " (" << pg.vertex[i % pg.vertexNumber].x << ',' << pg.vertex[i % pg.vertexNumber].y << ')';
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    char start;
    while (cin >> start, start != 'E')
    {
        string description;
        getline(cin, description);
        if (description.front() == ' ')
            description.erase(description.begin());
        cout << description << " convex hull:\n";
        
        vertexOfTotal = 0;
        while (cin >> start, start == 'P')
        {
            cin >> vertexPerObject;
            for (int i = 0; i < vertexPerObject; i++)
            {
                cin >> vertex[vertexOfTotal].x >> vertex[vertexOfTotal].y;
                vertexOfTotal++;
            }
        }

        jarvisConvexHull();

        cin.putback(start);
    }
    
	return 0;
}
