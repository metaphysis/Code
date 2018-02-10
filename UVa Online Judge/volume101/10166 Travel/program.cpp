// Travel
// UVa ID: 10166
// Verdict: Accepted
// Submission Date: 2018-02-10
// UVa Run Time: 0.080s
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

const int MAXV = 110, INF = 0x7fffffff;

struct edge
{
    int v, departure, arrive;
    edge (int v = 0, int departure = 0, int arrive = 0): v(v), departure(departure), arrive(arrive) {}
};

list<edge> edges[MAXV];

void format(int begin, int end)
{
    cout << setw(2) << right << setfill('0') << begin / 60;
    cout << setw(2) << right << setfill('0') << begin % 60 << ' ';
    cout << setw(2) << right << setfill('0') << end / 60;
    cout << setw(2) << right << setfill('0') << end % 60 << '\n';
}

void mooreDijkstra(int starting, int begin, int end)
{
    int departure = 0, arrive = INF, dist[MAXV];
    for (auto e : edges[begin])
    {
        if (e.departure < starting) continue;
        for (int i = 0; i < MAXV; i++) dist[i] = INF;
        queue<edge> q;
        q.push(edge(begin, e.departure, e.departure));
        while (!q.empty())
        {
            edge e1 = q.front(); q.pop();
            for (auto e2 : edges[e1.v])
                if (e1.arrive <= e2.departure && dist[e2.v] > e2.arrive)
                {
                    dist[e2.v] = e2.arrive;
                    q.push(e2);
                }
        }
        if (dist[end] != INF)
        {
            if (dist[end] < arrive ||
                (dist[end] == arrive && e.departure > departure))
                departure = e.departure, arrive = dist[end];
        }
    }

    if (arrive != INF) format(departure, arrive);
    else cout << "No connection\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string name, city1, city2;
    int n, trains, stations, t1, t2, starting;

    while (cin >> n, n > 0)
    {
        map<string, int> indexer;

        for (int i = 0; i < n; i++) edges[i].clear();
        for (int i = 0; i < n; i++)
        {
            cin >> name;
            indexer[name] = i;
        }

        cin >> trains;
        for (int i = 1; i <= trains; i++)
        {
            cin >> stations;
            for (int j = 0; j < stations; j++)
            {
                if (!j)
                {
                    cin >> t1 >> city1;
                    t1 = (t1 / 100) * 60 + t1 % 100;
                }
                else
                {
                    cin >> t2 >> city2;
                    t2 = (t2 / 100) * 60 + t2 % 100;
                    int s1 = indexer[city1], s2 = indexer[city2];
                    edges[s1].push_back(edge(s2, t1, t2));
                    city1 = city2, t1 = t2;
                }
            }
        }

        cin >> starting >> city1 >> city2;
        starting = (starting / 100) * 60 + starting % 100;
        mooreDijkstra(starting, indexer[city1], indexer[city2]);
    }

    return 0;
}
