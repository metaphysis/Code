// Trust groups
// UVa ID: 11709
// Verdict: Accepted
// Submission Date: 2017-10-17
// UVa Run Time: 0.210s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010;

int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
stack<int> s; vector<list<int>> edges(MAXV);
int P, T;

void initialize()
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    for (int u = 1; u <= P; u++) edges[u].clear();
    memset(dfn, 0, sizeof(dfn)); memset(scc, 0, sizeof(scc));
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime; s.push(u);
    for (auto v : edges[u])
    {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++cscc;
        while (true)
        {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            if (u == v) break;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> P >> T, P > 0)
    {
        map<string, int> indexer;
        cin.ignore(1024, '\n');
        
        string line;
        int cnt = 1;
        for (int i = 0; i < P; i++)
        {
            getline(cin, line);
            indexer[line] = cnt++;
        }

        initialize();

        string name1, name2;
        for (int i = 0; i < T; i++)
        {
            getline(cin, name1);
            getline(cin, name2);
            edges[indexer[name1]].push_back(indexer[name2]);
        }

        for (int u = 1; u <= P; u++)
            if (!dfn[u])
                tarjan(u);

        cout << cscc << '\n';
    }
    
    return 0;
}
