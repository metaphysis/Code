// Brownie Points I
// UVa ID: 10865
// Verdict: Accepted
// Submission Date: 2017-12-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
}ps[200010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> ps[i].x >> ps[i].y;

        int centerx = ps[n / 2].x, centery = ps[n / 2].y;
        int stan = 0, ollie = 0;
        for (int i = 0; i < n; i++)
        {
            if ((ps[i].x > centerx && ps[i].y > centery) || (ps[i].x < centerx && ps[i].y < centery))
                stan++;
            if ((ps[i].x > centerx && ps[i].y < centery) || (ps[i].x < centerx && ps[i].y > centery))
                ollie++;
        }
        cout << stan << ' ' << ollie << '\n';
    }

    return 0;
}
