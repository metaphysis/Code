// Picnic Planning
// UVa ID: 1537
// Verdict: Accepted
// Submission Date: 2019-02-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110, MAXE = 10010, INF = 0x7f7f7f7f;

struct edge
{
    int u, v, w;
    edge (int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
    bool operator<(const edge &e) const { return w < e.w; }
} edges[MAXE];

vector<edge> g[MAXV], ue;

int n, m;
int parent[MAXV];

void makeSet()
{
    for (int i = 0; i < n; i++) parent[i] = i;
}

int findSet(int x)
{
    return parent[x] == x ? x : parent[x] = findSet(parent[x]);
}

bool unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
    if (x == y) return false;
    parent[x] = y;
    return true;
}

void addEdge(int idx)
{
    edge e = edges[idx];
    g[e.u].push_back(edge(idx, e.v, e.w));
    g[e.v].push_back(edge(idx, e.u, e.w));
}

int chosen[MAXE], connected[MAXV], longest[MAXV], link[MAXV], idx[MAXV];

void dfs(int father, int u)
{
    for (auto e : g[u])
    {
        if (!chosen[e.u]) continue;
        if (e.v == father) continue;
        if (~father)
        {
            longest[e.v] = e.w;
            link[e.v] = e.u;
            if (longest[u] > longest[e.v])
            {
                longest[e.v] = longest[u];
                link[e.v] = link[u];
            }
        } else longest[e.v] = -INF;
        dfs(u, e.v);
    }
}

int kdbmst(int u, int k)
{
    memset(chosen, 0, sizeof(chosen));
    memset(idx, -1, sizeof(idx));

    makeSet();
    sort(edges, edges + m);

    ue.clear();
    for (int i = 0; i < m; i++)
    {
        if (edges[i].u == u) {
            edge e = edges[i];
            ue.push_back(edge(i, e.v, e.w));
            continue;
        }
        if (unionSet(edges[i].u, edges[i].v)) chosen[i] = 1;
    }

    int components = 0;
    connected[u] = 0;
    for (int i = 0; i < n; i++)
        if (i != u && findSet(i) == i)
        {
            components++;
            connected[i] = 0;
        }
    if (components > k) return INF;

    sort(ue.begin(), ue.end());
    for (auto e : ue)
    {
        int eid = e.u, scc = findSet(e.v);
        idx[e.v] = eid;
        if (!connected[scc]) connected[scc] = chosen[eid] = 1;
    }

    for (int i = 0; i < n; i++)
        if (i != u && findSet(i) == i)
            if (!connected[i])
                return INF;
    
    for (int i = 0; i < n; i++) g[i].clear();
    for (int i = 0; i < m; i++)
        if (chosen[i])
            addEdge(i);

    while (components < k)
    {
        dfs(-1, 0);
        int delta = INF, selected = INF;
        for (auto e : ue)
        {
            if (chosen[e.u]) continue;
            if (e.w - longest[e.v] < delta)
            {
                delta = e.w - longest[e.v];
                selected = e.v;
            }
        }
        if (delta >= 0) break;
        chosen[link[selected]] = 0;
        chosen[idx[selected]] = 1;
        addEdge(idx[selected]);
        components++;
    }

    int sum = 0;
    for (int i = 0; i < m; i++)
        if (chosen[i])
            sum += edges[i].w;
    return sum;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, s;
    map<string, int> names;
    string name1, name2;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> m;
        names.clear();
        n = 0;
        names["Park"] = n++;
        for (int i = 0, dist; i < m; i++)
        {
            cin >> name1 >> name2 >> dist;
            if (name2 == "Park") swap(name1, name2);
            if (names.find(name1) == names.end()) names[name1] = n++;
            if (names.find(name2) == names.end()) names[name2] = n++;
            edges[i] = edge(names[name1], names[name2], dist);
        }
        cin >> s;
        if (cs > 1) cout << '\n';
        cout << "Total miles driven: " << kdbmst(0, s) << '\n';
    }

    return 0;
}
