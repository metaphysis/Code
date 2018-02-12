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
#include <vector>

using namespace std;

const int MAXV = 1010, INF = 0x3f3f3f3f;

struct edge
{
    int idx, weight;
    bool operator<(const edge &e) const { return weight > e.weight; }
};

vector<edge> edges[MAXV];
int n, parent[MAXV], distToTree[MAXV], intree[MAXV];

int prim(int u)
{
    int minWeightSum = 0;

    for (int i = 0; i < n; i++) {
        parent[i] = -1; intree[i] = 0; distToTree[i] = INF;
    }

    distToTree[u] = 0;
    while (!intree[u]) {
        intree[u] = 1;
        minWeightSum += distToTree[u];

        for (int i = 0; i < edges[u].size(); i++) {
            edge v = edges[u][i];
            if (!intree[v.idx] && distToTree[v.idx] > v.weight) {
                distToTree[v.idx] = v.weight;
                parent[v.idx] = u;
            }
        }

        int minDistToTree = INF;
        for (int i = 0; i < n; i++) {
            if (!intree[i] && minDistToTree > distToTree[i]) {
                minDistToTree = distToTree[i];
                u = i;
            }
        }
    }

    return minWeightSum;
}

int prim1(int u)
{
    int minWeightSum = 0;

    for (int i = 0; i < n; i++) {
        parent[i] = -1; intree[i] = 0; distToTree[i] = INF;
    }

    priority_queue<edge> unvisited;
    unvisited.push((edge){u, 0});

    while (!unvisited.empty()) {
        edge v = unvisited.top(); unvisited.pop();

        if (intree[v.idx]) continue;
        intree[v.idx] = 1;
        minWeightSum += v.weight;

        for (int i = 0; i < edges[v.idx].size(); i++) {
            edge e = edges[v.idx][i];
            if (!intree[e.idx] && distToTree[e.idx] > e.weight) {
                distToTree[e.idx] = e.weight;
                parent[e.idx] = v.idx;
            }
        }
    }

    return minWeightSum;
}

int main(int argc, char *argv[])
{
    prim(0);
    prim1(0);

    return 0;
}
