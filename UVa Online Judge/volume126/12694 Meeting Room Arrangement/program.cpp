// Meeting Room Arrangement
// UVa ID: 12694
// Verdict: Accepted
// Submission Date: 2022-01-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

inline bool overlapped(int a, int b, int c, int d)
{
    if (c < a && a < d) return true;
    if (c < b && b < d) return true;
    if (a < c && c < b) return true;
    if (a < d && d < b) return true;
    if (a == c && b == d) return true;
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases, n, event[24][2];
    int starred[24], cnt;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        n = 0;
        while (cin >> event[n][0] >> event[n][1])
        {
            if (event[n][0] == 0 && event[n][1] == 0) break;
            n++;
        }
        int maxn = 0;
        for (int i = 0; i < (1 << n); i++)
        {
            cnt = 0;
            for (int j = 0; j < n; j++)
                if (i & (1 << j))
                    starred[cnt++] = j;
            int valid = 1;
            for (int j = 0; j < cnt && valid; j++)
                for (int k = j + 1; k < cnt && valid; k++)
                    if (overlapped(event[starred[j]][0], event[starred[j]][1], event[starred[k]][0], event[starred[k]][1]))
                        valid = 0;
            if (valid) maxn = max(maxn, __builtin_popcount(i));
        }
        cout << maxn << '\n';
    }
    return 0;
}
