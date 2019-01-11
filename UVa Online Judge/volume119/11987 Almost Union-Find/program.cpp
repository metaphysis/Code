// Almost Union-Find
// UVa ID: 11987
// Verdict: Accepted
// Submission Date: 2019-01-11
// UVa Run Time: 0.070s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 200020;

int parent[MAXV], ranks[MAXV], idx[MAXV], cnt;
long long sum[MAXV];

void makeSet(int n)
{
    for (int i = 1; i <= n; i++) parent[i] = i, ranks[i] = 1, sum[i] = i, idx[i] = i;
}

int findSet(int x)
{
    return (x == parent[x] ? x : parent[x] = findSet(parent[x]));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m, c, u, v;
    while (cin >> n >> m)
    {
        makeSet(n);
        cnt = n + 1;
        for (int i = 1; i <= m; i++)
        {
            cin >> c;
            if (c == 1)
            {
                cin >> u >> v;
                int p1 = findSet(idx[u]), p2 = findSet(idx[v]);
                if (p1 == p2) continue;
                parent[p1] = p2;
                ranks[p2] += ranks[p1], sum[p2] += sum[p1];
            }
            else if (c == 2)
            {
                cin >> u >> v;
                int p1 = findSet(idx[u]), p2 = findSet(idx[v]);
                if (p1 == p2) continue;
                ranks[p1] -= 1, sum[p1] -= u;
                idx[u] = cnt++;
                parent[idx[u]] = p2;
                ranks[p2] += 1, sum[p2] += u;
            }
            else
            {
                cin >> u;
                cout << ranks[findSet(idx[u])] << ' ' << sum[findSet(idx[u])] << '\n';
            }
        }
    }

    return 0;
}
