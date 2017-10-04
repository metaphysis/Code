// Faster Processing Feasibility
// UVa ID: 11358
// Verdict: Accepted
// Submission Date: 2017-09-23
// UVa Run Time: 0.140s
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

        queue<int> q; q.push(source);
        dist[source] = 1;

        while (!q.empty())
        {
            int u = q.front(); q.pop();
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
        link = new int[v], dist = new int[v], arcs = new arc[e];
        idx = 0, source = s, sink = t;
        memset(link, 0xff, vertices * sizeof(int));
    }

    ~Dinic()
    {
        delete[]link, dist, arcs;
    }

    int maxFlow()
    {
        int netFlow = 0;

        while (bfs())
            while (int delta = dfs(0, INF))
                netFlow += delta;

        return netFlow;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[idx] = (arc){u, v, capacity, capacity, link[u]};
        link[u] = idx++;
        arcs[idx] = (arc){v, u, capacity, 0, link[v]};
        link[v] = idx++;
    }
};

struct task
{
    int processing, arrival, deadline;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int C, P, T, A, R, D;

    cin >> C;
    for (int c = 1; c <= C; c++)
    {
        cin >> P >> T;

        vector<int> duration;
        vector<task> tasks;

        int needed = 0;
        for (int i = 1; i <= T; i++)
        {
            cin >> A >> R >> D;
            needed += R;
            duration.push_back(A); duration.push_back(D);
            tasks.push_back(task{R, A, D});
        }        

        sort(duration.begin(), duration.end());
        duration.erase(unique(duration.begin(), duration.end()), duration.end());

        Dinic dinic(130, 130 * 130, 0, 128);
        for (int i = 1; i < duration.size(); i++)
        {
            dinic.addArc(0, i, P * (duration[i] - duration[i - 1]));
            for (int j = 0; j < tasks.size(); j++)
                if (duration[i - 1] >= tasks[j].arrival && duration[i] <= tasks[j].deadline)
                    dinic.addArc(i, duration.size() + j, duration[i] - duration[i - 1]);
        }
        for (int i = 0; i < tasks.size(); i++)
            dinic.addArc(duration.size() + i, 128, tasks[i].processing);

        cout << (dinic.maxFlow() == needed ? "FEASIBLE" : "NO WAY") << '\n';
    }

    return 0;
}
