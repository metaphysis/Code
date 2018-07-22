// Square
// UVa ID: 10364
// Verdict: Accepted
// Submission Date: 2018-07-22
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, stick[22], size, ONES, marked[(1 << 20) + 10] = {};

bool dfs(int used, int depth, int side)
{
    if (marked[used]) return false;
    if (side == size) return dfs(used, depth + 1, 0);
    if (depth == 4) return true;
    marked[used] = 1;
    int available = ONES & (~used), next, bit;
    while (available)
    {
        next = available & (~available + 1);
        available ^= next;
        bit = __builtin_ctz(next);
        if (side + stick[bit] > size) continue;
        if (bit && stick[bit] == stick[bit - 1] && !(used & (next >> 1))) continue;
        if (dfs(used | next, depth, side + stick[bit])) return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        int side = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> stick[i];
            side += stick[i];
        }
        if (side % 4 != 0)
        {
            cout << "no\n";
            continue;
        }
        size = side / 4;
        sort(stick, stick + n, greater<int>());
        if (stick[0] > size)
        {
            cout << "no\n";
            continue;
        }
        ONES = (1 << n) - 1;
        memset(marked, 0, (1 << n) * sizeof(int));
        cout << (dfs(0, 0, 0) ? "yes" : "no") << '\n';
    }

    return 0;
}
