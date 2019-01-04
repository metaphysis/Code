const int MAXV = 1010, INF = 0x7f7f7f7f;

struct edge
{
    int v, weight;
    edge (int v = 0, int weight = 0): v(v), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
};

vector<edge> edges[MAXV];
int cntOfVertices, parent[MAXV], distToTree[MAXV], intree[MAXV];

int prim(int u)
{
    int minSumOfWeight = 0;

    for (int i = 0; i < cntOfVertices; i++)
        parent[i] = -1, intree[i] = 0, distToTree[i] = INF;

    priority_queue<edge> q;
    q.push(edge(u, 0));

    while (!q.empty()) {
        edge e1 = q.top(); q.pop();
        if (intree[e1.v]) continue;
        intree[e1.v] = 1, minSumOfWeight += e1.weight;
        for (auto e2 : edges[u])
            if (!intree[e2.v] && distToTree[e2.v] > e2.weight) {
                distToTree[e2.v] = e2.weight;
                parent[e2.v] = e1.v;
                q.push(edge(e2.v, e2.weight));
            }
    }

    return minSumOfWeight;
}
