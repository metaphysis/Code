const int MAXV = 110, MAXE = 10010, MAX_DIST = 1000000;

struct edge {
    int from, to, weight, next;
};

edge edges[MAXE];
int first[MAXV], number_of_vertices, number_of_edges;
int dist_to_tree[MAXV], intree[MAXV], parent[MAXV], used[MAXE];
int idx[MAXV][MAXV], max_edge[MAXV][MAXV];

void prim(int u)
{
    // 最小边权和。
    int min_weight_sum = 0;

    // 初始化。
    for (int i = 0; i < number_of_vertices; i++) {
        dist_to_tree[i] = MAX_DIST, intree[i] = 0, parent[i] = -1;
        for (int j = 0; j < number_of_vertices; j++)
            max_edge[i][j] = 0;
    }

    // 将指定的顶点置为已在树中。
    dist_to_tree[u] = 0;

    while (!intree[u]) {
        // 更新树中顶点与拟加入顶点间通路上的最大边权。
        for (int i = 0; i < number_of_vertices; i++) {
            if (intree[i]) {
                int weight = edges[idx[parent[u]][u]].weight;

                if (i != parent[u])
                    max_edge[i][u] = max(max_edge[i][parent[u]], weight);
                else
                    max_edge[i][u] = weight;

                // 根据对称性更新最大边权。
                max_edge[u][i] = max_edge[i][u];
            }
        }

        // 将顶点加入最小生成树并累加边权和。
        intree[u] = 1;
        min_weight_sum += dist_to_tree[u];

        // 更新尚未进入树中的顶点与树的距离。
        for (int i = first[u]; i != -1; i = edges[i].next) {
            edge v = edges[i];
            if (!intree[v.to] && dist_to_tree[v.to] > v.weight) {
                dist_to_tree[v.to] = v.weight;
                parent[v.to] = u;
            }
        }

        // 选取尚未进入树中且与树具有最小距离的顶点。
        int min_dist_to_tree = MAX_DIST;
        for (int i = 0; i < number_of_vertices; i++) {
            if (!intree[i] && min_dist_to_tree > dist_to_tree[i]) {
                min_dist_to_tree = dist_to_tree[i];
                u = i;
            }
        }
    }

    // 标记已经使用的边。
    memset(used, 0, sizeof(used));
    for (int i = 0; i < number_of_vertices; i++) {
        if (parent[i] != -1)
            used[idx[i][parent[i]]] = used[idx[parent[i]][i]] = 1;
    }

    // 逐一枚举尚未使用的边，寻找替换后的最小边权差。
    int min_weight_diff = MAX_DIST;
    for (int i = 0; i < number_of_edges; i++)
        if (!used[i]) {
            int diff = edges[i].weight - max_edge[edges[i].from][edges[i].to];
            if (min_weight_diff > diff) min_weight_diff = diff;
        }

    cout << min_weight_sum << ' ';
    cout << (min_weight_sum + min_weight_diff) << '\n';
}
