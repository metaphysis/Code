// K-Graph Oddity
// UVa ID: 1613
// Verdict: Accepted
// Submission Date: 2017-09-27
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10000;

vector<int> edges[MAXV], colored(MAXV, 0), used(MAXV, 0);

int k;

void dfs(int u)
{
    for (auto v : edges[u]) used[colored[v]] = u;

    for (int color = 1; color <= k; color++)
        if (used[color] != u)
        {
            colored[u] = color;
            break;
        }

    for (auto v : edges[u])
        if (!colored[v])
            dfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, m, a, b, cases = 0;

    while (cin >> n >> m)
    {
        for (int i = 1; i <= n; i++)
            edges[i].clear();

        int degree[MAXV] = {0};
        for (int i = 1; i <= m; i++)
        {
            cin >> a >> b;
            edges[a].push_back(b);
            edges[b].push_back(a);
            degree[a]++, degree[b]++;
        }

        k = *max_element(degree, degree + MAXV) | 1;
        fill(colored.begin(), colored.end(), 0);
        fill(used.begin(), used.end(), 0);

        dfs(1);

        if (cases++) cout << '\n';

        cout << k << '\n';
        for (int i = 1; i <= n; i++)
            cout << colored[i] << '\n';
    }
    
	return 0;
}
