// Pebble Solitaire
// UVa ID: 10651
// Verdict: Accepted
// Submission Date: 2018-09-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cache[1 << 12];

int dfs(int n, int pebbles)
{
    if (~cache[n]) return cache[n];
    int minimal = pebbles;
    for (int i = 0; i < 12; i++)
    {
        if (i < 10 && !(n & (1 << i)) && (n & (1 << (i + 1))) && (n & (1 << (i + 2))))
            minimal = min(minimal, dfs((n | (1 << i)) ^ ((1 << (i + 1)) | (1 << (i + 2))), pebbles - 1));
        if (i >= 2 && !(n & (1 << i)) && (n & (1 << (i - 1))) && (n & (1 << (i - 2))))
            minimal = min(minimal, dfs((n | (1 << i)) ^ ((1 << (i - 1)) | (1 << (i - 2))), pebbles - 1));
    }
    return cache[n] = minimal;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;

    memset(cache, -1, sizeof(cache));
    for (int cs = 1; cs <= cases; cs++)
    {
        char letter;
        int n = 0, pebbles = 0;
        for (int i = 0; i < 12; i++)
        {
            cin >> letter;
            if (letter == 'o')
            {
                n |= (1 << i);
                pebbles++;
            }
        }
        cout << dfs(n, pebbles) << '\n';
    }

    return 0;
}
