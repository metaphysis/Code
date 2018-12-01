// Travel in Desert
// UVa ID: 10816
// Verdict: Accepted
// Submission Date: 2018-12-01
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

struct edge
{
    int u, v, r, d, next;
    edge (int u = 0, int v = 0, int r = 0, int d = 0, int next = 0): u(u), v(v), r(r), d(d), next(next) {}
} edges[20480];

int getInt(string s)
{
    int n = 0;
    for (auto c : s)
        if (isdigit(c))
            n = n * 10 + c - '0';
    return n;
}

int head[128], idx = 0;
void addEdge(int u, int v, int r, int d)
{
    edges[idx] = edge(u, v, r, d, head[u]);
    head[u] = idx++;
    edges[idx] = edge(v, u, r, d, head[v]);
    head[v] = idx++;
}

int dist[128], parent[128], visited[128];
void mooreDijkstra(int u, int N, int R)
{
    for (int i = 0; i < N; i++) dist[i] = INF, parent[i] = -1, visited[i] = 0;
    dist[u] = 0;
    while (!visited[u])
    {
        visited[u] = 1;
        for (int i = head[u]; ~i; i = edges[i].next)
        {
            edge e = edges[i];
            if (!visited[e.v] && e.r <= R && dist[e.v] > dist[u] + e.d)
                dist[e.v] = dist[u] + e.d, parent[e.v] = u;
        }
        int least = INF;
        for (int i = 0; i < N; i++)
            if (!visited[i] && least > dist[i])
                least = dist[i], u = i;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, E, S, T, X, Y;
    string R, D;

    while (cin >> N >> E)
    {
        cin >> S >> T;
        S--, T--;
        
        idx = 0;
        memset(head, -1, sizeof(head));
        for (int i = 1; i <= E; i++)
        {
            cin >> X >> Y >> R >> D;
            X--, Y--;
            addEdge(X, Y, getInt(R), getInt(D));
        }

        int lowR = 0, highR = 500, middleR;
        while (lowR <= highR)
        {
            middleR = (lowR + highR) >> 1;
            mooreDijkstra(S, N, middleR);
            if (~parent[T]) highR = middleR - 1;
            else lowR = middleR + 1;
        }

        int TT = T;
        mooreDijkstra(S, N, lowR);

        vector<int> paths;
        while (T != S)
        {
            paths.push_back(T);
            T = parent[T];
        }
        paths.push_back(S);
        reverse(paths.begin(), paths.end());
        for (int i = 0; i < paths.size(); i++)
        {
            if (i) cout << ' ';
            cout << (paths[i] + 1);
        }
        cout << '\n';
        cout << (dist[TT] / 10) << '.' << (dist[TT] % 10);
        cout << ' ';
        cout << (lowR / 10) << '.' << (lowR % 10) << '\n';
    }

    return 0;
}
