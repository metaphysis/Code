// Monkeys in the Emei Mountain
// UVa ID: 11167
// Verdict: Accepted
// Submission Date: 2017-09-23
// UVa Run Time: 0.600s
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

    vector<vector<arc>> getArcs(int interval, int monkeys)
    {
        vector<vector<arc>> as(monkeys, vector<arc>());
        for (int u = 1; u <= interval; u++)
            for (int i = link[u]; i != -1; i = arcs[i].next)
                if (arcs[i].v != sink && arcs[i].v != source)
                    as[arcs[i].v - (interval + 1)].push_back(arcs[i]);
        return as;
    }
};

struct monkey
{
    int units, start, end;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n, m, v, a, b;

    while (cin >> n, n > 0)
    {
        cin >> m;

        vector<int> duration;
        vector<monkey> monkeys;

        int needed = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> v >> a >> b;
            needed += v;
            duration.push_back(a); duration.push_back(b);
            monkeys.push_back(monkey{v, a, b});
        }        

        // 去除重复的时间点。
        sort(duration.begin(), duration.end());
        duration.erase(unique(duration.begin(), duration.end()), duration.end());

        // 设置流量网络的最大顶点数为400，有向弧的数量最大为400*400；
        // 指定源点的序号为0，汇点的序号为320。
        Dinic dinic(400, 400 * 400, 0, 320);
        for (int i = 1; i < duration.size(); i++)
        {
            dinic.addArc(0, i, m * (duration[i] - duration[i - 1]));
            for (int j = 0; j < monkeys.size(); j++)
                if (duration[i - 1] >= monkeys[j].start && duration[i] <= monkeys[j].end)
                    dinic.addArc(i, duration.size() + j, duration[i] - duration[i - 1]);
        }
        for (int i = 0; i < monkeys.size(); i++)
            dinic.addArc(duration.size() + i, 320, monkeys[i].units);

        // 使用最大流算法确定是否存在可行的安排方案，若存在则根据正向弧
        // 的容量使用情况安排时间段。
        cout << "Case " << ++cases << ": ";
        if (dinic.maxFlow() < needed) { cout << "No\n"; continue; }
        cout << "Yes\n";

        vector<int> idx(duration.size(), 0), periods[n];
        vector<vector<arc>> arcs = dinic.getArcs(duration.size() - 1, n);

        for (int i = 0; i < arcs.size(); i++)
            for (auto r : arcs[i])
            {
                int provided = r.capacity - r.residual, u = r.u - 1;

                vector<int> hours;
                for (int j = 1; j <= provided; j++)
                {
                    if (idx[u] == duration[u + 1] - duration[u]) idx[u] = 0;
                    hours.push_back(duration[r.u - 1] + idx[u]);
                    idx[u]++;
                }

                sort(hours.begin(), hours.end());

                for (auto hour : hours)
                {
                    if (!periods[i].size() || hour != periods[i].back())
                    {
                        periods[i].push_back(hour);
                        periods[i].push_back(hour + 1);
                        continue;
                    }
                    periods[i].back()++;
                }
            }

        for (int i = 0; i < n; i++)
        {
            cout << periods[i].size() / 2 ;
            for (int j = 0; j < periods[i].size(); j += 2)
                cout << " (" << periods[i][j] << ',' << periods[i][j + 1] << ')';
            cout << '\n';
        }
    }

    return 0;
}
