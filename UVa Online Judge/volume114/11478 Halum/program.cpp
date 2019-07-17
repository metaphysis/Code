// Halum
// UVa ID: 11478
// Verdict: Accepted
// Submission Date: 2019-07-17
// UVa Run Time: 1.240s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f, MAXN = 510, MAXE = 4010;

struct edge
{
    int v, w, next;
    edge (int v = 0, int w = 0, int next = 0): v(v), w(w), next(next) {}
} edges[MAXE];

int idx, n, m, head[MAXN], dist[MAXN], in[MAXN], cnt[MAXN];

void addEdge(int u, int v, int w)
{
    edges[idx] = edge(v, w, head[u]);
    head[u] = idx++;
}

bool spfa()
{
    memset(in, 0, sizeof(in));
    memset(cnt, 0, sizeof(cnt));
    memset(dist, 0x3f, sizeof(dist));

    queue<int> q;
    dist[0] = 0, in[0] = 1;
    q.push(0);
    
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        if (cnt[u] > n) return false;
        in[u] = 0;
        for (int i = head[u]; ~i; i = edges[i].next)
        {
            edge e = edges[i];
            if (dist[e.v] > dist[u] + e.w)
            {
                dist[e.v] = dist[u] + e.w;
                if (!in[e.v])
                {
                    q.push(e.v);
                    in[e.v] = 1;
                    cnt[e.v]++;
                }
            }
        }
    }
    return true;
}

bool worked(int W)
{
    for (int i = 0; i < idx; i++) edges[i].w -= W;
    bool r = spfa();
    for (int i = 0; i < idx; i++) edges[i].w += W;
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m)
    {
        idx = 0;
        memset(head, -1, sizeof(head));
        int W = -INF;
        for (int i = 0, u, v, w; i < m; i++)
        {
            cin >> u >> v >> w;
            addEdge(u, v, w);
            W = max(w, W);
        }
        for (int i = 1; i <= n; i++)
            addEdge(0, i, 0);

        if (worked(W + 1)) cout << "Infinite\n";
        else
        {
            if (!worked(1)) cout << "No Solution\n";
            else
            {
                int L = 1, R = W, M, A;
                while (L <= R)
                {
                    M = (L + R) / 2;
                    if (worked(M))
                    {
                        A = M;
                        L = M + 1;
                    }
                    else R = M - 1;
                }
                cout << A << '\n';
            }
        }
    }
    
    return 0;
}
