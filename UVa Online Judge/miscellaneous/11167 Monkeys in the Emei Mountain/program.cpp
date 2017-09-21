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

class EdmondsKarp
{
private:
    arc *arcs;
    int vertices, idx, source, sink, *link, *path, *visited;

public:
    EdmondsKarp(int v, int e, int s, int t)
    {
        vertices = v;
        link = new int[v], path = new int[v], visited = new int[v];
        arcs = new arc[e];
        source = s, sink = t;
        idx = 0;
        memset(link, 0xff, vertices * sizeof(int));
    }

    ~EdmondsKarp()
    {
        delete [] link, path, visited, arcs;
    }

    int maxFlow()
    {
        int netFlow = 0;

        while (true)
        {
            memset(path, 0, vertices * sizeof(int));
            memset(visited, 0xff, vertices * sizeof(int));

            queue<int> unvisited; unvisited.push(source);
            visited[source] = 1;

            while (!unvisited.empty())
            {
                int u = unvisited.front(); unvisited.pop();

                for (int x = link[u]; x != -1; x = arcs[x].next)
                    if (!visited[arcs[x].v] && arcs[x].residual > 0)
                    {
                        unvisited.push(arcs[x].v);
                        visited[arcs[x].v] = 1;
                        path[arcs[x].v] = x;
                    }
            }

            if (!visited[sink]) break;

            int delta = INF;
            for (int x = path[sink]; x != -1; x = path[arcs[x].u])
                delta = min(delta, arcs[x].residual);

            netFlow += delta;
            for (int x = path[sink]; x != -1; x = path[arcs[x].u])
            {
                arcs[x].residual -= delta;
                arcs[x ^ 1].residual += delta;
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

    vector<arc> getArcs(int u)
    {
        vector<arc> as;
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

        EdmondsKarp ek(50200, 11000000, 0, 50150);
        
        memset(drinked, 0, sizeof(drinked));
        
        int flow = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> v >> a >> b;

            flow += v;
            
            ek.addArc(0, i, v);
            for (int j = a; j < b; j++)
            {
                ek.addArc(i, n + j + 1, 1);
                if (drinked[j]) continue;
                ek.addArc(n + j + 1, 50150, m);
                drinked[j] = 1;
            }
        }        

        cout << "Case " << ++cases << ": "; 
        if (ek.maxFlow() == flow)
        {
            cout << "Yes\n";
            for (int i = 1; i <= n; i++)
            {
                vector<int> interval;
                for (auto a : ek.getArcs(i))
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
