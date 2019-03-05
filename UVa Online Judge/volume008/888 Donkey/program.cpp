// Donkey
// UVa ID: 888
// Verdict: TLE
// Submission Date: 2019-03-05
// UVa Run Time: 3.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define GET(X, Y) ((X & (0x1F << (5 * Y))) >> (5 * Y))

int M, N;
double dp[4][1 << 20];

int getMask(int who, int die, int mask)
{
    int river = GET(mask, who) + die;
    while (true)
    {
        bool conflict = false;
        for (int i = 0; i < N; i++)
            if (river == GET(mask, i))
            {
                river++;
                conflict = true;
                break;
            }
        if (!conflict) break;
    }
    return (mask & ~(0x1F << (5 * who))) | (river << (5 * who));
}

double dfs(int who, int mask)
{
    if (GET(mask, 0) > M) return 1.0;
    for (int i = 1; i < N; i++) if (GET(mask, i) > M) return 0.0;
    if (dp[who][mask] >= 0) return dp[who][mask];
    double r = 0.0;
    for (int die = 1; die <= 6; die++)
        r += dfs((who + 1) % N, getMask(who, die, mask)) / 6;
    return dp[who][mask] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Game " << cs << ":the probability that player 1 wins = ";
        cin >> M >> N;
        int river, mask = 0, who;
        for (int i = 0; i < N; i++)
        {
            cin >> river;
            mask |= (river << (5 * i));
        }
        cin >> who;
        if (N == 1) cout << "1.000\n";
        else
        {
            for (int i = 0; i < N; i++)
                for (int j = 0; j < (1 << (5 * N)); j++)
                    dp[i][j] = -1;
            cout << fixed << setprecision(3) << dfs(who - 1, mask) << '\n';
        }
    }

    return 0;
}
