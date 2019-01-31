// Cranes
// UVa ID: 11515
// Verdict: Accepted
// Submission Date: 2018-11-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct circle
{
    int x, y, r;
} circles[16];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, C;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> C;
        for (int i = 0; i < C; i++)
            cin >> circles[i].x >> circles[i].y >> circles[i].r;
        int bad[256], cnt = 0;
        for (int i = 0; i < C; i++)
            for (int j = i + 1; j < C; j++)
            {
                int t1 = (circles[i].x - circles[j].x) * (circles[i].x - circles[j].x) + (circles[i].y - circles[j].y) * (circles[i].y - circles[j].y);
                int t2 = (circles[i].r + circles[j].r) * (circles[i].r + circles[j].r);
                if (t1 <= t2) bad[cnt++] = (1 << i) | (1 << j);
            }

        int most = 0;
        for (int i = 1; i < (1 << C); i++)
        {
            bool good = true;
            for (int j = 0; j < cnt; j++)
                if ((i & bad[j]) == bad[j])
                {
                    good = false;
                    break;
                }
            if (!good) continue;
            int area = 0;
            for (int j = 0; j < C; j++)
                if (i & (1 << j))
                    area += circles[j].r * circles[j].r;
            most = max(most, area);
        }

        cout << most << '\n';
    }

    return 0;
}
