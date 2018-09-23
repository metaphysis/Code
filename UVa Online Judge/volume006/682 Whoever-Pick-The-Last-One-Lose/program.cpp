// Whoever-Pick-The-Last-One-Lose
// UVa ID: 682
// Verdict: Accepted
// Submission Date: 2018-09-23
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define SET(T, x) (T[(x) >> 5] |= (1 << ((x) & 31)))
#define GET(T, x) ((T[(x) >> 5] >> ((x) & 31)) & 1)

int cache[1 << 25];

int dfs(int mask)
{
    if (~cache[mask]) return cache[mask];
    for (int b = 0; b < 25; b++)
        if (mask & (1 << b))
        {
            int next_mask = mask;
            int ii = b / 5, jj = b % 5;
            while (jj < 5)
            {
                if (!(mask & (1 << (ii * 5 + jj)))) break;
                next_mask ^= (1 << (ii * 5 + jj));
                if (!dfs(next_mask)) return cache[mask] = 1;
                jj++;
            }
            next_mask = mask;
            ii = b / 5, jj = b % 5;
            while (ii < 5)
            {
                if (!(mask & (1 << (ii * 5 + jj)))) break;
                next_mask ^= (1 << (ii * 5 + jj));
                if (!dfs(next_mask)) return cache[mask] = 1;
                ii++;
            }
        }
    
    return cache[mask] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(cache, -1, sizeof(cache));
    cache[0] = 1;

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int mask = 0, bit;
        for (int i = 0; i < 25; i++)
        {
            cin >> bit;
            mask |= (bit << i);
        }
        cout << (dfs(mask) ? "winning" : "losing") << '\n';
    }

    return 0;
}
