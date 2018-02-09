// Travel
// UVa ID: 10166
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

const int MAXV = 110;

struct edge
{
    int v, departure, arrive;
    edge (int v = 0, int departure = 0, int arrive = 0): v(v), departure(departure), arrive(arrive) {}
};

list<edge> edges[MAXV];
int n;

void format(int time)
{
    cout << setw(2) << right << setfill('0') << time / 60;
    cout << setw(2) << right << setfill('0') << time % 60;
}

void bfs(int starting, int begin, int end)
{
    int departure = -1, arrive = -1;
    queue<edge> q;
    for (auto e : edges[begin])
    {
        if (e.departure < starting) continue;
        q.push(edge(e.v, e.departure, e.arrive));
    }

    while (!q.empty())
    {
        edge e1 = q.front(); q.pop();
        if (e1.v == end)
        {
            if (departure < 0 ||
                e1.arrive < arrive ||
                (e1.arrive == arrive && e1.departure > departure))
            {
                departure = e1.departure;
                arrive = e1.arrive;
            }
            continue;
        }
        for (auto e2 : edges[e1.v])
        {
            if (e2.departure < e1.arrive) continue;
            q.push(edge(e2.v, e1.departure, e2.arrive));
        }
    }
    
    if (departure == -1) cout << "No connection\n";
    else
    {
        format(departure);
        cout << ' ';
        format(arrive);
        cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string name, city1, city2;
    int trains, stations, t1, t2, starting;

    while (cin >> n, n > 0)
    {
        map<string, int> indexer;

        for (int i = 0; i < n; i++)
            edges[i].clear();

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
        bfs(starting, indexer[city1], indexer[city2]);
    }

    return 0;
}
