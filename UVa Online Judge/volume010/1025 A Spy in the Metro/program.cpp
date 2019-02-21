// A Spy in the Metro
// UVa ID: 1025
// Verdict: Accepted
// Submission Date: 2019-02-21
// UVa Run Time: 0.010s
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

vector<edge> edges[10010];
vector<int> stopTime[60];
int mapping[60][210], dist[10010];

void mooreDijkstra()
{
    memset(dist, 0x7f, sizeof(dist));
    priority_queue<edge> q;
    dist[0] = 0;
    q.push(edge(0, 0));
    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
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
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    int N, T, M1, M2;
    int forward[60], backward[60];
    
    while (cin >> N, N > 0)
    {
        cin >> T;
        int C = 0;
        for (int i = 1; i <= N; i++)
            for (int j = 0; j <= T; j++)
            {
                mapping[i][j] = C++;
                edges[mapping[i][j]].clear();
            }
        forward[1] = 0;
        for (int i = 2, t1; i <= N; i++)
        {
            cin >> t1;
            forward[i] = forward[i - 1] + t1;
        }
        backward[N] = 0;
        for (int i = N - 1; i >= 1; i--)
            backward[i] = forward[N] - forward[i];
        for (int i = 1; i <= N; i++) stopTime[i].clear();
        cin >> M1;
        for (int i = 1, d1; i <= M1; i++)
        {
            cin >> d1;
            for (int j = 1; j <= N; j++)
            {
                if (d1 + forward[j] <= T)
                    stopTime[j].push_back(d1 + forward[j]);
                for (int k = j + 1; k <= N; k++)
                {
                    if (d1 + forward[j] <= T && d1 + forward[k] <= T)
                        edges[mapping[j][d1 + forward[j]]].push_back(edge(mapping[k][d1 + forward[k]], 0));
                }
            }
        }
        cin >> M2;
        for (int i = 1, e1; i <= M2; i++)
        {
            cin >> e1;
            for (int j = N; j >= 1; j--)
            {
                if (e1 + backward[j] <= T)
                    stopTime[j].push_back(e1 + backward[j]);
                for (int k = j - 1; k >= 1; k--)
                {
                    if (e1 + backward[j] <= T && e1 + backward[k] <= T)
                        edges[mapping[j][e1 + backward[j]]].push_back(edge(mapping[k][e1 + backward[k]], 0));
                }
            }
        }
        
        stopTime[1].push_back(0);
        stopTime[N].push_back(T);
        for (int i = 1; i <= N; i++)
        {
            sort(stopTime[i].begin(), stopTime[i].end());
            stopTime[i].erase(unique(stopTime[i].begin(), stopTime[i].end()), stopTime[i].end());
        }
        
        for (int i = 0; i <= N; i++)
        {
            int tot = stopTime[i].size();
            for (int j = 0; j < tot - 1; j++)
                for (int k = j + 1; k < tot; k++)
                {
                    int t1 = stopTime[i][j], t2 = stopTime[i][k];
                    edges[mapping[i][t1]].push_back(edge(mapping[i][t2], t2 - t1));
                }
        }
        
        mooreDijkstra();
        
        int D = dist[mapping[N][T]];
        cout << "Case Number " << ++cases << ": ";
        if (D == INF) cout << "impossible\n";
        else cout << D << '\n';
    }

    return 0;
}
