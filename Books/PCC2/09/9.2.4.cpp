#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, MAXE = 1000010;

struct edge { int u, v, weight, next; } g[MAXE];

int n, m;
int head[MAXV], idx;

int main(int argc, char *argv[])
{
    idx = 0;
    memset(head, -1, sizeof(head));
    
    cin >> n >> m;

    for (int i = 0, u, v, weight; i < m; i++)
    {
        cin >> u >> v >> weight;
        
        g[idx] = edge{u, v, weight, head[u]};
        head[u] = idx++;
        
        g[idx] = edge{v, u, weight, head[v]};
        head[v] = idx++;
    }

    for (int i = 0; i < n; i++)
        for (int j = head[i]; ~j; j = g[j].next)
            cout << g[j].u << ' ' << g[j].v << ' ' << g[j].weight << '\n';

    return 0;
}
