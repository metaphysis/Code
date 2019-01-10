const int MAXV = 110;
int visited[MAXV], n, cscc;
vector<list<int>> g1(MAXV), g2(MAXV);
vector<int> fn, scc;

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : g1[u])
        if (!visited[v])
            dfs(v);
    fn.push_back(u);
}

void reverseEdge()
{
    for (int u = 1; u <= n; u++)
        for (auto v : g1[u])
            g2[v].push_back(u);
}

void rdfs(int u)
{
    visited[u] = 1;
    for (auto v : g2[u])
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

    reverseEdge();

    cscc = 0;
    memset(visited, 0, sizeof visited);
    while (fn.size())
    {
        int u = fn.back();
        if (!visited[u]) 
        {
            cscc++, scc.clear();
            rdfs(u);
            cout << "cscc = " << cscc;
            for (auto v : scc) cout << ' ' << v;
            cout << '\n';
        }
        fn.pop_back();
    }
}
