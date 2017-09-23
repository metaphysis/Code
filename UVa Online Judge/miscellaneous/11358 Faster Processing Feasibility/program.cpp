// Faster Processing Feasibility
// UVa ID: 11358
// Verdict: Accepted
// Submission Date: 2017-09-23
// UVa Run Time: 0.200s
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

class EdmondsKarp
{
private:
    arc *arcs;
    int vertices, idx, source, sink, *link, *parent, *visited;

    bool bfs()
    {
        memset(parent, 0xff, vertices * sizeof(int));
        memset(visited, 0, vertices * sizeof(int));

        queue<int> unvisited; unvisited.push(source);
        visited[source] = 1;

        while (!unvisited.empty())
        {
            int u = unvisited.front(); unvisited.pop();
            for (int i = link[u]; i != -1; i = arcs[i].next)
                if (!visited[arcs[i].v] && arcs[i].residual > 0)
                {
                    unvisited.push(arcs[i].v);
                    visited[arcs[i].v] = 1;
                    parent[arcs[i].v] = i;
                }
        }

        return visited[sink];
    }

public:
    EdmondsKarp(int v, int e, int s, int t)
    {
        vertices = v;
        link = new int[v], parent = new int[v], visited = new int[v], arcs = new arc[e];
        idx = 0, source = s, sink = t;
        memset(link, 0xff, vertices * sizeof(int));
    }

    ~EdmondsKarp()
    {
        delete [] link, parent, visited, arcs;
    }

    int maxFlow()
    {
        int netFlow = 0;

        while (bfs())
        {
            int delta = INF;
            for (int i = parent[sink]; i != -1; i = parent[arcs[i].u])
                delta = min(delta, arcs[i].residual);

            netFlow += delta;
            for (int i = parent[sink]; i != -1; i = parent[arcs[i].u])
            {
                arcs[i].residual -= delta;
                arcs[i ^ 1].residual += delta;
            }
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

        EdmondsKarp ek(130, 130 * 130, 0, 128);
        for (int i = 1; i < duration.size(); i++)
        {
            ek.addArc(0, i, P * (duration[i] - duration[i - 1]));
            for (int j = 0; j < tasks.size(); j++)
                if (duration[i - 1] >= tasks[j].arrival && duration[i] <= tasks[j].deadline)
                    ek.addArc(i, duration.size() + j, duration[i] - duration[i - 1]);
        }
        for (int i = 0; i < tasks.size(); i++)
            ek.addArc(duration.size() + i, 128, tasks[i].processing);

        cout << (ek.maxFlow() == needed ? "FEASIBLE" : "NO WAY") << '\n';
    }

    return 0;
}
