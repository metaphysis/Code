// Tracking Bio-Bots
// UVa ID: 1092
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct segment
{
    long long x1, y1, x2, y2;
    bool operator<(const segment &s) const
    {
        if (y1 != s.y1) return y1 < s.y1;
        return x1 < s.x1;
    }
} segs[1024];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int w;
    long long m, n;
    while (cin >> m >> n >> w)
    {
        if (m == 0) break;
        for (int i = 0; i < w; i++)
            cin >> segs[i].x1 >> segs[i].y1 >> segs[i].x2 >> segs[i].y2;
        cout << blocks << '\n';
    }

    return 0;
}
