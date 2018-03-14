// XYZZY
// UVa ID: 10557
// Verdict: Accepted
// Submission Date: 2018-02-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110, MAXE = 10010, INF = 0x3f3f3f3f;

struct edge { int u, v, weight; } edges[MAXE];

list<int> adjacent[MAXV];
int n, m, doors, room, energy, visited[MAXV], dist[MAXV], backup[MAXV];

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : adjacent[u])
        if (!visited[v])
            dfs(v);
}

bool updateDist()
{
    bool updated = false;
    for (int i = 0; i < m; i++)
    {
        energy = dist[edges[i].u] + edges[i].weight;
        if (energy >= 0) continue;
        if (dist[edges[i].v] > energy)
        {
            dist[edges[i].v] = energy;
            updated = true;
        }
    }
    return updated;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        m = 0;
        for (int i = 1; i <= n; i++) adjacent[i].clear();
        for (int i = 1; i <= n; i++)
        {
            cin >> energy >> doors;
            for (int j = 1; j <= doors; j++)
            {
                cin >> room;
                edges[m++] = edge{i, room, -energy};
                adjacent[i].push_back(room);
            }
        }

        // Check connectness.
        memset(visited, 0, sizeof(visited));
        dfs(1);
        if (!visited[n])
        {
            cout << "hopeless\n";
            continue;
        }

        // Bellman-Ford algorithm.
        for (int i = 1; i <= n; i++) dist[i] = INF;
        dist[1] = -100;
        for (int k = 1; k < n; k++)
            if (!updateDist())
                break;
        memcpy(backup, dist, sizeof(dist));
        updateDist();
        for (int i = 1; i <= n; i++)
            if (visited[i] && dist[i] < backup[i])
                dist[i] = -INF;
        updateDist();

        if (dist[n] < 0) cout << "winnable\n";
        else cout << "hopeless\n";
    }
    
	return 0;
}
