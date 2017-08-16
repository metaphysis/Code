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

class graph
{
    int vertices, *visited;
    list<int> *edges;

public:
    graph(int v) { this->vertices = v; edges = new list<int>[v]; visited = new int[v]; }
    ~graph() { delete [] edges; delete [] visited; }

    void findEulerTrail();

    void addEdge(int u, int v) { edges[u].push_back(v); edges[v].push_back(u); }
    void removeEdge(int u, int v);

    void fleury(int u);
    void dfs(int u);
    bool isValidNextEdge(int u, int v);
};

void graph::findEulerTrail()
{
    int u = 0;
    for (int i = 0; i < vertices; i++)
        if (edges[i].size() & 1)
            { u = i; break; }

    fleury(u);

    cout << '\n';
}

void graph::fleury(int u)
{
    for (auto v: edges[u])
        if (v != -1 && isValidNextEdge(u, v))
        {
            cout << u << '-' << v << ' ';
            removeEdge(u, v);
            fleury(v);
        }
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

void graph::removeEdge(int u, int v)
{
    *find(edges[u].begin(), edges[u].end(), v) = -1;
    *find(edges[v].begin(), edges[v].end(), u) = -1;
}

int main(int argc, char *argv[])
{
    graph g1(4);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.findEulerTrail();

    graph g2(3);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0);
    g2.findEulerTrail();

    graph g3(5);
    g3.addEdge(1, 0);
    g3.addEdge(0, 2);
    g3.addEdge(2, 1);
    g3.addEdge(0, 3);
    g3.addEdge(3, 4);
    g3.addEdge(3, 2);
    g3.addEdge(3, 1);
    g3.addEdge(2, 4);
    g3.findEulerTrail();

    return 0;
}
