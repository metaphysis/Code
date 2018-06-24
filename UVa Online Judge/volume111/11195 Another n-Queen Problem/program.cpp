// Another n-Queen Problem
// UVa ID: 11195
// Verdict: Accepted
// Submission Date: 2018-06-24
// UVa Run Time: 1.330s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n;
char chess[16][16];

int dfs(int d, int L, int M, int R)
{
    if (d >= n) return 1;
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (chess[d][i] != '*' && ((1 << i) & (L | M | R)) == 0)
            cnt += dfs(d + 1, (L | (1 << i)) << 1, M | (1 << i), (R | (1 << i)) >> 1);
    return cnt;
}

int main(int argc, char *argv[])
{
    int cases = 0;

    while (cin >> n, n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> chess[i][j];
        cout << "Case " << ++cases << ": " << dfs(0, 0, 0, 0) << '\n';
    }

    return 0;
}
