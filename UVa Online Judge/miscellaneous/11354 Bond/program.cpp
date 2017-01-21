// Bond
// UVa ID: 11354
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
#include <vector>

using namespace std;

const int MAXV = 50010, MAXE = 100010, MAX_DIST = 1000000;

struct edge {
    int from, to, weight, next;
};

struct node
{
    int from, dist;
    
    bool operator<(const node& x) const {
        return dist > x.dist;
    }
};

edge edges[MAXE];
int first[MAXV], N, M, E, Q;
int dist_to_tree[MAXV], intree[MAXV], parent[MAXV];
map<int, int> idx, max_edge;

void prim(int u)
{
    // 初始化。
    for (int i = 0; i < N; i++) {
        dist_to_tree[i] = MAX_DIST, intree[i] = 0, parent[i] = -1;
        for (int j = 0; j < N; j++) max_edge[i * N + j] = 0;
    }

    // 将指定的顶点置为已在树中。
    dist_to_tree[u] = 0;
    priority_queue<node> unvisited;
    unvisited.push((node){u, 0});

    while (!unvisited.empty()) {
        node current = unvisited.top();
        unvisited.pop();

        u = current.from;
        if (intree[u]) continue;

        // 更新树中顶点与拟加入顶点间通路上的最大边权。
        for (int i = 0; i < N; i++) {
            if (intree[i]) {
                int weight = edges[idx[parent[u] * N + u]].weight;

                if (i != parent[u])
                    max_edge[i * N + u] = max(max_edge[i * N + parent[u]], weight);
                else
                    max_edge[i * N + u] = weight;

                // 根据对称性更新最大边权。
                max_edge[u * N + i] = max_edge[i * N + u];
            }
        }

        // 将顶点加入最小生成树。
        intree[u] = 1;

        // 更新尚未进入树中的顶点与树的距离。
        for (int i = first[u]; i != -1; i = edges[i].next) {
            edge v = edges[i];
            if (!intree[v.to] && dist_to_tree[v.to] > v.weight) {
                dist_to_tree[v.to] = v.weight;
                parent[v.to] = u;
                unvisited.push((node){v.to, dist_to_tree[v.to]});
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, s, t, w;

    while (cin >> N >> M) {
        for (int i = 0; i < N; i++) {
            first[i] = -1;
            for (int j = i; j < N; j++) idx[i * N + j] = idx[j * N + i] = -1;
        }

        E = 0;
        for (int i = 0; i < M; i++)
        {
            cin >> s >> t >> w;

            s--, t--;
            edges[E] = (edge){s, t, w, first[s]}, first[s] = E++;
            edges[E] = (edge){t, s, w, first[t]}, first[t] = E++;

            if (idx[s * N + t] == -1 || w < edges[idx[s * N + t]].weight)
                idx[s * N + t] = first[s], idx[t * N + s] = first[t];
        }

        prim(0);

        if (cases++ > 0) cout << '\n';
        cin >> Q;
        for (int i = 1; i <= Q; i++)
        {
            cin >> s >> t;
            s--, t--;
            cout << max_edge[s * N + t] << '\n';
        }
    }

    return 0;
}
