// A Plug for UNIX
// UVa ID: 753
// Verdict: Accepted
// Submission Date: 2017-09-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7fffffff;

struct arc
{
    int u, v, capacity, residual, next;
};

class EdmondsKarp
{
private:
    arc *arcs;
    int vertices, indexer, source, sink, *link, *parent, *visited;

    bool bfs()
    {
        memset(parent, 0xff, vertices * sizeof(int));
        memset(visited, 0, vertices * sizeof(int));

        queue<int> q; q.push(source);
        visited[source] = 1;

        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (int i = link[u]; i != -1; i = arcs[i].next)
                if (!visited[arcs[i].v] && arcs[i].residual > 0)
                {
                    q.push(arcs[i].v);
                    visited[arcs[i].v] = 1;
                    parent[arcs[i].v] = i;
                }
        }

        return visited[sink];
    }

public:
    EdmondsKarp(int v, int e, int s, int t)
    {
        vertices = v;
        link = new int[v], parent = new int[v], visited = new int[v];
        arcs = new arc[e];
        indexer = 0, source = s, sink = t;
        memset(link, 0xff, vertices * sizeof(int));
    }

    ~EdmondsKarp()
    {
        delete [] link, parent, visited, arcs;
    }

    int maxFlow()
    {
        int netFlow = 0;

        while (bfs())
        {
            int delta = INF;
            for (int i = parent[sink]; i != -1; i = parent[arcs[i].u])
                delta = min(delta, arcs[i].residual);

            netFlow += delta;
            for (int i = parent[sink]; i != -1; i = parent[arcs[i].u])
            {
                arcs[i].residual -= delta;
                arcs[i ^ 1].residual += delta;
            }
        }

        return netFlow;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[indexer] = (arc){u, v, capacity, capacity, link[u]};
        link[u] = indexer++;
        arcs[indexer] = (arc){v, u, capacity, 0, link[v]};
        link[v] = indexer++;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, m, k;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        EdmondsKarp ek(220, 220 * 220, 0, 210);

        vector<int> edges[810];
        map<int, int> receptaclesIdx, plugsIdx;
        map<string, int> receptacles, plugs;
        string receptacle, device, plug;
        int indexer = 1;

        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> receptacle;

            // Add arc from source to receptacle.
            ek.addArc(0, i, 1);

            if (receptacles.find(receptacle) == receptacles.end())
                receptacles[receptacle] = indexer++;
            if (plugs.find(receptacle) == plugs.end())
                plugs[receptacle] = indexer++;
            edges[receptacles[receptacle]].push_back(plugs[receptacle]);

            receptaclesIdx[i] = receptacles[receptacle];
        }
        
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> device >> plug;
            
            if (receptacles.find(plug) == receptacles.end())
                receptacles[plug] = indexer++;
            if (plugs.find(plug) == plugs.end())
                plugs[plug] = indexer++;
            edges[receptacles[plug]].push_back(plugs[plug]);
            
            plugsIdx[n + i] = plugs[plug];
        }

        cin >> k;
        for (int i = 1; i <= k; i++)
        {
            cin >> receptacle >> plug;

            if (receptacles.find(receptacle) == receptacles.end())
                receptacles[receptacle] = indexer++;
            if (plugs.find(receptacle) == plugs.end())
                plugs[receptacle] = indexer++;
            edges[receptacles[receptacle]].push_back(plugs[receptacle]);
            
            if (receptacles.find(plug) == receptacles.end())
                receptacles[plug] = indexer++;
            if (plugs.find(plug) == plugs.end())
                plugs[plug] = indexer++;
            edges[receptacles[plug]].push_back(plugs[plug]);
            
            edges[plugs[plug]].push_back(receptacles[receptacle]);
        }

        int available[810][810] = {0}, visited[810];

        for (auto r : receptacles)
        {
            memset(visited, 0, sizeof(visited));
            queue<int> q; q.push(r.second);
            visited[r.second] = 1;

            while (!q.empty())
            {
                int u = q.front(); q.pop();
                for (auto v : edges[u])
                    if (!visited[v])
                    {
                        visited[v] = 1;
                        q.push(v);
                        available[r.second][v] = 1;
                    }
            }
        }

        for (auto d : plugsIdx)
        {
            for(auto p : receptaclesIdx)
                if (available[p.second][d.second])
                    // Add arc from receptacle to device.
                    ek.addArc(p.first, d.first, 1);
                    
            // Add arc from device to sink.
            ek.addArc(d.first, 210, 1);
        }

        if (c > 1) cout << '\n';
        int maxFlow = ek.maxFlow();
        cout << (m - maxFlow) << '\n';
    }
    
    return 0;
}
