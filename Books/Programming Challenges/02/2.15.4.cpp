#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;   // 最大结点数
const int MAXQ = 100010;   // 最大查询数
const int MAXLOG = 18;     // 倍增表大小

vector<int> g[MAXN + 5];

// color: 原颜色；colorCompressed: 离散化后的颜色
int color[MAXN + 5], colorCompressed[MAXN + 5];

// 欧拉序：每个结点进入、离开各记录一次，长度最多 2N
int euler[MAXN * 2 + 5];
int first[MAXN + 5], last[MAXN + 5];

// 倍增求 LCA
int depth[MAXN + 5];
int parent[MAXN + 5][MAXLOG];

int clocks = 0;
int blockSize;

// cnt[color] 表示当前有效区间中该颜色出现次数
// visited[u] 表示结点 u 在当前区间中出现次数的奇偶性
int cnt[MAXN + 5], visited[MAXN + 5];

int currentAnswer = 0;
int answer[MAXQ + 5];

struct Query {
    int l, r, id;
    // extra 表示需要额外加入的 LCA 结点编号；若 LCA 就是 u，则 extra = -1
    int extra;
    bool operator<(const Query& other) const {
        int ba = l / blockSize;
        int bb = other.l / blockSize;
        if (ba != bb) return ba < bb;
        // 奇偶优化
        if (ba & 1) return r > other.r;
        return r < other.r;
    }
} queries[MAXQ + 5];

// DFS 预处理欧拉序、深度、倍增表
void dfs(int u, int p) {
    parent[u][0] = p;
    depth[u] = depth[p] + 1;
    // 第一次访问 u
    euler[++clocks] = u;
    first[u] = clocks;
    // 预处理倍增表
    for (int i = 1; i < MAXLOG; ++i) parent[u][i] = parent[parent[u][i - 1]][i - 1];
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    // 离开 u
    euler[++clocks] = u;
    last[u] = clocks;
}

