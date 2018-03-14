// Alternative Arborescence
// UVa ID: 11307
// Verdict: Accepted
// Submission Date: 2018-02-25
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10010, INF = 0x3f3f3f3f, COLOR = 6;

list<int> edges[MAXV];
int n, sum[MAXV][8], indeg[MAXV];
char seperator;

void dfs(int u, int up)
{
    if (sum[u][up] != INF) return;
    for (int c = 1; c <= COLOR; c++)
    {
        if (c == up) continue;
        int s = c;
        for (auto v : edges[u])
        {
            dfs(v, c);
            s += sum[v][c];
        }
        sum[u][up] = min(sum[u][up], s);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++) edges[i].clear();
        memset(indeg, 0, sizeof(indeg));
        cin.ignore(1024, '\n');
        for (int i = 1, u, v; i <= n; i++)
        {
            getline(cin, line);
            istringstream iss(line);
            iss >> u >> seperator;
            while (iss >> v)
            {
                edges[u].push_back(v);
                indeg[v] = 1;
            }
        }

        // find the node with zero degree as root of tree.
        int root = -1;
        for (int i = 0; i < n; i++)
            if (indeg[i] == 0)
            {
                root = i;
                break;
            }

        // DP.
        memset(sum, 0x3f, sizeof(sum));
        dfs(root, 0);

        cout << sum[root][0] << '\n';
    }

    return 0;
}
