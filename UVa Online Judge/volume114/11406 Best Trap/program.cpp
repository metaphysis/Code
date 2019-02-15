// Best Trap
// UVa ID: 11406
// Verdict: Accepted
// Submission Date: 2019-02-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
} dots[20];

struct circle {
    double x, y, r;
    double distTo(point a) { return sqrt(pow(x - a.x, 2) + pow(y - a.y, 2)); }
};

circle getCircleFromTriangle(point &a, point &b, point &c)
{
    double A1 = a.x - b.x, B1 = a.y - b.y;
    double A2 = c.x - b.x, B2 = c.y - b.y;
    double C1 = (a.x * a.x - b.x * b.x + a.y * a.y - b.y * b.y) / 2;
    double C2 = (c.x * c.x - b.x * b.x + c.y * c.y - b.y * b.y) / 2;

    circle cc;
    cc.x = (C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1);
    cc.y = (A1 * C2 - A2 * C1) / (A1 * B2 - A2 * B1);
    cc.r = cc.distTo(a);

    return cc;
}

double getDist(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int mosquitoes, n;
double N, radius;

void update(double x, double y)
{
    int inCircle = 0;
    for (int i = 0; i < n; i++)
        if (getDist(dots[i].x, dots[i].y, x, y) <= radius)
            inCircle++;
    mosquitoes = max(inCircle, mosquitoes);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> radius >> n;
        for (int i = 0; i < n; i++)
            cin >> dots[i].x >> dots[i].y;
        mosquitoes = 0;
        for (int i = 0; i < n; i++)
        {
            update(dots[i].x, dots[i].y);
            for (int j = i + 1; j < n; j++)
            {
                update((dots[i].x + dots[j].x) / 2, (dots[i].y + dots[j].y) / 2);
                for (int k = j + 1; k < n; k++)
                {
                    circle cc = getCircleFromTriangle(dots[i], dots[j], dots[k]);
                    update(cc.x, cc.y);
                }
            }
        }
        cout << mosquitoes << '\n';
    }

    return 0;
}
