// Clever Naming Patterns
// UVa ID: 11418
// Verdict: Accepted
// Submission Date: 2017-10-06
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
    int vertices, idx, source, sink, *head, *path, *visited;

    bool bfs()
    {
        memset(path, -1, vertices * sizeof(int));
        memset(visited, 0, vertices * sizeof(int));

        queue<int> q; q.push(source);
        visited[source] = 1;

        while (!q.empty())
        {
            int u = q.front(); q.pop();
            if (u == sink) break;
            for (int i = head[u]; ~i; i = arcs[i].next)
                if (!visited[arcs[i].v] && arcs[i].residual > 0)
                {
                    q.push(arcs[i].v);
                    visited[arcs[i].v] = 1;
                    path[arcs[i].v] = i;
                }
        }

        return visited[sink];
    }

public:
    EdmondsKarp(int v, int e, int s, int t)
    {
        vertices = v;
        head = new int[v], path = new int[v], visited = new int[v];
        arcs = new arc[e];
        idx = 0, source = s, sink = t;
        memset(head, -1, vertices * sizeof(int));
    }

    ~EdmondsKarp()
    {
        delete [] head, path, visited, arcs;
    }

    int maxFlow()
    {
        int flow = 0;

        while (bfs())
        {
            int delta = INF;
            for (int i = path[sink]; ~i; i = path[arcs[i].u])
                delta = min(delta, arcs[i].residual);
            flow += delta;
            for (int i = path[sink]; ~i; i = path[arcs[i].u])
            {
                arcs[i].residual -= delta;
                arcs[i ^ 1].residual += delta;
            }
        }

        return flow;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[idx] = (arc){u, v, capacity, capacity, head[u]};
        head[u] = idx++;
        arcs[idx] = (arc){v, u, capacity, 0, head[v]};
        head[v] = idx++;
    }
    
    arc getArc(int u)
    {
        for (int i = head[u]; ~i; i = arcs[i].next)
            if (arcs[i].u < arcs[i].v && !arcs[i].residual)
                return arcs[i];
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, m;
    vector<string> names[32];
    string name;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        EdmondsKarp ek(100, 2000, 0, 64);

        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            names[i].clear();

            cin >> m;
            for (int j = 1; j <= m; j++)
            {
                cin >> name;
                for (int k = 0; k < name.size(); k++)
                    name[k] = tolower(name[k]);
                name.front() = toupper(name.front());
                names[i].push_back(name);
                ek.addArc(i, name.front() - 'A' + 27, 1);
            }

            ek.addArc(0, i, 1);
            ek.addArc(i + 26, 64, 1);
        }

        ek.maxFlow();
        
        vector<string> titles;
        for (int i = 1; i <= n; i++)
        {
            arc a = ek.getArc(i);
            for (int j = 0; j < names[i].size(); j++)
                if (names[i][j].front() == ('A' + a.v - 27))
                {
                    titles.push_back(names[i][j]);
                    break;
                }
        }
        
        sort(titles.begin(), titles.end());
        cout << "Case #" << c << ":\n";
        for (auto title : titles) cout << title << '\n';
    }

    return 0;
}
