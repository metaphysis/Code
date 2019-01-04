// The Traveling Judges Problem
// UVa ID: 1040
// Verdict: Accepted
// Submission Date: 2019-01-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 32, MAXE = 1000, INF = 0x7f7f7f7f;

struct edge {
    int u, v, weight;
    edge (int u = 0, int v = 0, int weight = 0): u(u), v(v), weight(weight) {}
    bool operator<(const edge &e) const { return weight < e.weight; }
} edges[MAXE];


int NC, DC, NR, NJ, NJ_CITY[MAXV];
int dist[MAXV], father[MAXV], visited[MAXV], g[MAXV][MAXV];

int parent[MAXV], ranks[MAXV];

void makeSet()
{
    for (int i = 0; i < NC; i++) parent[i] = i, ranks[i] = 0;
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

bool unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
        return true;
    }
    return false;
}

bool better(int x, int y)
{
    int bitx = __builtin_popcount(x);
    int bity = __builtin_popcount(y);
    if (bitx != bity) return bitx < bity;
    for (int i = 0; i < NC; i++)
        if ((x & (1 << i)) != (y & (1 << i)))
            return x & (1 << i);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;

    // All index start from 0.
    while (cin >> NC)
    {
        if (NC == -1) break;
        cin >> DC >> NR;
        DC--;
        for (int i = 0, u, v, w; i < NR; i++)
        {
            cin >> u >> v >> w;
            u--, v--;
            edges[i] = edge(u, v, w);
        }
        
        int city_mask = 0;
        cin >> NJ;
        for (int i = 0; i < NJ; i++)
        {
            cin >> NJ_CITY[i];
            NJ_CITY[i]--;
            city_mask |= (1 << NJ_CITY[i]);
        }
        city_mask |= (1 << DC);

        sort(edges, edges + NR);

        int best_mask = (1 << NC) - 1, best_city = NC, best_miles = INF;
        for (int i = 0; i < (1 << NC); i++)
        {
            if ((i & city_mask) != city_mask) continue;
            if (__builtin_popcount(i) > best_city) continue;

            // Kruskal.
            int miles = 0, cntOfMerged = 0;
            makeSet();
            for (int j = 0; j < NR; j++)
            {
                if ((i & (1 << edges[j].u)) && (i & (1 << edges[j].v)))
                    if (unionSet(edges[j].u, edges[j].v)) {
                        cntOfMerged++;
                        miles += edges[j].weight;
                    }
            }
            if (cntOfMerged + 1 != __builtin_popcount(i)) continue;

            if (miles < best_miles || (miles == best_miles && better(i, best_mask)))
            {
                best_miles = miles;
                best_city = __builtin_popcount(i);
                best_mask = i;
            }
        }
        
        // Get all edges in MST.
        memset(g, 0, sizeof(g));
        makeSet();
        for (int j = 0; j < NR; j++)
        {
            if ((best_mask & (1 << edges[j].u)) && (best_mask & (1 << edges[j].v)))
                if (unionSet(edges[j].u, edges[j].v))
                    g[edges[j].u][edges[j].v] = g[edges[j].v][edges[j].u] = 1;
        }

        // BFS to get the path.
        for (int i = 0; i < NC; i++) father[i] = -1, visited[i] = 0;
        queue<int> q;
        visited[DC] = 1;
        father[DC] = DC;
        q.push(DC);

        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (int v = 0; v < NC; v++)
                if (g[u][v] && !visited[v])
                {
                    father[v] = u;
                    visited[v] = 1;
                    q.push(v);
                }
        }
        
        cout << "Case " << ++cases << ": distance = " << best_miles << '\n';
        for (int i = 0; i < NJ; i++)
        {
            int s = NJ_CITY[i];
            cout << "   " << (s + 1);
            while (s != DC)
            {
                s = father[s];
                cout << '-' << (s + 1);
            }
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
