#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>

using namespace std;

#define MAX_VERTICES 105
#define EPSILON 1E-10

struct point
{
	int x;
	int y;
};

struct polygon
{
	int number;
	point vertex[MAX_VERTICES];
};

// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能并不是按逆时针方向给出。
double area(point vertex[], int number)
{
	double total = 0.0;

	for (int i = 0; i < number; i++)
	{
		int j = (i + 1) % number;
		total += (vertex[i].x * vertex[j].y - vertex[j].x * vertex[i].y);
	}

	return fabs(total / 2.0);
}

// 叉积，判断点 first，second，third 组成的两条线段的转折方向。当叉积大于 0，则形成一个右拐，
// 否则共线（cp = 0）或左拐（cp > 0）。
int crossProduct(point a, point b, point c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 从点first向点second望去，点third位于线段first-second的右侧，返回true。
bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) > EPSILON;
}
// 从点first向点second望去，点third位于线段first-second的左侧时，返回true。
bool ccw(point a, point b, point c)
{
	return crossProduct(a, b, c) < -EPSILON;
}

// 当三点共线时，返回true。
bool collinear(point a, point b, point c)
{
	return fabs(crossProduct(a, b, c)) <= EPSILON;
}

double distanceOfPoint(point a, point b)
{
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

// Jarvis 步进法求凸包。
void jarvisConvexHull(point vertex[], int number, polygon& hull)
{
	// 得到位置处于最左的点，当有共线情况存在时，取 y 坐标最小的点。
	int leftLower = 0;
	for (int i = 1; i < number; i++)
        if ((vertex[i].x < vertex[leftLower].x) ||
            (fabs(vertex[i].x - vertex[leftLower].x) <= EPSILON &&
                (vertex[i].y < vertex[leftLower].y)))
            leftLower = i;
                
    // 初始化变量。
    int current = leftLower, next = 0;
    hull.number = 0;

    do
    {
        next = (current + 1) % number;
        
        // 测试点 current，i，next 是否构成一个左转，或者共线。
        // 当构成左转时，说明点 i 相对于 current 有更小的极角，应该将
        // 当前的待选凸包点更新为点 i。
        // 当共线时，选择距离当前凸包点 current 更远的点。
        for (int i = 0; i < number; i++)
            if (ccw(vertex[current], vertex[i], vertex[next]) ||
                (collinear(vertex[current], vertex[i], vertex[next]) &&
                    (distanceOfPoint(vertex[current], vertex[i]) >
                        distanceOfPoint(vertex[current], vertex[next]))))
                next = i;
        
        // 将点 next 加入凸包。
        hull.vertex[hull.number++] = vertex[next];
        current = next;
    } while (current != leftLower);
}

int main(int ac, char *av[])
{
	point tile[MAX_VERTICES];
	polygon container;
	int number, currentCase = 1;

	cout.precision(2);
	cout.setf(ios::fixed | ios::showpoint);

	while (cin >> number, number)
	{
		for (int i = 0; i < number; i++)
		{
			cin >> tile[i].x;
			cin >> tile[i].y;
		}

		double used = area(tile, number);

		jarvisConvexHull(tile, number, container);

		cout << "Tile #" << currentCase++ << endl;
		double all = area(container.vertex, container.number);
		double rate = (1.0 - used / all) * 100.0;
		cout << "Wasted Space = " << rate << " %" << endl;
		cout << endl;
	}

	return 0;
}
