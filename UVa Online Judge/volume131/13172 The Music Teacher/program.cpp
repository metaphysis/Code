// The Music Teacher
// UVa ID: 13172
// Verdict: Accepted
// Submission Date: 2018-02-11
// UVa Run Time: 0.240s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 1024, INF = 0x3f3f3f3f;

struct edge
{
    int v, weight;
    edge (int v = 0, int weight = 0): v(v), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
};

list<edge> edges[MAXV];
int n, m, dist[MAXV][MAXV], cached[MAXV], used[MAXV];

void mooreDijkstra(int u)
{
    memset(dist[u], 0x3f, sizeof(dist[u]));
    priority_queue<edge> q;
    q.push(edge(u, 0));
    dist[u][u] = 0;
    
    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (auto e2 : edges[e1.v])
        {
            if (dist[u][e2.v] > dist[u][e1.v] + e2.weight)
            {
                dist[u][e2.v] = dist[u][e1.v] + e2.weight;
                q.push(edge(e2.v, dist[u][e2.v]));
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int u, v, weight, cases, numberOfVillage, cntOfVillages;
    vector<int> villages;

    while (cin >> n >> m)
    {
        for (int i = 1; i <= n; i++) edges[i].clear();
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> weight;
            edges[u].push_back(edge(v, weight));
            edges[v].push_back(edge(u, weight));
        }

        cin >> cases;
        memset(cached, 0, sizeof(cached));
        for (int i = 1; i <= cases; i++)
        {
            cin >> cntOfVillages;
            memset(used, 0, sizeof(used));
            villages.clear();
            for (int j = 1; j <= cntOfVillages; j++)
            {
                cin >> numberOfVillage;
                villages.push_back(numberOfVillage);
                used[numberOfVillage] = 1;
                if (cached[numberOfVillage]) continue;
                cached[numberOfVillage] = 1;
                mooreDijkstra(numberOfVillage);
            }

            sort(villages.begin(), villages.end());
            int minDist = INF, selectedVillage = -1;
            do
            {
                int d1 = 0;
                for (int j = 1; j < villages.size(); j++)
                {
                    if (dist[villages[j - 1]][villages[j]] == INF)
                    {
                        d1 = INF;
                        break;
                    }
                    d1 += dist[villages[j - 1]][villages[j]];
                }
                if (d1 == INF) continue;
                for (int j = 1; j <= n; j++)
                    if (!used[j])
                    {
                        if (dist[villages.front()][j] == INF) continue;
                        if (dist[villages.back()][j] == INF) continue;
                        int d2 = d1 + dist[villages.front()][j] + dist[villages.back()][j];
                        if (d2 < minDist || (d2 == minDist && j < selectedVillage))
                        {
                            minDist = d2;
                            selectedVillage = j;
                        }
                    }
            } while(next_permutation(villages.begin(), villages.end()));
            cout << selectedVillage << ' ' << minDist << '\n';
        }
        cout << "---\n";
    }

    return 0;
}
