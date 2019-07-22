// Maximizing the ICPC
// UVa ID: 11439
// Verdict: Accepted
// Submission Date: 2019-07-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 210;

int n, m;
vector<int> g[MAXN];
int father[MAXN], linked[MAXN], belong[MAXN], state[MAXN];

void initialize() { for (int i = 0; i <= n; i++) g[i].clear(); }
void addEdge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }

int lca(int u, int v)
{
    static int token = 0, tag[MAXN] = {};
    for (++token; ; swap(u, v)) {
        if (u == 0) continue;
        if (tag[u] == token) return u;
        tag[u] = token;
        u = belong[father[linked[u]]];
    }
}

void shrink(int u, int v, int p, queue<int> &q)
{
    while (belong[u] != p) {
        father[u] = v, v = linked[u];
        if (state[v] == 1) q.push(v), state[v] = 0;
        belong[u] = belong[v] = p, u = father[v];
    }
}

int bfs(int u)
{
    for (int i = 0; i <= n; i++) belong[i] = i;
    memset(state, -1, sizeof(state));
    queue<int> q;
    q.push(u);
    state[u] = 0;
    while (!q.empty()) {
        u = q.front(), q.pop();
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (state[v] == -1) {
                father[v] = u, state[v] = 1;
                if (!linked[v]) {
                    for (int prev; u; v = prev, u = father[v]) {
                        prev = linked[u];
                        linked[u] = v, linked[v] = u;
                    }
                    return 1;
                }
                q.push(linked[v]), state[linked[v]] = 0;
            } else if (state[v] == 0 && belong[v] != belong[u]) {
                int p = lca(u, v);
                shrink(v, u, p, q);
                shrink(u, v, p, q);
            }
        }
    }
    return 0;
}

int edmonds()
{
    memset(father, 0, sizeof(father));
    memset(linked, 0, sizeof(linked));
    int matches = 0;
    for (int i = 1; i <= n; i++) {
        if (!linked[i] && bfs(i))
            matches++;
    }
    return matches;
}

int main(int argc, char *argv[])
{
    int cases, N, ICPC[MAXN][MAXN];
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N;
        n = (1 << N);
        int low = 1, high = 0;
        for (int i = 1; i < n; i++)
            for (int j = i + 1; j <= n; j++)
            {
                cin >> ICPC[i][j];
                high = max(high, ICPC[i][j]);
            }
        int least = 0;
        while (low <= high)
        {
            int middle = (low + high) / 2;
            initialize();
            for (int i = 1; i < n; i++)
                for (int j = i + 1; j <= n; j++)
                    if (ICPC[i][j] >= middle)
                        addEdge(i, j);
            if (edmonds() == (n / 2))
            {
                least = middle;
                low = middle + 1;
            }
            else high = middle - 1;
        }
        cout << "Case " << cs << ": " << least << '\n';
    }
    return 0;
}
