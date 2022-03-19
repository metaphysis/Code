const int MAXV = 110;

int visited[MAXV];
vector<list<int>> g(MAXV);
stack<int> ts;

// 将DFS过程中发现的顶点按遍历完成时间入栈，从栈顶到栈底的顺序即为一种可行的拓扑排序。
void dfs(int u)
{
    visited[u] = 1;
    for (auto v : g[u])
        if (!visited[v])
            dfs(v);
    ts.push(u);
}

void topologicalSort()
{
    // 反复调用DFS过程，直到所有顶点为已访问状态。
    while (!ts.empty()) ts.pop();
    memset(visited, 0, sizeof visited);
    for (int u = 1; u <= n; u++)
        if (!visited[u])
            dfs(u);
}
