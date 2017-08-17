// Catenyms
// UVa ID: 10441
// Verdict: Accepted
// Submission Date: 2017-08-13
// UVa Run Time: 0.000s
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

vector<string> dictionary[26], trail;

class disjointSet
{
private:
    int numberOfVertices, *parent, *rank;

public:
    disjointSet(int v)
    {
        numberOfVertices = v;
        parent = new int[v], rank = new int[v];
    }

    ~disjointSet()
    {
        delete [] parent, rank;
    }

    void makeSet()
    {
        for (int i = 0; i < numberOfVertices; i++) parent[i] = i, rank[i] = 0;
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
                if (rank[x] == rank[y]) rank[y]++;
            }
            return true;
        }
        return false;
    }
};

class graph
{
private:
    bool isUndirectedGraph;
    int numberOfVertices, startOfEulerianTrail, *visited, *appeared;
    list<int> *edges;

public:
    graph(int v, bool ug)
    {
        numberOfVertices = v;
        edges = new list<int>[v];
        visited = new int[v];
        appeared = new int[v];
        memset(appeared, 0, sizeof(int) * v);
        isUndirectedGraph = ug;
    }

    ~graph()
    {
        delete [] edges, visited, appeared;
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

    if (eulerian)
    {
        disjointSet ds(numberOfVertices);
        ds.makeSet();

        for (int u = 0; u < numberOfVertices; u++)
            for (auto v : edges[u])
                if (ds.findSet(u) != ds.findSet(v))
                    ds.unionSet(u, v);

        for (int first = -1, u = 0; u < numberOfVertices; u++)
        {
            if (!appeared[u]) continue;
            if (first == -1) first = u;
            if (ds.findSet(first) != ds.findSet(u))
            {
                eulerian = false;
                break;
            }
        }
    }

    if (!eulerian) return eulerian;

    if (isUndirectedGraph)
    {
        startOfEulerianTrail = 0;

        int odd = 0;
        for (int u = 0; u < numberOfVertices; u++)
        {
            if (!appeared[u]) continue;
            if (edges[u].size() & 1)
                odd++, startOfEulerianTrail = u;
        }

        eulerian = (odd == 0 || odd == 2);
    }
    else
    {
        int *id = new int[numberOfVertices], *od = new int[numberOfVertices];

        memset(id, 0, sizeof(int) * numberOfVertices);
        memset(od, 0, sizeof(int) * numberOfVertices);

        for (int u = 0; u < numberOfVertices; u++)
            for (auto v : edges[u])
                od[u]++, id[v]++;

        int moreOne = 0, lessOne = 0, evenStart = -1, oddStart = -1;
        for (int u = 0; u < numberOfVertices; u++)
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
    if (eulerian) fleury(startOfEulerianTrail);
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
    trail.push_back(dictionary[u].front());
    dictionary[u].erase(dictionary[u].begin());
}

bool graph::isValidNextEdge(int u, int v)
{
    int connected = 0;
    for (auto iv : edges[u]) if (iv != -1) connected++;
    if (connected == 1) return true;

    memset(visited, 0, sizeof(int) * numberOfVertices);
    dfs(u);
    int count1 = count(visited, visited + numberOfVertices, 1);

    removeEdge(u, v);
    memset(visited, 0, sizeof(int) * numberOfVertices);
    dfs(u);
    int count2 = count(visited, visited + numberOfVertices, 1);

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
    appeared[u] = appeared[v] = 1;
    edges[u].push_back(v);
    if (isUndirectedGraph) edges[v].push_back(u);
}

void graph::removeEdge(int u, int v)
{
    *find(edges[u].begin(), edges[u].end(), v) = -1;
    if (isUndirectedGraph) *find(edges[v].begin(), edges[v].end(), u) = -1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    string word;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;

        vector<string> words;
        for (int i = 0; i < n; i++)
        {
            cin >> word;
            words.push_back(word);
        }
        sort(words.begin(), words.end());

        for (int i = 0; i < 26; i++) dictionary[i].clear();

        graph g(26, false);
        for (int i = 0; i < n; i++)
        {
            word = words[i];
            int u = word.front() - 'a', v = word.back() - 'a';
            g.addEdge(u, v);
            dictionary[u].push_back(word);
        }

        trail.clear();
        if (!g.findEulerianTrail()) cout << "***";
        else
        {
            for (int i = 0; i < trail.size(); i++)
            {
                if (i > 0) cout << '.';
                cout << trail[i];
            }
        }
        cout << '\n';
    }

    return 0;
}