// 倍增法求 LCA
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; i < MAXLOG; ++i)
        if ((diff >> i) & 1)
            u = parent[u][i];
    if (u == v) return u;
    for (int i = MAXLOG - 1; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

// 莫队的加入操作：切换结点访问状态
void add(int pos) {
    int node = euler[pos];
    visited[node] ^= 1;
    int c = colorCompressed[node];
    if (visited[node]) {
        // 结点第一次在当前区间中出现
        if (++cnt[c] == 1) ++currentAnswer;
    } else {
        // 结点第二次出现，说明它不在目标路径上，需要抵消
        if (--cnt[c] == 0) --currentAnswer;

    }
}

// 删除操作与加入操作对称
void remove(int pos) { add(pos); }

void solve(int m) {
    sort(queries, queries + m);
    int curL = 1;
    int curR = 0;
    for (int i = 0; i < m; ++i) {
        Query qu = queries[i];
        // 扩展区间
        while (curL > qu.l) {
            --curL;
            add(curL);
        }
        while (curR < qu.r) {
            ++curR;
            add(curR);
        }
        // 收缩区间
        while (curL < qu.l) {
            remove(curL);
            ++curL;
        }
        while (curR > qu.r) {
            remove(curR);
            --curR;
        }
        int ans = currentAnswer;
        // 若 LCA 不在区间中，需要单独判断是否加入答案
        if (qu.extra != -1 &&
            cnt[colorCompressed[qu.extra]] == 0) {
            ++ans;
        }
        answer[qu.id] = ans;
    }
}

// =============================================================
// 随机对拍测试
// =============================================================

// 重置全局状态，n 表示本次测试使用的结点数
void resetForTest(int n) {
    for (int i = 0; i <= n; ++i) g[i].clear();
    clocks = 0;
    currentAnswer = 0;
    fill(visited, visited + n + 1, 0);
    fill(cnt, cnt + n + 1, 0);
    // parent 会在 dfs 中重新赋值；depth[0] 需手动设
    depth[0] = -1;
}

// 随机对拍主函数
bool runTests() {
    mt19937 rng((unsigned int)time(NULL));
    const int TEST_CASES = 1000;

    for (int tc = 1; tc <= TEST_CASES; ++tc) {
        // 规模尽可能小，同时覆盖 n=1、链、多叉等多种情形
        int n = (int)(rng() % 40) + 1;   // 1..40
        int m = (int)(rng() % 40) + 1;   // 1..40
        // ---- 重置 ----
        resetForTest(n);
        // ---- 随机生成树，1 为根 ----
        for (int v = 2; v <= n; ++v) {
            int u = (int)(rng() % (v - 1)) + 1;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        // ---- 随机颜色（值域小，易出现重复颜色）----
        vector<int> colors(n);
        for (int i = 1; i <= n; ++i) {
            color[i] = (int)(rng() % 6) + 1;  // 1..6
            colors[i - 1] = color[i];
        }
        // 颜色离散化
        {
            vector<int> cs = colors;
            sort(cs.begin(), cs.end());
            cs.erase(unique(cs.begin(), cs.end()), cs.end());
            for (int i = 1; i <= n; ++i) {
                colorCompressed[i] =
                    lower_bound(cs.begin(), cs.end(), color[i]) - cs.begin();
            }
        }
        // ---- DFS ----
        depth[0] = -1;
        dfs(1, 0);
        blockSize = max(1, (int)sqrt(clocks));
        // ---- 生成查询并记录期望答案 ----
        vector<int> quU(m), quV(m), expected(m);
        for (int i = 0; i < m; ++i) {
            int u = (int)(rng() % n) + 1;
            int v = (int)(rng() % n) + 1;
            quU[i] = u;
            quV[i] = v;
            // 映射到欧拉序区间（与原算法逻辑一致）
            int uu = u, vv = v;
            if (first[uu] > first[vv]) swap(uu, vv);
            int p = lca(uu, vv);
            if (p == uu) {
                queries[i] = {first[uu], first[vv], i, -1};
            } else {
                queries[i] = {last[uu], first[vv], i, p};
            }
            // ---- 暴力：求 u 到 v 的路径上所有结点 ----
            vector<int> pathU, pathV;
            int a = u, b = v;
            while (depth[a] > depth[b]) {
                pathU.push_back(a);
                a = parent[a][0];
            }
            while (depth[b] > depth[a]) {
                pathV.push_back(b);
                b = parent[b][0];
            }
            while (a != b) {
                pathU.push_back(a);
                pathV.push_back(b);
                a = parent[a][0];
                b = parent[b][0];
            }
            pathU.push_back(a);  // LCA
            vector<int> path = pathU;
            for (int j = (int)pathV.size() - 1; j >= 0; --j)
                path.push_back(pathV[j]);

            // 统计路径上不同颜色数
            unordered_set<int> sc;
            for (int nd : path) sc.insert(color[nd]);
            expected[i] = (int)sc.size();
        }
        // ---- 树上莫队求解 ----
        solve(m);
        // ---- 比对结果 ----
        for (int i = 0; i < m; ++i) {
            if (answer[i] != expected[i]) {
                cerr << "Test failed! tc=" << tc << "\n";
                cerr << "n=" << n << ", m=" << m << "\n";
                cerr << "Edges: ";
                for (int v = 2; v <= n; ++v) {
                    for (int u : g[v]) {
                        if (u < v) cerr << "(" << u << "-" << v << ") ";
                    }
                }
                cerr << "\nColors: ";
                for (int x = 1; x <= n; ++x) cerr << color[x] << " ";
                cerr << "\nQuery[" << i << "]: u=" << quU[i]
                     << " v=" << quV[i]
                     << " expected=" << expected[i]
                     << " got=" << answer[i] << "\n";
                return false;
            }
        }
    }
    cout << "All " << TEST_CASES << " random tests passed.\n";
    return true;
}

#define DEBUG

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    #ifdef DEBUG
        return runTests() ? 0 : 1;
    #endif

    int n, m;
    cin >> n >> m;
    vector<int> colors(n);

    for (int i = 1; i <= n; ++i) {
        cin >> color[i];
        colors[i - 1] = color[i];
    }
    // 颜色离散化
    sort(colors.begin(), colors.end());
    colors.erase(unique(colors.begin(), colors.end()), colors.end());
    for (int i = 1; i <= n; ++i)
        colorCompressed[i] =
            lower_bound(colors.begin(), colors.end(), color[i]) - colors.begin();
    // 读入树边
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // 虚拟结点 0 的深度设为 -1，使根结点 1 的深度为 0
    depth[0] = -1;
    dfs(1, 0);
    // 欧拉序长度为 clocks = 2n
    blockSize = max(1, (int)sqrt(clocks));
    // 读入查询并映射为欧拉序区间
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (first[u] > first[v]) swap(u, v);
        int p = lca(u, v);
        if (p == u) queries[i] = {first[u], first[v], i, -1};
        else queries[i] = {last[u], first[v], i, p};
    }
    solve(m);
    for (int i = 0; i < m; ++i) cout << answer[i] << '\n';
    return 0;
}
