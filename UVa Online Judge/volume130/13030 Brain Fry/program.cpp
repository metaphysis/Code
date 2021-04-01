// Brain Fry
// UVa ID: 13030
// Verdict: Accepted
// Submission Date: 2019-02-19
// UVa Run Time: 0.620s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7f7f7f7f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

double p[260], probability[260][150], elapsed[260][150];
int visited[260][150];
vector<edge> edges[260];
int N, M, T, dist[260], neighbours[260];

void dfs(int u, int t)
{
    if (visited[u][t]) return;
    visited[u][t] = 1;
    probability[u][t] = elapsed[u][t] = 0;
    if (u)
    {
        probability[u][t] += p[u];
        elapsed[u][t] += p[u] * (t + dist[u]);

        if (t >= T)
        {
            elapsed[u][t] += (1 - p[u]) * (t + dist[u]);
            return;
        }

        if (neighbours[u] == 0)
        {
            dfs(0, t + dist[u]);
            probability[u][t] += (1 - p[u]) * probability[0][t + dist[u]];
            elapsed[u][t] += (1 - p[u]) * elapsed[0][t + dist[u]];
        }
        else
        {
            double s = 1.0 / neighbours[u];
            for (auto e : edges[u])
            {
                if (e.v)
                {
                    dfs(e.v, t + e.w);
                    probability[u][t] += s * (1 - p[u]) * probability[e.v][t + e.w];
                    elapsed[u][t] += s * (1 - p[u]) * elapsed[e.v][t + e.w];
                }
            }
        }
    }
    else
    {
        if (t >= T)
        {
            elapsed[u][t] = t + dist[u];
            return;
        }
        if (neighbours[u] > 0)
        {
            double s = 1.0 / neighbours[u];
            for (auto e : edges[u])
            {
                dfs(e.v, t + e.w);
                probability[u][t] += s * probability[e.v][t + e.w];
                elapsed[u][t] += s * elapsed[e.v][t + e.w];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> M >> T;
        for (int i = 1; i <= N; i++) cin >> p[i];
        for (int i = 0; i <= N; i++)
        {
            edges[i].clear();
            neighbours[i] = 0;
        }
        for (int i = 0, u, v, w; i < M; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, w));
            edges[v].push_back(edge(u, w));
            neighbours[u] += (v > 0);
            neighbours[v] += (u > 0);
        }

        memset(dist, INF, sizeof(dist));
        priority_queue<edge> q;
        dist[0] = 0;
        q.push(edge(0, 0));
        while (!q.empty())
        {
            edge e1 = q.top();
            q.pop();
            if (dist[e1.v] < e1.w) continue;
            for (auto e2 : edges[e1.v])
            {
                if (dist[e2.v] > dist[e1.v] + e2.w)
                {
                    dist[e2.v] = dist[e1.v] + e2.w;
                    q.push(edge(e2.v, dist[e2.v]));
                }
            }
        }

        memset(visited, 0, sizeof(visited));               
        dfs(0, 0);
        cout << "Case " << cs << ": ";
        cout << fixed << setprecision(6) << probability[0][0] << ' ' << elapsed[0][0] << '\n';
    }

    return 0;
}
