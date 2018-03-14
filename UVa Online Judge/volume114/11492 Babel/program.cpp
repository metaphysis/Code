// Babel
// UVa ID: 11492
// Verdict: Accepted
// Submission Date: 2018-02-10
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 4010, INF = 0x7f7f7f7f;

struct edge
{
    int v, c, w;
    edge (int v = 0, int c = 0, int w = 0): v(v), c(c), w(w) {};
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges[MAXV];
string O, D, I1, I2, P;
map<string, int> indexer;
int n, m, dist[MAXV][32];

int getIndex(string key)
{
    if (indexer.find(key) == indexer.end())
    {
        indexer[key] = n;
        n++;
    }
    return indexer[key];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> m, m > 0)
    {
        n = 0;
        indexer.clear();
        for (int i = 0; i < MAXV; i++)
            edges[i].clear();

        cin >> O >> D;
        getIndex(O); getIndex(D);

        for (int i = 0; i < m; i++)
        {
            cin >> I1 >> I2 >> P;
            int i1 = getIndex(I1), i2 = getIndex(I2);
            edges[i1].push_back(edge(i2, P.front() - 'a' + 1, P.length()));
            edges[i2].push_back(edge(i1, P.front() - 'a' + 1, P.length()));
        }
        
        int io = getIndex(O), id = getIndex(D);
        memset(dist, 0x7f, sizeof(dist));
        priority_queue<edge> q;
        q.push(edge(io, 0, 0));
        dist[io][0] = 0;
        
        while (!q.empty())
        {
            edge u = q.top(); q.pop();
            for (auto e : edges[u.v])
            {
                if (u.c == e.c) continue;
                if (dist[e.v][e.c] > dist[u.v][u.c] + e.w)
                {
                    dist[e.v][e.c] = dist[u.v][u.c] + e.w;
                    q.push(edge(e.v, e.c, dist[e.v][e.c]));
                }
            }
        }
        
        int minDist = INF;
        for (int i = 1; i <= 26; i++)
            minDist = min(minDist, dist[id][i]);
        if (minDist != INF) cout << minDist << '\n';
        else cout << "impossivel\n";
    }

    return 0;
}
