// http://www.geeksforgeeks.org/fleurys-algorithm-for-printing-eulerian-path/, 2017.

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

class disjointSet
{
private:
    int vertices, *parent, *ranks;
    
public:
    disjointSet(int v)
    {
        vertices = v;
        parent = new int[v], ranks = new int[v];
    }
    
    ~disjointSet()
    {
        delete [] parent, ranks;
    }

    void makeSet()
    {
        for (int i = 0; i < vertices; i++) parent[i] = i, ranks[i] = 0;
    }

    int findSet(int x)
    {
        return (x == parent[x] ? x : parent[x] = findSet(parent[x]));
    }

    bool unionSet(int x, int y)
    {
        x = findSet(x), y = findSet(y);
        if (x != y) {
            if (ranks[x] > ranks[y]) parent[y] = x;
            else {
                parent[x] = y;
                if (ranks[x] == ranks[y]) ranks[y]++;
            }
            return true;
        }
        return false;
    }
};

class graph
{
private:
    bool undirected;
    int vertices, start, *visited;
    list<int> *edges;

public:
    graph(int v, bool undirected)
    {
        vertices = v;
        edges = new list<int>[v];
        visited = new int[v];
        undirected = undirected;
    }

    ~graph()
    {
        delete [] edges, visited;
    }

    bool findEulerianTrail();

    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    
private:
    bool isEulerian();
    void printTrail(int u, int v);

    void fleury(int u);
    void dfs(int u);
    bool isValidNextEdge(int u, int v);
};

bool graph::isEulerian()
{
    bool eulerian = true;

    if (undirected)
    {
        start = 0;

        int odd = 0;
        for (int u = 0; u < vertices; u++)
            if (edges[u].size() & 1)
            {
                odd++;
                start = u;
            }

        eulerian = (odd == 0 || odd == 2);
    }
    else
    {
        int *in = new int[vertices], *out = new int[vertices];

        memset(in, 0, sizeof(int) * vertices);
        memset(out, 0, sizeof(int) * vertices);

        for (int u = 0; u < vertices; u++)
            for (auto v : edges[u])
                out[u]++, in[v]++;

        start = 0;

        int moreOne = 0, lessOne = 0;
        for (int u = 0; u < vertices; u++)
        {
            int diff = in[u] - out[u];
            if (abs(in[u] - out[u]) >= 2 ||
                (diff == 1 && ++moreOne > 1) || (diff == -1 && ++lessOne > 1))
                { eulerian = false; break; }
            if (diff == 1) start = u;
        }
        if (moreOne != lessOne) { eulerian = false; }
        
        delete [] in, out;
    }
    
    if (eulerian)
    {
        disjointSet ds(vertices);
        ds.makeSet();
        for (int u = 0; u < vertices; u++)
            for (auto v : edges[u])
                if (ds.findSet(u) != ds.findSet(v))
                    ds.unionSet(u, v);
        for (int u = 1; u < vertices; u++)
            if (ds.findSet(0) != ds.findSet(u))
                { eulerian = false; break; }
    }
    
    return eulerian;
}

bool graph::findEulerianTrail()
{
    bool eulerian = isEulerian();
    if (eulerian) fleury(start);
    return eulerian;
}

void graph::fleury(int u)
{
    for (auto v: edges[u])
        if (v != -1 && isValidNextEdge(u, v))
        {
            printTrail(u, v);
            removeEdge(u, v);
            fleury(v);
        }
}

void graph::printTrail(int u, int v)
{
    cout << u << '.' << v << ' ';
}

bool graph::isValidNextEdge(int u, int v)
{
    int connected = 0;
    for (auto iv : edges[u]) if (iv != - 1) connected++;
    if (connected == 1) return true;

    memset(visited, 0, sizeof(int) * vertices);
    dfs(u);
    int count1 = count(visited, visited + vertices, 1);

    removeEdge(u, v);
    memset(visited, 0, sizeof(int) * vertices);
    dfs(u);
    int count2 = count(visited, visited + vertices, 1);

    addEdge(u, v);

    return count1 == count2;
}

void graph::dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (v != -1 && !visited[v])
            dfs(v);
}

void graph::addEdge(int u, int v)
{
    edges[u].push_back(v);
    if (undirected) edges[v].push_back(u);
}

void graph::removeEdge(int u, int v)
{
    *find(edges[u].begin(), edges[u].end(), v) = -1;
    if (undirected) *find(edges[v].begin(), edges[v].end(), u) = -1;
}

int main(int argc, char * argv[])
{
    graph g1(4, true);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.findEulerianTrail();

    graph g2(3, true);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0);
    g2.findEulerianTrail();

    graph g3(5, true);
    g3.addEdge(1, 0);
    g3.addEdge(0, 2);
    g3.addEdge(2, 1);
    g3.addEdge(0, 3);
    g3.addEdge(3, 4);
    g3.addEdge(3, 2);
    g3.addEdge(3, 1);
    g3.addEdge(2, 4);
    g3.findEulerianTrail();
    
    return 0;
}
