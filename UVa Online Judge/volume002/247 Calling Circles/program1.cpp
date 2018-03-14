// Calling Circles
// UVa ID: 247
// Verdict: Accepted
// Submission Date: 2017-10-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;
int visited[MAXV], n, cscc;
vector<list<int>> edges1(MAXV), edges2(MAXV);
vector<int> fn, scc;

int m;
map<string, int> indexer;
map<int, string> names;

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges1[u])
        if (!visited[v])
            dfs(v);
    fn.push_back(u);
}

void reverseGraph()
{
    for (int u = 1; u <= n; u++)
        for (auto v : edges1[u])
            edges2[v].push_back(u);
}

void rdfs(int u)
{
    visited[u] = 1;
    for (auto v : edges2[u])
        if (!visited[v])
            rdfs(v);
    scc.push_back(u);
}

void kosaraju()
{
    fn.clear();
    memset(visited, 0, sizeof visited);
    for (int u = 1; u <= n; u++)
        if (!visited[u])
            dfs(u);
    
    reverseGraph();

    cscc = 0;
    memset(visited, 0, sizeof visited);
    while (fn.size())
    {
        int u = fn.back();
        if (!visited[u]) 
        {
            cscc++, scc.clear();

            rdfs(u);

            for (int i = 0; i < scc.size(); i++)
            {
                if (i) cout << ", ";
                cout << names[scc[i]];
            }
            cout << '\n';
        }
        fn.pop_back();
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), cout.sync_with_stdio(false);

    int cases = 0;
    string name1, name2;

    while (cin >> n >> m, n > 0)
    {
        for (int u = 1; u <= n; u++) edges1[u].clear(), edges2[u].clear();

        n = 0;
        indexer.clear(), names.clear();
        for (int i = 1; i <= m; i++)
        {
            cin >> name1 >> name2;
            if (indexer.find(name1) == indexer.end())
            {
                indexer[name1] = ++n;
                names[n] = name1;
            }
            if (indexer.find(name2) == indexer.end())
            {
                indexer[name2] = ++n;
                names[n] = name2;
            }
            edges1[indexer[name1]].push_back(indexer[name2]);
        }

        if (cases++ > 0) cout << '\n';
        cout << "Calling circles for data set " << cases << ":\n";

        kosaraju();
    }

	return 0;
}
