// Transportation System
// UVa ID: 11228
// Verdict: Accepted
// Submission Date: 2018-02-05
// UVa Run Time: 0.070s
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

const int MAXV = 1010;

struct edge
{
    int from, to, weight;
    edge (int from = 0, int to = 0, int weight = 0): from(from), to(to), weight(weight) {}
    bool operator<(const edge& x) const {
        return weight < x.weight;
    }
};

edge edges1[1000010], edges2[1000010];
int parent[MAXV], ranks[MAXV];
int n, m1, m2;
map<string, int> indexer;

void makeSet()
{
    for (int i = 0; i < n; i++) {
        parent[i] = i; ranks[i] = 0;
    }
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, r, xs[MAXV], ys[MAXV];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> r;
        for (int i = 0; i < n; i++)
            cin >> xs[i] >> ys[i];

        m1 = m2 = 0;
        int threshold = r * r;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                int dist = (xs[i] - xs[j]) * (xs[i] - xs[j]) + (ys[i] - ys[j]) * (ys[i] - ys[j]);
                if (dist <= threshold)
                    edges1[m1++] = edge(i, j, dist);
                else
                    edges2[m2++] = edge(i, j, dist);
            }

        makeSet();

        // Road.
        int merged = 0;
        double roads = 0.0;
        sort(edges1, edges1 + m1);
        for (int i = 0; i < m1; i++)
            if (unionSet(edges1[i].from, edges1[i].to))
            {
                merged++;
                roads += sqrt(edges1[i].weight);
            }

        // Railroad.
        double railroads = 0.0;
        sort(edges2, edges2 + m2);
        for (int i = 0; i < m2; i++)
            if (unionSet(edges2[i].from, edges2[i].to))
                    railroads += sqrt(edges2[i].weight);

        cout << "Case #" << c << ": " << (n - merged);
        cout << ' ' << fixed << setprecision(0) << roads;
        cout << ' ' << fixed << setprecision(0) << railroads << '\n';
    }

    return 0;
}
