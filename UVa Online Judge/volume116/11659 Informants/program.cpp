// Informants
// UVa ID: 11659
// Verdict: Accepted
// Submission Date: 2022-01-26
// UVa Run Time: 0.100s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, a;
    int survey[24][2];
    while (cin >> n >> a)
    {
        if (n == 0) break;
        memset(survey, 0, sizeof survey);
        int self = 0;
        for (int i = 0, x, y, absy; i < a; i++)
        {
            cin >> x >> y;
            x--;
            absy = abs(y) - 1;
            survey[x][0] |= 1 << absy;
            if (y > 0) survey[x][1] |= 1 << absy;
            if (x == absy && y < 0) self |= 1 << absy;
        }
        int maxn = 0;
        for (int i = 0; i < (1 << n); i++)
        {
            if (i & self) continue;
            int valid = 1;
            for (int j = 0; j < n; j++)
            {
                if (i & (1 << j))
                    if ((i & survey[j][0]) != survey[j][1])
                    {
                        valid = 0;
                        break;
                    }
            }
            if (valid) maxn = max(maxn, __builtin_popcount(i));
        }
        cout << maxn << '\n';
    }
    return 0;
}
