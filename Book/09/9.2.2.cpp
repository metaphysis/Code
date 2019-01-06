#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, MAXE = 1000010;

struct edge {
    int u, v, weight;
    
    bool operator<(const edge &e) const
    {
        if (u == e.u) {
            if (v == e.v) return weight < e.weight;
            else return v < e.v;
        }
        else
            return u < e.u;
    }
} g[MAXE];

int n, m, head[MAXV];

int main(int argc, char *argv[])
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        cin >> g[i].u >> g[i].v >> g[i].weight;

    sort(g, g + m);

    memset(head, -1, sizeof(head));

    head[g[0].u] = 0;
    for (int i = 0; i < m; i++)
        if (g[i - 1].u != g[i].u)
            head[g[i].u] = i;

    for (int i = 0; i < n; i++)
        for (int j = head[i]; g[j].u == i; j++)
            cout << g[j].u << ' ' << g[j].v << ' ' << g[j].weight << '\n';

    return 0;
}
