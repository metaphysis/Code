// Sending email
// UVa ID: 10986
// Verdict: Accepted
// Submission Date: 2017-10-25
// UVa Run Time: 0.130s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 20010, INF = 0x3fffffff;

struct edge
{
    int to, weight;
    bool operator<(const edge &e) const { return weight > e.weight; }
};

list<edge> edges[MAXV];
int dist[MAXV], parent[MAXV], visited[MAXV];
int n, m, S, T;
        
void mooreDijkstra(int u)
{
    for (int i = 0; i < n; i++) dist[i] = INF, parent[i] = -1;
    dist[u] = 0;
    
    priority_queue<edge> q;
    q.push((edge){u, dist[u]});
    while (!q.empty())
    {
        edge v = q.top(); q.pop();
        for (auto e : edges[v.to])
            if (dist[e.to] > dist[v.to] + e.weight)
            {
                dist[e.to] = dist[v.to] + e.weight;
                parent[e.to] = v.to;
                q.push((edge){e.to, dist[e.to]});
            }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int from, to, weight;

        cin >> n >> m >> S >> T;

        for (int i = 0; i < n; i++)  edges[i].clear();
        for (int i = 0; i < m; i++)
        {
            cin >> from >> to >> weight;
            edges[from].push_back(edge{to, weight});
            edges[to].push_back(edge{from, weight});
        }
        
        mooreDijkstra(S);
        
        cout << "Case #" << c << ": ";
        if (dist[T] != INF) cout << dist[T];
        else cout << "unreachable";
        cout << '\n';
    }

    return 0;
}
