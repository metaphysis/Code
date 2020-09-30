// Adventure of Super Mario
// UVa ID: 10269
// Verdict: Accepted
// Submission Date: 2018-12-19
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

struct edge
{
    int v, length;
    edge (int v = 0, int length = 0): v(v), length(length) {}
};

struct walk
{
    int u, k, walked;
    walk (int u = 0, int k = 0, int walked = 0): u(u), k(k), walked(walked) {}
};

int T, A, B, M, L, K, D[128][16][512];
list<edge> edges[126];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> A >> B >> M >> L >> K;
        for (int i = 1; i <= (A + B); i++) edges[i].clear();
        for (int i = 1, Xi, Yi, Li; i <= M; i++)
        {
            cin >> Xi >> Yi >> Li;
            edges[Xi].push_back(edge(Yi, Li));
            edges[Yi].push_back(edge(Xi, Li));
        }
        memset(D, INF, sizeof(D));
        D[A + B][0][0] = 0;
        queue<walk> q;
        q.push(walk(A + B, 0, 0));
        while (!q.empty())
        {
            walk w = q.front(); q.pop();
            for (auto e : edges[w.u])
            {
                if (!w.walked)
                {
                    if (D[e.v][w.k][0] > D[w.u][w.k][0] + e.length)
                    {
                        D[e.v][w.k][0] = D[w.u][w.k][0] + e.length;
                        q.push(walk(e.v, w.k, 0));
                    }
                }
                else
                {
                    int next_walked = (e.v > A || w.walked + e.length > L) ? 0 : w.walked + e.length;
                    if (D[e.v][w.k][next_walked] > D[w.u][w.k][w.walked] + (next_walked ? 0 : e.length))
                    {
                        D[e.v][w.k][next_walked] = D[w.u][w.k][w.walked] + (next_walked ? 0 : e.length);
                        q.push(walk(e.v, w.k, next_walked));
                    }
                }
                if (w.k < K && e.length <= L)
                {
                    int next_k = w.k + 1, next_walked = e.v > A ? 0 : e.length;
                    if (D[e.v][next_k][next_walked] > D[w.u][w.k][w.walked])
                    {
                        D[e.v][next_k][next_walked] = D[w.u][w.k][w.walked];
                        q.push(walk(e.v, next_k, next_walked));
                    }
                }
            }
        }
        int best = INF;
        for (int i = 0; i <= K; i++)
            for (int j = 0; j <= L; j++)
                best = min(best, D[1][i][j]);
        cout << best << '\n';
    }

    return 0;
}
