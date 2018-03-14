// Ouroboros Snake
// UVa ID: 10040
// Verdict: Accepted
// Submission Date: 2017-08-14
// UVa Run Time: 2.260s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// It may lead to stack overflow if your computer owns a small memory.

#include <bits/stdc++.h>

using namespace std;

int n, k;
int used[1 << 21], sequence[1 << 21], top;
int bits, mask;

void dfs(int u)
{
    u = (u & mask) << 1;
    for (int v = 0; v <= 1; v++)
    {
        if (used[u + v]) continue;
        used[u + v] = 1;
        dfs(u + v);
        sequence[top++] = u + v;
    }
}

int main(int argc, char *argv[])
{
    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> k;
        top = 0, bits = 1 << n, mask = (1 << (n - 1)) - 1;
        memset(used, 0, sizeof(int) * bits);
        dfs(0);
        cout << sequence[bits - 1 - k] << '\n';
    }

    return 0;
}
