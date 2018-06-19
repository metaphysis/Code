// Stones
// UVa ID: 12469
// Verdict: Accepted
// Submission Date: 2018-06-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cache[1001][1001];

int dfs(int n, int m)
{
    if (~cache[n][m]) return cache[n][m];
    if (m >= n) return cache[n][m] = 1;
    int next = n / 3;
    if (n % 3 == 0) next--;
    next = min(m, next);
    for (int i = 1; i <= next; i++)
        if (!dfs(n - i, 2 * i)) return cache[n][m] = 1;
    return cache[n][m] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    memset(cache, -1, sizeof(cache));
    while (cin >> n, n > 0)
        cout << (dfs(n, n - 1) ? "Alicia" : "Roberto") << '\n';

    return 0;
}
