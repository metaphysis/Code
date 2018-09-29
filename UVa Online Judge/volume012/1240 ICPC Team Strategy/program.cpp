// ICPC Team Strategy
// UVa ID: 1240
// Verdict: Accepted
// Submission Date: 2018-09-29
// UVa Run Time: 0.470s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, Ai[4][16], cache[1 << 12][4][300];

int dfs(int mask, int student, int minutes)
{
    if (~cache[mask][student][minutes]) return cache[mask][student][minutes];
    int r = 0;
    for (int bit = 0; bit < N; bit++)
    {
        if (mask & (1 << bit)) continue;
        if (student)
        {
            for (int s = 1; s <= 3; s++)
                if (s != student && minutes + Ai[s][bit] <= 280)
                    r = max(r, 1 + dfs(mask | (1 << bit), s, minutes + Ai[s][bit]));
        }
        else
        {
            for (int s = 1; s <= 3; s++)
                if (minutes + Ai[s][bit] <= 280)
                r = max(r, 1 + dfs(mask | (1 << bit), s, minutes + Ai[s][bit]));
        }
    }
    return cache[mask][student][minutes] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N;
        for (int i = 1; i <= 3; i++)
            for (int j = 0; j < N; j++)
                cin >> Ai[i][j];
        for (int i = 0; i < (1 << N); i++)
            for (int j = 0; j <= 3; j++)
                for (int k = 0; k <= 280; k++)
                    cache[i][j][k] = -1;
        cout << dfs(0, 0, 0) << '\n';
    }

    return 0;
}
