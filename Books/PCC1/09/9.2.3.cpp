#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010;

int n, m;

vector<vector<int>> g(MAXV + 1);
// vector<set<int>> g(MAXV + 1);
// list<list<int>> g(MAXV + 1);
    
int main(int argc, char *argv[])
{
    cin >> n >> m;
    for (int i = 0, u, v; i < m; i++)
    {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < n; i++)
        if (g[i].size() > 0)
        {
            cout << i;
            for (int j = 0; j < g[i].size(); j++)
                cout << ' ' << g[i][j];
            cout << '\n';
        }

    return 0;
}
