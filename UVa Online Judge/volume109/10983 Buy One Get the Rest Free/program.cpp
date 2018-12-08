// Buy One Get the Rest Free
// UVa ID: 10983
// Verdict: Accepted
// Submission Date: 2018-12-08
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

struct arc
{
    int u, v, capacity, residual, cost, next;
};

class EdmondsKarp
{
private:
    arc *arcs;
    int vertices, idx, source, sink, *head, *path, *visited;

    bool bfs(int cost)
    {
        memset(path, -1, vertices * sizeof(int));
        memset(visited, 0, vertices * sizeof(int));

        queue<int> q;
        q.push(source);
        visited[source] = 1;

        while (!q.empty())
        {
            int u = q.front(); q.pop();
            if (u == sink) break;
            for (int i = head[u]; ~i; i = arcs[i].next)
                if (!visited[arcs[i].v] && arcs[i].residual > 0 && arcs[i].cost <= cost)
                {
                    q.push(arcs[i].v);
                    visited[arcs[i].v] = 1;
                    path[arcs[i].v] = i;
                }
        }

        return visited[sink];
    }

    void restoreFlowNetwork()
    {
        for (int i = 0; i < idx; i++)
        {
            if (i & 1) arcs[i].residual = 0;
            else arcs[i].residual = arcs[i].capacity;
        }
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

    int maxFlow(int cost)
    {
        restoreFlowNetwork();

        int flow = 0;
        while (bfs(cost))
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

    void addArc(int u, int v, int capacity, int cost)
    {
        arcs[idx] = (arc){u, v, capacity, capacity, cost, head[u]};
        head[u] = idx++;
        arcs[idx] = (arc){v, u, capacity, 0, cost, head[v]};
        head[v] = idx++;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, d, m, participants, id[32][16], cnt;
    
    int cases, u, v, c, p, e;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> d >> m;
        cnt = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= d; j++)
                id[i][j] = cnt++;
        EdmondsKarp ek(cnt + 1, 10240, 0, cnt);
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> c >> p >> e;
            ek.addArc(id[u][e], id[v][e + 1], c, p);
        }
        participants = 0;
        for (int i = 1, zi; i <= n; i++)
        {
            cin >> zi;
            ek.addArc(0, id[i][0], zi, 0);
            participants += zi;
        }
        ek.addArc(id[n][d], cnt, INF, 0);
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < d; j++)
                ek.addArc(id[i][j], id[i][j + 1], INF, 0);

        cout << "Case #" << cs << ": ";
        int low = 0, high = 100010, mid;
        if (ek.maxFlow(high) < participants)
        {
            cout << "Impossible\n";
            continue;
        }
        while (low <= high)
        {
            mid = (low + high) >> 1;
            if (ek.maxFlow(mid) == participants) high = mid - 1;
            else low = mid + 1;
        }
        cout << low << '\n';
    }

    return 0;
}
