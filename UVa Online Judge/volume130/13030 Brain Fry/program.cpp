// Brain Fry
// UVa ID: 13030
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

double p[260], dp[260][150][2], visited[260][150];
vector<edge> edges[260];
int N, M, T, dist[260];

void dfs(int u, int t)
{
    if (visited[u][t]) return;
    visited[u][t] = 1;
    dp[u][t][0] = dp[u][t][1] = 0;
    if (u)
    {
        dp[u][t][0] += p[u];
        dp[u][t][1] += p[u] * (t + dist[u]);

        if (t >= T)
        {
            dp[u][t][1] += (1 - p[u]) * (t + dist[u]);
            return;
        }

        int neighbour = 0;
        for (auto e : edges[u])
            if (e.v)
                neighbour++;
        if (neighbour == 0)
        {
            dfs(0, t + dist[u]);
            dp[u][t][0] += (1 - p[u]) * dp[0][t + dist[u]][0];
            dp[u][t][1] += (1 - p[u]) * dp[0][t + dist[u]][1];
        }
        else
        {
            double s = 1.0 / neighbour;
            for (auto e : edges[u])
            {
                if (e.v)
                {
                    dfs(e.v, t + e.w);
                    dp[u][t][0] += s * (1 - p[u]) * dp[e.v][t + e.w][0];
                    dp[u][t][1] += s * (1 - p[u]) * dp[e.v][t + e.w][1];
                }
            }
        }
    }
    else
    {
        if (t >= T)
        {
            dp[u][t][1] = t + dist[u];
            return;
        }
        int neighbour = edges[u].size();
        if (neighbour)
        {
            double s = 1.0 / neighbour;
            for (auto e : edges[u])
            {
                dfs(e.v, t + e.w);
                dp[u][t][0] += s * dp[e.v][t + e.w][0];
                dp[u][t][1] += s * dp[e.v][t + e.w][1];
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
        for (int i = 0; i <= N; i++) edges[i].clear();
        for (int i = 0, u, v, w; i < M; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, w));
            edges[v].push_back(edge(u, w));
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
        cout << fixed << setprecision(6) << dp[0][0][0] << ' ' << dp[0][0][1] << '\n';
    }

    return 0;
}
