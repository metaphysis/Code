// Toll
// UVa ID: 1027
// Verdict: Accepted
// Submission Date: 2018-02-10
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
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges[128];

int getX(int p, bool town)
{
    if (!town) return p + 1;
    int x = p + 1;
    while (true)
    {
        if ((x - (x / 20) - ((x % 20) != 0 ? 1 : 0)) == p) break;
        x++;
    }
    return x;
}

int getY(int p, bool town)
{
    if (!town) return p - 1;
    return p - (p / 20) - ((p % 20) != 0 ? 1 : 0);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int n, p, s, t, dist[128];
    char start, end;

    while (cin >> n, n >= 0)
    {
        for (int i = 0; i < 128; i++)
            edges[i].clear();
        for (int i = 0; i < n; i++)
        {
            cin >> start >> end;
            s = start - 0, t = end - 0;
            edges[s].push_back(t);
            edges[t].push_back(s);
        }
        cin >> p >> start >> end;
        s = start - 0, t = end - 0;
    
        memset(dist, 0x7f, sizeof(dist));
        priority_queue<edge> q;
        p = getX(p, t <= 'Z');
        q.push(edge(t, p));
        dist[t] = p;

        while (!q.empty())
        {
            edge u = q.top(); q.pop();
            for (auto e : edges[u.v])
            {
                p = getX(dist[u.v], e.v <= 'Z');
                if (dist[e.v] > p)
                {
                    dist[e.v] = p;
                    q.push(edge(e.v, p));
                }
            }
        }
        
        cout << "Case " << ++cases << ": " << getY(dist[s], s <= 'Z') << '\n';
    }

    return 0;
}
