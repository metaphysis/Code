// A Funny Stone Game
// UVa ID: 1378
// Verdict: Accepted
// Submission Date: 2019-03-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, stones[32], sg[32];

int dfs(int i)
{
    if (i == n - 1) return sg[i] = 0;
    if (sg[i] >= 0) return sg[i];
    set<int> visited;
    for (int j = i + 1; j < n; j++)
        for (int k = j; k < n; k++)
            visited.insert(dfs(j) ^ dfs(k));
    int grundy = 0;
    while (visited.find(grundy) != visited.end()) grundy++;
    return sg[i] = grundy;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++) cin >> stones[i];
        memset(sg, -1, sizeof(sg));
        dfs(0);
        int mex = 0;
        for (int i = 0; i < n; i++)
            if (stones[i] % 2)
                mex ^= sg[i];
        cout << "Game " << ++cases << ": ";
        if (mex)
        {
            for (int i = 0; i < n; i++)
            {
                if (!stones[i]) continue;
                for (int j = i + 1; j < n; j++)
                    for (int k = j; k < n; k++)
                    {
                        int mex = 0;
                        for (int x = 0; x < n; x++)
                            if ((stones[x] - (x == i) + (x == j) + (x == k)) % 2)
                                mex ^= sg[x];
                        if (mex == 0)
                        {
                            cout << i << ' ' << j << ' ' << k << '\n';
                            goto out;
                        }
                    }
            }
        }
        else cout << "-1 -1 -1\n";
        out: continue;
    }

    return 0;
}
