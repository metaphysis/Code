// Useless Tile Packers （没用的瓷砖打包公司）
// PC/UVa IDs: 111405/10065, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2017-06-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
	double x, y;
};

typedef vector<point> polygon;

double cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool ccw(point a, point b, point c)
{
	return cp(a, b, c) > EPSILON;
}

polygon melkmanConvexHull(polygon &pg)
{
	if (pg.size() < 3) return pg;

    point deque[2 * pg.size() + 1];
    int bottom = pg.size(), top = bottom - 1;

    bool isLeft = ccw(pg[0], pg[1], pg[2]);
    deque[++top] = isLeft ? pg[0] : pg[1], deque[++top] = isLeft ? pg[1] : pg[0];
    deque[++top] = pg[2], deque[--bottom] = pg[2];

    int next = 3;
    while (next < pg.size())
    {
        if (ccw(deque[top - 1], deque[top], pg[next]) &&
            ccw(deque[bottom], deque[bottom + 1], pg[next]))
        {
            next++;
            continue;
        }

        while (!ccw(deque[top - 1], deque[top], pg[next])) top--;
        deque[++top] = pg[next];

        while (!ccw(pg[next], deque[bottom], deque[bottom + 1])) bottom++;
        deque[--bottom] = pg[next];

        next++;
    }

    polygon ch;
	for (int i = bottom; i < top; i++) ch.push_back(deque[i]);

    return ch;
}
