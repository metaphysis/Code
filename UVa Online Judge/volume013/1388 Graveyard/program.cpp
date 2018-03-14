// Graveyard
// UVa ID: 1388 
// Verdict: Accepted
// Submission Date: 2017-12-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m;

    while (cin >> n >> m)
    {
        double moved = 0, gap = (double)(n + m) / n;
        for (int i = 0; i < n; i++)
        {
            double d = i * gap;
            moved += min(fabs(d - floor(d)), fabs(d - ceil(d)));
        }

        moved *= 10000.0 / (n + m);
        cout << fixed << setprecision(4) << moved << '\n';
    }

    return 0;
}
