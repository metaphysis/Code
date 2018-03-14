// As Long as I Learn, I Live
// UVa ID: 12376
// Verdict: Accepted
// Submission Date: 2018-01-29
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, units[110], edges[110], n, m, u, v, t;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        memset(edges, -1, sizeof(edges));
        for (int i = 0; i < n; i++)
            cin >> units[i];
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v;
            if (edges[u] < 0 || units[v] > units[edges[u]])
                edges[u] = v;
        }
        u = t = 0;
        do
        {
            u = edges[u];
            t += units[u];
        } while (edges[u] >= 0);
        cout << "Case " << c << ": " << t << ' ' << u << '\n';
    }

    return 0;
}
