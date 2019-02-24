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

vector<edge> g[MAXV];

int n, m;
int parent[MAXV];

void makeSet()
{
    for (int i = 0; i < n; i++) parent[i] = i;
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

void addEdge(int i)
{
    edge e = edges[i];
    g[e.u].push_back(edge(i, e.v, e.w));
    g[e.v].push_back(edge(i, e.u, e.w));
}

int choose[MAXE], best[MAXV], candidate[MAXV], linkTo[MAXV];
void dfs(int father, int u)
{
    for (auto e : g[u])
    {
        if (!choose[e.u]) continue;
        if (e.v == father) continue;
        if (u)
        {
            best[e.v] = e.w;
            candidate[e.v] = e.u;
            if (best[u] > best[e.v])
            {
                best[e.v] = best[u];
                candidate[e.v] = candidate[u];
            }
        }
        else best[e.v] = -INF;
        dfs(u, e.v);
    }
}

int rmst(int k)
{
    memset(choose, 0, sizeof(choose));
    memset(linkTo, -1, sizeof(linkTo));

    makeSet();
    sort(edges, edges + m);

    for (int i = 0; i < m; i++)
    {
        if (!edges[i].u) continue;
        int x = findSet(edges[i].u), y = findSet(edges[i].v);
        if (x == y) continue;
        parent[x] = y;
        choose[i] = 1;
    }

    int components = 0;
    best[0] = INF;
    for (int i = 1; i < n; i++)
        if (findSet(i) == i)
        {
            components++;
            best[i] = INF;
        }
    if (components > k) return INF;

    for (int i = 0; i < m; i++)
    {
        if (edges[i].u) continue;
        linkTo[edges[i].v] = i;
        int x = findSet(edges[i].v);
        if (edges[i].w < best[x])
        {
            best[x] = edges[i].w;
            candidate[x] = i;
        }
    }

    for (int i = 1; i < n; i++)
        if (findSet(i) == i)
        {
            if (best[i] == INF) return INF;
            choose[candidate[i]] = 1;
        }

    for (int i = 0; i < n; i++)
        g[i].clear();
    for (int i = 0; i < m; i++)
        if (choose[i])
            addEdge(i);

    while (components < k)
    {
        dfs(-1, 0);
        int tmpBest = INF, tmpCandidate;
        for (int i = 1; i < n; i++)
        {
            if (linkTo[i] == -1 || best[i] == -INF) continue;
            int beta = edges[linkTo[i]].w - best[i];
            if (beta < tmpBest)
            {
                tmpBest = beta;
                tmpCandidate = i;
            }
        }
        //if (tmpBest == INF) return INF;
        if (tmpBest >= 0) break;
        choose[candidate[tmpCandidate]] = 0;
        choose[linkTo[tmpCandidate]] = 1;
        addEdge(linkTo[tmpCandidate]);
        components++;
    }

    int sumOfWeight = 0;
    for (int i = 0; i < m; i++)
        if (choose[i])
            sumOfWeight += edges[i].w;
    return sumOfWeight;
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
        cout << "Total miles driven: " << rmst(s) << '\n';
    }

    return 0;
}
