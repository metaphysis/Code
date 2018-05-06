// Wedding
// UVa ID: 11294
// Verdict: Accepted
// Submission Date: 2018-05-05
// UVa Run Time: 0.660s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 256;

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
        while (true)
        {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            if (u == v) break;
        }
        cscc++;
    }
}


int n, m;
vector<int> value;
vector<vector<int>> components;

int getValue(int idx)
{
    int x = (idx & 1) ? (idx ^ 1) : idx;
    if (value[x] == -1) return -1;
    return (idx & 1) ? !value[x] : value[x];
}

void assignValue()
{
    components.assign(cscc, vector<int>());
    for (int i = 0; i < 4 * n; i++)
        components[scc[i]].push_back(i);

    value.assign(4 * n, -1);
    for (int i = 0; i < cscc; i++)
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
            if (u & 1)
                value[u ^ 1] = !boolean;
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
        initialize();

        // Index of Groom: 0 to (n - 1), index of bride: n to (2 * n - 1)

        // Groom must be FALSE, bride must be TRUE.
        edges[0].push_back(1);
        edges[2 * n + 1].push_back(2 * n);

        // For other couples, one must be TRUE, another must be FALSE.
        for (int i = 1; i < n; i++)
        {
            int x = 2 * i, y = 2 * (i + n);
            edges[x ^ 1].push_back(y);
            edges[y ^ 1].push_back(x);
            edges[x].push_back(y ^ 1);
            edges[y].push_back(x ^ 1);
        }

        // Avoid to see both members with adulterous relationships.
        // Two must not be FALSE at same time.
        string p1, p2;
        for (int i = 0; i < m; i++)
        {
            cin >> p1 >> p2;
            bool h1 = p1.back() == 'h';
            bool h2 = p2.back() == 'h';
            p1.pop_back();
            p2.pop_back();
            int x = stoi(p1), y = stoi(p2);
            if (!h1) x += n;
            if (!h2) y += n;
            x *= 2, y *= 2;
            edges[x ^ 1].push_back(y);
            edges[y ^ 1].push_back(x);
        }

        for (int i = 0; i < 4 * n; i++)
            if (!dfn[i])
                tarjan(i);

        bool flag = true;
        for (int i = 0; i < 4 * n; i += 2)
            if (scc[i] == scc[i ^ 1])
            {
                flag = false;
                break;
            }

        if (!flag)
        {
            cout << "bad luck" << '\n';
            continue;
        }

        assignValue();

        for (int i = 1; i < n; i++)
        {
            if (i > 1) cout << ' ';
            cout << i;
            if (value[2 * i]) cout << 'h';
            else cout << 'w';
        }
        cout << '\n';
    }

    return 0;
}
