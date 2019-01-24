// Color a Tree
// UVa ID: 1205
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010;

int N, R, cost[MAXV];
vector<int> g[MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> R)
    {
        if (N == 0) break;
        for (int i = 1; i <= N; i++) cin >> cost[i];
        for (int i = 1; i <= N; i++) g[i].clear();
        for (int i = 1, u, v; i < N; i++)
        {
            cin >> u >> v;
            g[u].push_back(v);
        }
    }

    return 0;
}
