// Astronauts
// UVa ID: 1391
// Verdict: Accepted
// Submission Date: 2018-05-05
// UVa Run Time: 0.660s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 200010, YOUNG = 0, SENIOR = 1;

int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
vector<list<int>> edges(MAXV);
stack<int> s;

void initialize()
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    for (int u = 0; u < MAXV; u++) edges[u].clear();
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

int n, m;
vector<int> value;
vector<vector<int>> components;

int getValue(int idx)
{
    int x = idx > n ? idx - n : idx;
    if (value[x] == -1) return -1;
    return idx > n ? !value[x] : value[x];
}

void setValue()
{
    components.assign(cscc + 1, vector<int>());
    for (int i = 0; i < 2 * n; i++)
        components[scc[i]].push_back(i);

    value.assign(n, -1);
    for (int i = 1; i <= cscc; i++)
    {
        int boolean = 1;
        for (auto u : components[i])
        {
            if (getValue(u) == 0) boolean = 0;
            for (auto v : edges[u])
                if (getValue(v) == 0)
                {
                    boolean = 0;
                    break;
                }
            if (boolean == 0) break;
        }
        for (auto u : components[i])
            if (u > n)
                value[u - n] = !boolean;
            else
                value[u] = boolean;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int ages[MAXV];
    while (cin >> n >> m, n > 0)
    {
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> ages[i];
            sum += ages[i];
        }

        initialize();

        int x, y, b1, b2;
        for (int i = 1; i <= m; i++)
        {
            cin >> x >> y;
            x--, y--;
            if (x > y) swap(x, y);
            if (ages[x] * n >= sum) b1 = SENIOR;
            else b1 = YOUNG;
            if (ages[y] * n >= sum) b2 = SENIOR;
            else b2 = YOUNG;

            if (b1 == b2)
            {
                // One is TRUE, another is FALSE.
                // (b1 or b2) and (!b1 or !b2)
                edges[x + n].push_back(y);
                edges[y + n].push_back(x);
                edges[x].push_back(y + n);
                edges[y].push_back(x + n);
            }
            else
            {
                // Two cann't both TRUE.
                // (!b1 or !b2)
                edges[x].push_back(y + n);
                edges[y].push_back(x + n);
            }
        }

        for (int i = 0; i < 2 * n; i++)
            if (!dfn[i])
                tarjan(i);

        bool flag = true;
        for (int i = 0; i < n; i++)
            if (scc[i] == scc[i + n])
            {
                flag = false;
                break;
            }

        if (!flag)
        {
            cout << "No solution." << '\n';
            continue;
        }

        setValue();

        for (int i = 0; i < n; i++)
            if (value[i]) cout << 'C' << '\n';
            else
            {
                if (ages[i] * n >= sum) cout << 'A' << '\n';
                else cout << 'B' << '\n';
            }
    }

    return 0;
}
