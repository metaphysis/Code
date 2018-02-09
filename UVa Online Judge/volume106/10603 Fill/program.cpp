// Fill
// UVa ID: 10603
// Verdict: Accepted
// Submission Date: 2018-02-09
// UVa Run Time: 0.040s
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

struct edge
{
    int to, weight;
    edge (int to = 0, int weight = 0): to(to), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
};

map<int, list<edge>> edges;
int a, b, c, d;

inline int getKey(int aa, int bb, int cc)
{
    return aa * 1000000 + bb * 1000 + cc;
}

void buildGraph()
{
    int tag[6][2] = {{0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1}};
    int poured, volumes[3], liters[3] = {a, b, c};

    edges.clear();

    int key = getKey(0, 0, c);
    queue<edge> q;
    q.push(edge(key, 0));
    
    set<int> visited;
    visited.insert(key);

    while (!q.empty())
    {
        edge u = q.front(); q.pop();
        int aa = u.to / 1000000, bb = (u.to % 1000000) / 1000, cc = u.to % 1000;
        for (int k = 0; k < 6; k++)
        {
            int from = tag[k][0], to = tag[k][1];
            volumes[0] = aa, volumes[1] = bb, volumes[2] = cc;
            if (!volumes[from]) continue;
            if (volumes[from] > (liters[to] - volumes[to]))
            {
                poured = liters[to] - volumes[to];
                volumes[from] -= poured;
                volumes[to] = liters[to];
            }
            else
            {
                poured = volumes[from];
                volumes[to] += poured;
                volumes[from] = 0;
            }
            key = getKey(volumes[0], volumes[1], volumes[2]);
            edges[u.to].push_back(edge(key, poured));
            if (visited.find(key) == visited.end())
            {
                visited.insert(key);
                q.push(edge(key, 0));
            }
        }
    }
}

void mooreDijkstra()
{
    map<int, int> dist;
    priority_queue<edge> q;
    q.push(edge(getKey(0, 0, c), 0));
    dist[getKey(0, 0, c)] = 0;

    while (!q.empty())
    {
        edge u = q.top(); q.pop();
        for (auto v : edges[u.to])
        {
            if (dist.find(v.to) == dist.end() || dist[v.to] > dist[u.to] + v.weight)
            {
                dist[v.to] = dist[u.to] + v.weight;
                q.push(edge(v.to, dist[v.to]));
            }
        }
    }
    
    int r[201], INF = 0x3fffffff;
    for (int i = 0; i < 201; i++) r[i] = INF;
    r[0] = r[c] = 0;

    for (auto dt : dist)
    {
        int aa = dt.first / 1000000, bb = (dt.first % 1000000) / 1000, cc = dt.first % 1000;
        r[aa] = min(r[aa], dt.second);
        r[bb] = min(r[bb], dt.second);
        r[cc] = min(r[cc], dt.second);
    }
    for (int i = min(d, c); i >= 0; i--)
        if (r[i] != INF)
        {
            cout << r[i] << ' ' << i << '\n';
            break;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> a >> b >> c >> d;
        buildGraph();
        mooreDijkstra();
    }

    return 0;
}
