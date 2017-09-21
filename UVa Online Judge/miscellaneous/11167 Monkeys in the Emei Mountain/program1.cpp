// Monkeys in the Emei Mountain
// UVa ID: 11167
// Verdict: TLE
// Submission Date: 2017-09-21
// UVa Run Time: 3.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

const int INF = 0x7fffffff;

struct arc
{
    int u, v, capacity, residual, next;
};

class Dinic
{
private:
    arc *arcs;
    int vertices, idx, source, sink, *link, *dist;

    bool bfs()
    {
        memset(dist, 0xff, vertices * sizeof(int));

        queue<int> q;
        q.push(source);
        dist[source] = 1;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int x = link[u]; x != -1; x = arcs[x].next)
                if (arcs[x].residual > 0 && dist[arcs[x].v] < 0)
                {
                    dist[arcs[x].v] = dist[u] + 1;
                    q.push(arcs[x].v);
                }
        }

        return dist[sink] > 0;
    }

    int dfs(int u, int flow)
    {
        if (u == sink) return flow;

        for (int x = link[u]; x != -1; x = arcs[x].next)
        {
            int v = arcs[x].v, r = arcs[x].residual;
            if (dist[v] == (dist[u] + 1) && r > 0)
            {
                int volume = dfs(v, min(r, flow));
                if (volume > 0)
                {
                    arcs[x].residual -= volume;
                    arcs[x ^ 1].residual += volume;
                    return volume;
                }
            }
        }

        return 0;
    }

public:
    Dinic(int v, int e, int s, int t)
    {
        vertices = v;
        link = new int[v], dist = new int[v];
        arcs = new arc[e];
        source = s, sink = t;
        idx = 0;
        memset(link, 0xff, vertices * sizeof(int));
    }

    ~Dinic()
    {
        delete[]link, dist, arcs;
    }

    int maxFlow()
    {
        int delta, netFlow = 0;

        while (bfs())
        {
            while (delta = dfs(0, INF))
                netFlow += delta;
        }

        return netFlow;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[idx] = (arc){u, v, capacity, capacity, link[u]};
        link[u] = idx++;

        arcs[idx] = (arc){v, u, capacity, 0, link[v]};
        link[v] = idx++;
    }

    vector<arc> getArcs(int u)
    {
        vector < arc > as;
        for (int i = link[u]; i != -1; i = arcs[i].next)
            as.insert(as.begin(), arcs[i]);
        return as;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int n, m;
    int v, a, b;
    int drinked[50000];

    while (cin >> n, n > 0)
    {
        cin >> m;

        Dinic dinic(50200, 11000000, 0, 50150);

        memset(drinked, 0, sizeof(drinked));

        int flow = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> v >> a >> b;
            flow += v;
            dinic.addArc(0, i, v);
            for (int j = a; j < b; j++)
            {
                dinic.addArc(i, n + j + 1, 1);
                if (drinked[j])
                    continue;
                dinic.addArc(n + j + 1, 50150, m);
                drinked[j] = 1;
            }
        }

        cout << "Case " << ++cases << ": ";
        if (dinic.maxFlow() == flow)
        {
            cout << "Yes\n";
            for (int i = 1; i <= n; i++)
            {
                vector < int >interval;
              for (auto a:dinic.getArcs(i))
                {
                    if (a.residual == 0)
                    {
                        if (!interval.size() || (a.v - n - 1) != interval.back())
                        {
                            interval.push_back(a.v - n - 1);
                            interval.push_back(a.v - n);
                        }
                        else
                            interval.back() += 1;
                    }
                }

                cout << interval.size() / 2;
                for (int i = 0; i < interval.size(); i += 2)
                    cout << " (" << interval[i] << ',' << interval[i + 1] << ')';
                cout << '\n';
            }
        }
        else
            cout << "No\n";
    }

    return 0;
}
