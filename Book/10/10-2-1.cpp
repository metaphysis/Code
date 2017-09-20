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
    int vertices, *parent, *rank;

public:
    disjointSet(int v)
    {
        vertices = v;
        parent = new int[v], rank = new int[v];
    }

    ~disjointSet()
    {
        delete [] parent, rank;
    }

    void makeSet()
    {
        for (int i = 0; i < vertices; i++) parent[i] = i, rank[i] = 0;
    }

    int findSet(int x)
    {
        return (x == parent[x] ? x : parent[x] = findSet(parent[x]));
    }

    bool unionSet(int x, int y)
    {
        x = findSet(x), y = findSet(y);
        if (x != y) {
            if (rank[x] > rank[y]) parent[y] = x;
            else {
                parent[x] = y;
                if (rank[x] == rank[y]) rank[x]++;
            }
            return true;
        }
        return  false;
    }
};

class graph
{
private:
    bool isUndirectedGraph;
    int vertices, startOfEulerianTrail, *appeared;
    list<int> *edges;

public:
    graph(int v, bool ug)
    {
        vertices = v;
        edges = new list<int>[v];
        appeared = new int[v];
        memset(appeared, 0, sizeof(int) * v);
        isUndirectedGraph = ug;
    }

    ~graph()
    {
        delete [] edges, appeared;
    }

    bool findEulerianTrail();

    void addEdge(int u, int v);
    void removeEdge(int u, int v);

private:
    bool isEulerian();
    void printTrail(int u, int v);
    void fleury(int u);
    void hierholzer(int u);
    int getConnectedVertices(int u);
    bool isValidNextEdge(int u, int v);
    void deleteEdge(int u, int v);
    void restoreEdge(int u, int v);
};

bool graph::isEulerian()
{
    bool eulerian = true;

    int connected = count(appeared, appeared + vertices, 1);
    for (int u = 0; u < vertices; u++)
        if (appeared[u])
        {
            eulerian = (connected == getConnectedVertices(u));
            break;
        }
    if (!eulerian) return eulerian;

    if (isUndirectedGraph)
    {
        startOfEulerianTrail = 0;

        int odd = 0;
        for (int u = 0; u < vertices; u++)
        {
            if (!appeared[u]) continue;
            if (edges[u].size() & 1)
                odd++, startOfEulerianTrail = u;
        }

        eulerian = (odd == 0 || odd == 2);
    }
    else
    {
        int *id = new int[vertices], *od = new int[vertices];

        memset(id, 0, sizeof(int) * vertices);
        memset(od, 0, sizeof(int) * vertices);

        for (int u = 0; u < vertices; u++)
            for (auto v : edges[u])
                od[u]++, id[v]++;

        int moreOne = 0, lessOne = 0, evenStart = -1, oddStart = -1;
        for (int u = 0; u < vertices; u++)
        {
            if (!appeared[u]) continue;
            int diff = od[u] - id[u];
            if (abs(diff) >= 2) { eulerian = false; break; }
            if (diff == 1 && ++moreOne > 1) { eulerian = false; break; }
            if (diff == -1 && ++lessOne > 1) { eulerian = false; break; }
            if (moreOne  && oddStart < 0) oddStart = u;
            if (diff == 0 && evenStart < 0) evenStart = u;
        }

        delete [] id, od;

        if (moreOne != lessOne) { eulerian = false; }
        startOfEulerianTrail = oddStart >= 0 ? oddStart : evenStart;
    }

    return eulerian;
}

bool graph::findEulerianTrail()
{
    bool eulerian = isEulerian();
    //if (eulerian) fleury(startOfEulerianTrail);
    if (eulerian) hierholzer(startOfEulerianTrail);
    return eulerian;
}

void graph::fleury(int u)
{
    for (auto v : edges[u])
        if (v >= 0 && isValidNextEdge(u, v))
        {
            printTrail(u, v);
            removeEdge(u, v);
            fleury(v);
            break;
        }
}

void graph::hierholzer(int u)
{
    stack<int> path; path.push(u);
    vector<int> circuit;

    int current = u;
    while (!path.empty())
    {
        if (edges[current].size())
        {
            path.push(current);
            int next = edges[current].front();
            edges[current].erase(edges[current].begin());
            current = next;
        }
        else
        {
            circuit.push_back(current);
            current = path.top();
            path.pop();
        }
    }

    for (int i = circuit.size() - 1; i > 0; i--)
        printTrail(circuit[i], circuit[i - 1]);
}

void graph::printTrail(int u, int v)
{
    cout << u << "->" << v << ' ';
}

bool graph::isValidNextEdge(int u, int v)
{
    int connected = 0;
    for (auto v : edges[u])
        if (v >= 0)
            connected++;
    if (connected == 1) return true;

    int connected1 = getConnectedVertices(u);
    deleteEdge(u, v);
    int connected2 = getConnectedVertices(u);
    restoreEdge(u, v);

    return connected1 == connected2;
}

int graph::getConnectedVertices(int source)
{
    disjointSet ds(vertices);
    ds.makeSet();

    for (int u = 0; u < vertices; u++)
        for (auto v : edges[u])
            if (v >= 0 && ds.findSet(u) != ds.findSet(v))
                ds.unionSet(u, v);

    int connected = 0;
    for (int u = 0; u < vertices; u++)
        if (ds.findSet(source) == ds.findSet(u))
            connected++;

    return connected;
}

void graph::addEdge(int u, int v)
{
    appeared[u] = appeared[v] = 1;
    edges[u].push_back(v);
    if (isUndirectedGraph) edges[v].push_back(u);
}

void graph::removeEdge(int u, int v)
{
    *find(edges[u].begin(), edges[u].end(), v) = -1;
    if (isUndirectedGraph) *find(edges[v].begin(), edges[v].end(), u) = -1;
}

void graph::restoreEdge(int u, int v)
{
    *find(edges[u].begin(), edges[u].end(), -2) = v;
    if (isUndirectedGraph) *find(edges[v].begin(), edges[v].end(), -2) = u;  
}

void graph::deleteEdge(int u, int v)
{
    *find(edges[u].begin(), edges[u].end(), v) = -2;
    if (isUndirectedGraph) *find(edges[v].begin(), edges[v].end(), u) = -2;    
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
