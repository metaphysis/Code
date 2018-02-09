// Lift Hopping
// UVa ID: 10801
// Verdict: Accepted
// Submission Date: 2018-02-09
// UVa Run Time: 0.000s
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
    int elevator, floor, second;
    edge (int elevator = 0, int floor = 0, int second = 0): elevator(elevator), floor(floor), second(second) {}
    bool operator<(const edge &e) const { return second > e.second; }
};

list<edge> edges[10][110];
vector<int> floors[10];
set<int> passed[10];
int dist[10][110], switchTime[10], INF = 0x7fffffff;
int n, k;

void mooreDijkstra()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 110; j++)
            dist[i][j] = INF;

    queue<edge> q;
    for (int i = 0; i < n; i++)
        if (passed[i].find(0) != passed[i].end())
        {
            q.push(edge(i, 0, 0));
            dist[i][0] = 0;
        }

    while (!q.empty())
    {
        edge u = q.front(); q.pop();
        for (auto e : edges[u.elevator][u.floor])
            if (dist[e.elevator][e.floor] > dist[u.elevator][u.floor] + e.second)
            {
                dist[e.elevator][e.floor] = dist[u.elevator][u.floor] + e.second;
                q.push(edge(e.elevator, e.floor, dist[e.elevator][e.floor]));
            }
    }
    
    if (k > 99) cout << "IMPOSSIBLE";
    else
    {
        int minDist = INF;
        for (int i = 0; i < n; i++)
            minDist = min(minDist, dist[i][k]);
        if (minDist != INF) cout << minDist;
        else cout << "IMPOSSIBLE";       
    }
    cout << '\n';
}

void buildGraph()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 110; j++)
            edges[i][j].clear();

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < floors[i].size(); j++)
        {
            int f1 = floors[i][j - 1], f2 = floors[i][j];
            int seconds = switchTime[i] * (f2 - f1);
            edges[i][f1].push_back(edge(i, f2, seconds));
            edges[i][f2].push_back(edge(i, f1, seconds));
        }
        
        for (auto f : floors[i])
        {
            for (int j = i + 1; j < n; j++)
            {
                if (passed[j].find(f) != passed[j].end())
                {
                    edges[i][f].push_back(edge(j, f, 60));
                    edges[j][f].push_back(edge(i, f, 60));
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;

    while (cin >> n >> k)
    {
        for (int i = 0; i < n; i++)
            cin >> switchTime[i];

        cin.ignore(1024, '\n');
        for (int i = 0; i < n; i++)
        {
            floors[i].clear();
            passed[i].clear();

            getline(cin, line);
            istringstream iss(line);

            int f;
            while (iss >> f)
            {
                floors[i].push_back(f);
                passed[i].insert(f);
            }
        }
        buildGraph();
        mooreDijkstra();
    }

    return 0;
}
