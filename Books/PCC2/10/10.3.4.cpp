#include <bits/stdc++.h>
using namespace std;

const int MAXV = 110, MAXE = 10010, INF = 0x7f7f7f7f;

struct edge {
    int u, v, w;
    edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
    bool operator<(const edge &e) const { return w < e.w; }
} edges[MAXE];

vector<edge> g[MAXV], ue;
int n, m;

// 并查集
int parent[MAXV];
void makeSet() {
    for (int i = 0; i < n; i++) parent[i] = i;
}
int findSet(int x) {
    return parent[x] == x ? x : parent[x] = findSet(parent[x]);
}
bool unionSet(int x, int y) {
    x = findSet(x), y = findSet(y);
    if (x == y) return false;
    parent[x] = y;
    return true;
}

// 将边列表中序号为 i 的边添加到无向图中
void addEdge(int i) {
    edge e = edges[i];
    g[e.u].push_back(edge(i, e.v, e.w));
    g[e.v].push_back(edge(i, e.u, e.w));
}

int chosen[MAXE], connected[MAXV], longest[MAXV], linked[MAXV];

// 通过 DFS 确定根结点到其他顶点的路径上、且不含与根关联树边的最长边
void dfs(int father, int u) {
    for (auto e : g[u]) {
        if (!chosen[e.u]) continue;
        if (e.v == father) continue;
        if (~father) {
            longest[e.v] = e.w;
            linked[e.v] = e.u;
            if (longest[u] > longest[e.v]) {
                longest[e.v] = longest[u];
                linked[e.v] = linked[u];
            }
        } else {
            // u 为根 v0 时，其直接孩子的路径上不含与 v0 关联的树边
            longest[e.v] = -INF;
        }
        dfs(u, e.v);
    }
}

// 确定以顶点 u 为根的单顶点 k 度限制最小生成树
int kdbmst(int u, int k) {
    memset(chosen, 0, sizeof(chosen));
    makeSet();
    sort(edges, edges + m);

    ue.clear();
    for (int i = 0; i < m; i++) {
        edge e = edges[i];
        if (e.u == u) {
            ue.push_back(edge(i, e.v, e.w));
            continue;
        }
        if (e.v == u) {
            ue.push_back(edge(i, e.u, e.w));
            continue;
        }
        if (unionSet(e.u, e.v)) chosen[i] = 1;
    }

    // 确定最小生成树森林的分支数
    int components = 0;
    memset(connected, 0, sizeof(connected));
    connected[u] = 0;
    for (int i = 0; i < n; i++) {
        if (i != u && findSet(i) == i) {
            components++;
            connected[i] = 0;
        }
    }
    if (components > k) return INF;

    // 将指定顶点 u 与各个连通分支连接
    sort(ue.begin(), ue.end());
    for (auto e : ue) {
        int eid = e.u, scc = findSet(e.v);
        if (!connected[scc]) connected[scc] = chosen[eid] = 1;
    }

    // 检查所有连通分支是否均有边连接
    for (int i = 0; i < n; i++) {
        if (i != u && findSet(i) == i) {
            if (!connected[i]) return INF;
        }
    }

    // 生成以 u 为根的图
    for (int i = 0; i < n; i++) g[i].clear();
    for (int i = 0; i < m; i++) {
        if (chosen[i]) addEdge(i);
    }

    // 尝试替换边，增加顶点 u 的度
    while (components < k) {
        dfs(-1, u);
        int delta = INF, selected = -1, selectedEdge = -1;
        for (auto e : ue) {
            if (chosen[e.u]) continue;
            // u 的直接孩子路径上没有可删除的非 u 关联树边，不能增加度
            if (longest[e.v] == -INF) continue;
            int d = e.w - longest[e.v];
            if (d < delta) {
                delta = d;
                selected = e.v;
                selectedEdge = e.u;
            }
        }
        // 若不存在可替换的边则退出，否则更新最小生成树
        if (selectedEdge == -1 || delta == INF) return INF;
        chosen[linked[selected]] = 0;
        chosen[selectedEdge] = 1;
        addEdge(selectedEdge);
        components++;
    }

    // 统计最小生成树的边权和
    int sum = 0;
    for (int i = 0; i < m; i++) {
        if (chosen[i]) sum += edges[i].w;
    }
    return sum;
}

// 暴力枚举，用于验证 kdbmst
int bruteKDBMST(int n, int u, int k, const vector<edge> &es) {
    int m = (int)es.size();
    int ans = INF;

    for (int mask = 0; mask < (1 << m); mask++) {
        if (__builtin_popcount(mask) != n - 1) continue;

        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        function<int(int)> find = [&](int x) {
            return p[x] == x ? x : p[x] = find(p[x]);
        };

        int deg = 0, sum = 0;
        bool ok = true;

        for (int i = 0; i < m; i++) {
            if ((mask >> i) & 1) {
                int a = es[i].u, b = es[i].v, w = es[i].w;
                if (a == u) deg++;
                if (b == u) deg++;

                int ra = find(a), rb = find(b);
                if (ra == rb) {
                    ok = false;
                    break;
                }
                p[ra] = rb;
                sum += w;
            }
        }

        if (!ok) continue;
        if (deg != k) continue;

        // n-1 条无环边一定连通
        ans = min(ans, sum);
    }

    return ans;
}

int main() {
    srand((unsigned)time(0));

    for (int tc = 1; tc <= 1000; tc++) {
        n = rand() % 5 + 2;  // 2..6
        int maxM = min(10, n * (n - 1) / 2 + 2);
        m = rand() % maxM + 1;

        vector<edge> input;
        for (int i = 0; i < m; i++) {
            int a = rand() % n;
            int b = rand() % n;
            while (b == a) b = rand() % n;
            int w = rand() % 20 + 1;
            input.push_back(edge(a, b, w));
        }

        for (int u = 0; u < n; u++) {
            for (int k = 1; k <= n - 1; k++) {
                // kdbmst 会排序全局 edges，每次重新复制
                for (int i = 0; i < m; i++) edges[i] = input[i];

                int got = kdbmst(u, k);
                int expect = bruteKDBMST(n, u, k, input);

                if (got != expect) {
                    cout << "Mismatch! tc=" << tc
                         << " n=" << n << " m=" << m
                         << " u=" << u << " k=" << k << "\n";
                    cout << "got=" << (got == INF ? -1 : got)
                         << " expect=" << (expect == INF ? -1 : expect) << "\n";
                    cout << "Edges:\n";
                    for (auto &e : input) {
                        cout << e.u << "-" << e.v << " w=" << e.w << "\n";
                    }
                    return 1;
                }
            }
        }
    }

    cout << "All tests passed!\n";
    return 0;
}
