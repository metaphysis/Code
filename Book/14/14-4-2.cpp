// Useless Tile Packers （没用的瓷砖打包公司）
// PC/UVa IDs: 111405/10065, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2017-06-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int EPSILON = 0;

struct point
{
	int x, y;
	
	bool operator<(const point &p) const
	{
	    if (fabs(x - p.x) > EPSILON) return x < p.x;
	    return y < p.y;
	}
	
	bool operator==(const point &p) const
	{
	    return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
	}
	
	int distTo(const point &p)
	{
	    return pow(x - p.x, 2) + pow(y - p.y, 2);
	}
};

typedef vector<point> polygon;

double area(polygon pg)
{
	double areaOfPolygon = 0.0;

    int n = pg.size();
	for (int i = 0; i < n; i++)
	{
		int j = (i + 1) % n;
		areaOfPolygon += (pg[i].x * pg[j].y - pg[j].x * pg[i].y);
	}

	return fabs(areaOfPolygon / 2.0);
}

// 叉积，判断点a，b，c组成的两条线段的转折方向。当叉积大于0，则形成一个右拐，
// 否则共线（cp = 0）或左拐（cp < 0）。
int crossProduct(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Jarvis步进法求凸包。
polygon jarvisConvexHull(polygon &pg)
{
    polygon ch;

	// 排序得到位置处于最左且最下的点，当有共线情况存在时，取y坐标最小的点。
    sort(pg.begin(), pg.end());
    
	// 去除重复点。
    pg.erase(unique(pg.begin(), pg.end()), pg.end());

    int current = 0;
    do
    {
        // 测试点current，next，i是否构成一个右转，或者共线。
        // 当构成右转时，说明点i比点next相对于current有更小的极角，应该将当前的
        // 待选凸包点更新为点i。
        // 当共线时，选择距离当前凸包点current更远的点。
        int next = 0;
        for (int i = 1; i < pg.size(); i++)
        {
            int cp = crossProduct(pg[current], pg[next], pg[i]);
            if (cp < -EPSILON || (fabs(cp) <= EPSILON &&
                pg[current].distTo(pg[i]) > pg[current].distTo(pg[next])))
                next = i;
        }
        
        // 将点next加入凸包。
        ch.push_back(pg[next]);
        current = next;
    } while (current != 0);
    
    return ch;
}

int main(int argc, char *argv[])
{
	cout.precision(2);
	cout.setf(ios::fixed | ios::showpoint);

	int number, cases = 1;
	while (cin >> number, number)
	{
	    polygon tile(number);
		for (int i = 0; i < number; i++)
			cin >> tile[i].x >> tile[i].y;
		double used = area(tile);
		double all = area(jarvisConvexHull(tile));
		cout << "Tile #" << cases++ << '\n';
		cout << "Wasted Space = " << (1.0 - used / all) * 100.0 << " %\n\n";
	}

	return 0;
}
