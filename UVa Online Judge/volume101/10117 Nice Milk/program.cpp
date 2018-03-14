// Nice Milk （美味的牛奶）
// PC/UVa IDs: 111408/10117, Popularity: C, Success rate: low Level: 4
// Verdict: Accepted
// Submission Date: 2017-05-08
// UVa Run Time: 0.160s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAXN 25
#define EPSILON (1E-7)

struct point
{
    double x, y;
};

// 使用直线和 X 轴所成的角度和直线经过的两个点的坐标来表示该条直线。
struct line
{
    point a, b;
    double angle;
};

// edges 直线组指的是凸多边形相邻顶点之间的直线，innerLine 直线组指的是 edges
// 向凸多边形中心靠近 h 距离后的直线。
line edges[MAXN], innerLine[MAXN], deque[MAXN], tmpLine[MAXN];
point bread[MAXN], innerBread[MAXN];
int innerN;
double minArea;
bool finished, dipped[MAXN];

double cp(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

// 从点 a 向点 b 望去，点 c 位于线段 ab 的右侧，返回 true。
bool cw(point a, point b, point c)
{
    return cp(a, b, c) < -EPSILON;
}

// 从点 a 向点 b 望去，点 c 位于线段 ab 的左侧时，返回 true。
bool ccw(point a, point b, point c)
{
    return cp(a, b, c) > EPSILON;
}

void pointsToLine(point a, point b, line &l)
{
    l.a = a;
    l.b = b;
    l.angle = atan2(a.y - b.y, a.x - b.x);
}

// 角度排序函数。
bool cmpAngle(line a, line b)
{
    return fabs(a.angle - b.angle) <= EPSILON;
}

// 半平面比较函数。
bool cmpLine(line f, line s)
{
    if (fabs(f.angle - s.angle) <= EPSILON) return cw(f.a, f.b, s.a);
    return f.angle < s.angle;
}

// 两条直线是否平行。
bool parallel(line f, line s)
{
    return fabs((f.a.x - f.b.x) * (s.a.y - s.b.y) - (s.a.x - s.b.x) * (f.a.y - f.b.y)) <= EPSILON;
}

// 计算两点间距离。
double getDist(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// 坐标变换。
void shiftPoint(point a, point b, point &c, point &d, double offset)
{
    double distance = getDist(a, b);
    double dx = offset / distance * (a.y - b.y);
    double dy = offset / distance * (-a.x + b.x);
    c.x = a.x + dx;
    c.y = a.y + dy;
    d.x = b.x + dx;
    d.y = b.y + dy;
}

// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能并不是按逆时针方向给出。
double area(point p[], int n)
{
    if (n < 3) return 0.0;
    double total = 0.0;
    for (int i = 0, j = (i + 1) % n; i < n; i++, j = (i + 1) % n)
        total += (p[i].x * p[j].y - p[j].x * p[i].y);
    return fabs(total / 2.0);
}

point getIntersection(line f, line s)
{
    point p = f.a;
    double tmp =
        ((f.a.x - s.a.x) * (s.a.y - s.b.y) - (f.a.y -
            s.a.y) * (s.a.x - s.b.x)) / ((f.a.x -
            f.b.x) * (s.a.y - s.b.y) - (f.a.y - f.b.y) * (s.a.x - s.b.x));
    p.x += (f.b.x - f.a.x) * tmp;
    p.y += (f.b.y - f.a.y) * tmp;
    return p;
}

// 给定一组直线，求直线的交点得到多边形的顶点。
void halfPlaneIntersection(line *edges, int n, point *vertex, int &nPoint)
{
    nPoint = 0;
    sort(edges, edges + n, cmpLine);
    n = unique(edges, edges + n, cmpAngle) - edges;

    int bottom = 0, top = 1;
    deque[0] = tmpLine[0], deque[1] = tmpLine[1];

    for (int i = 2; i < n; i++)
    {
        if (parallel(deque[top], deque[top - 1]) || parallel(deque[bottom], deque[bottom + 1]))
            return;

        while (bottom < top && cw(tmpLine[i].a, tmpLine[i].b,
                getIntersection(deque[top], deque[top - 1])))
            top--;

        while (bottom < top && cw(tmpLine[i].a, tmpLine[i].b,
                getIntersection(deque[bottom], deque[bottom + 1])))
            bottom++;

        deque[++top] = tmpLine[i];
    }

    while (bottom < top && cw(deque[bottom].a, deque[bottom].b,
            getIntersection(deque[top], deque[top - 1])))
        top--;

    while (bottom < top && cw(deque[top].a, deque[top].b,
            getIntersection(deque[bottom], deque[bottom + 1])))
        bottom++;

    if (top <= (bottom + 1))
        return;

    // 求相邻两条凸包边的交点获取顶点坐标。
    for (int i = bottom; i < top; i++)
        vertex[nPoint++] = getIntersection(deque[i], deque[i + 1]);

    // 首尾两条直线的交点也是顶点。
    if (bottom < (top + 1))
        vertex[nPoint++] = getIntersection(deque[bottom], deque[top]);
}

// 回溯以遍历可能的蘸牛奶方案。
void backtrack(int choice, int current, int target, int n)
{
    if ((n - choice) < (target - current))
        return;

    if (current == target)
    {
        memcpy(tmpLine, edges, sizeof(edges));
        for (int i = 0; i < n; i++)
            if (dipped[i])
                tmpLine[i] = innerLine[i];
        halfPlaneIntersection(tmpLine, n, innerBread, innerN);
        minArea = min(minArea, area(innerBread, innerN));
        if (minArea == 0.0)
            finished = true;
    }
    else
    {
        for (int i = choice; i < n; i++)
            if (dipped[i] == false)
            {
                dipped[i] = true;
                backtrack(i, current + 1, target, n);
                dipped[i] = false;
                if (finished)
                    return;
            }
    }
}

int main(int argc, char const *argv[])
{
    cout.precision(2);
    cout.setf(ios::fixed | ios::showpoint);

    int n, k, h;

    while (cin >> n >> k >> h, n || k || h)
    {
        for (int i = 0; i < n; i++)
            cin >> bread[i].x >> bread[i].y;

        // 牛奶深度为 0，或者蘸的次数为 0，则能蘸到的面积为 0。
        if (h == 0 || k == 0)
        {
            cout << "0.00" << endl;
            continue;
        }

        // 求预设的直线组 edges 和 innerLine，直线组 innerLine 中直线由直线
        // 组 edges 移动 h 距离而来。
        for (int i = 0, j = (i + 1) % n; i < n; i++, j = (i + 1) % n)
        {
            pointsToLine(bread[i], bread[j], edges[i]);
            point c, d;
            shiftPoint(bread[i], bread[j], c, d, (double)(h));
            pointsToLine(c, d, innerLine[i]);
        }

        // 当蘸的次数大于边数时，重设蘸的次数。
        k = min(k, n);

        // 回溯遍历可能的蘸牛奶方案。
        finished = false;
        minArea = 1E20;
        memset(dipped, false, sizeof(dipped));
        backtrack(0, 0, k, n);

        double allArea = area(bread, n);
        cout << (allArea - minArea) << endl;
    }

    return 0;
}
