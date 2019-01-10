const int MAXV = 110, MAXE = 12100, INF = 0x7f7f7f7f;

struct edge { int u, v, weight, next; } edges[MAXE];

int head[MAXV], n, m;
int distToTree[MAXV], intree[MAXV], parent[MAXV], used[MAXE];
int idx[MAXV][MAXV], maxEdge[MAXV][MAXV];

void prim(int u)
{
    int minSumOfWeight = 0;

    for (int i = 0; i < n; i++) {
        distToTree[i] = INF, intree[i] = 0, parent[i] = -1;
        for (int j = 0; j < n; j++)
            maxEdge[i][j] = 0;
    }

    distToTree[u] = 0;

    while (!intree[u]) {
        for (int i = 0; i < n; i++) {
            if (intree[i]) {
                int weight = edges[idx[parent[u]][u]].weight;

                if (i != parent[u])
                    maxEdge[i][u] = max(maxEdge[i][parent[u]], weight);
                else
                    maxEdge[i][u] = weight;

                maxEdge[u][i] = maxEdge[i][u];
            }
        }

        intree[u] = 1;
        minSumOfWeight += distToTree[u];

        for (int i = head[u]; i != -1; i = edges[i].next) {
            edge e = edges[i];
            if (!intree[e.v] && distToTree[e.v] > e.weight)
                distToTree[e.v] = e.weight, parent[e.v] = u;
                parent[e.v] = u;
        }

        int minDistToTree = INF;
        for (int i = 0; i < n; i++)
            if (!intree[i] && minDistToTree > distToTree[i])
                minDistToTree = distToTree[i], u = i;
    }

    memset(used, 0, sizeof(used));
    for (int i = 0; i < n; i++) {
        if (~parent[i])
            used[idx[i][parent[i]]] = used[idx[parent[i]][i]] = 1;
    }

    int minWeightDiff = INF;
    for (int i = 0; i < m; i++)
        if (!used[i]) {
            int diff = edges[i].weight - maxEdge[edges[i].u][edges[i].v];
            if (minWeightDiff > diff) minWeightDiff = diff;
        }

    cout << minSumOfWeight << ' ' << (minSumOfWeight + minWeightDiff) << '\n';
}
