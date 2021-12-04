const int MAXV = 1010, INF = 0x7f7f7f7f;

struct edge
{
    int v, weight;
};

vector<edge> edges[MAXV];
int n, parent[MAXV], distToTree[MAXV], intree[MAXV];

int prim(int u)
{
    int minSumOfWeight = 0;

    for (int i = 0; i < n; i++)
        parent[i] = -1, intree[i] = 0, distToTree[i] = INF;

    distToTree[u] = 0;
    while (!intree[u]) {
        intree[u] = 1, minSumOfWeight += distToTree[u];

        for (auto e : edges[u])
            if (!intree[e.v] && distToTree[e.v] > e.weight)
                distToTree[e.v] = e.weight, parent[e.v] = u;

        int minDistToTree = INF;
        for (int i = 0; i < n; i++)
            if (!intree[i] && minDistToTree > distToTree[i])
                minDistToTree = distToTree[i], u = i;
    }

    return minSumOfWeight;
}
