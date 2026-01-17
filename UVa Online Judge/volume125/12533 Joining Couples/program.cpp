// Joining Couples
// UVa ID: 12533
// Verdict: Accepted
// Submission Date: 2026-01-16
// UVa Run Time: 0.110s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOGN = 17; // 2^17 > 1e5

int n, q;
int to[MAXN];
int compId[MAXN]; // 所属基环树编号
int ringId[MAXN]; // 所属环编号（如果在环上）
int depth[MAXN];  // 在树上的深度（到环的距离）
int parent[MAXN][LOGN];
int ringPos[MAXN]; // 在环上的位置（0..环长-1）
int ringSize[MAXN]; // 环的大小
bool onRing[MAXN];
vector<int> revGraph[MAXN]; // 反向边，用于拓扑找枝

// 清空全局数据结构
void clearData() {
    for (int i = 1; i <= n; i++) {
        compId[i] = ringId[i] = depth[i] = ringPos[i] = ringSize[i] = 0;
        onRing[i] = false;
        revGraph[i].clear();
        for (int j = 0; j < LOGN; j++) parent[i][j] = 0;
    }
}

void dfs(int u, int cid, int rid, int d, int pos) {
    compId[u] = cid;
    ringId[u] = rid;
    depth[u] = d;
    ringPos[u] = pos;
    for (int v : revGraph[u]) {
        if (onRing[v] || compId[v]) continue;
        parent[v][0] = u;
        dfs(v, cid, rid, d + 1, pos);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; i < LOGN; i++)
        if (diff & (1 << i)) u = parent[u][i];
    if (u == v) return u;
    for (int i = LOGN - 1; i >= 0; i--)
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    return parent[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 循环读取直到文件结束
    while (cin >> n) {
        clearData(); // 清空上一组数据
        
        for (int i = 1; i <= n; i++) cin >> to[i];
        
        // 初始化入度数组
        vector<int> inDegree(n + 1, 0);
        for (int i = 1; i <= n; i++) inDegree[to[i]]++;
        
        // 构建反向图
        for (int i = 1; i <= n; i++) revGraph[to[i]].push_back(i);
        
        // 拓扑排序，标记不在环上的节点
        queue<int> qq;
        for (int i = 1; i <= n; i++)
            if (inDegree[i] == 0) qq.push(i);
        while (!qq.empty()) {
            int u = qq.front(); qq.pop();
            int v = to[u];
            inDegree[v]--;
            if (inDegree[v] == 0) qq.push(v);
        }
        
        // 标记环
        int compCnt = 0, ringCnt = 0;
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] > 0 && compId[i] == 0) {
                compCnt++;
                vector<int> ring;
                int cur = i;
                while (inDegree[cur] > 0 && compId[cur] == 0) {
                    compId[cur] = compCnt;
                    ring.push_back(cur);
                    onRing[cur] = true;
                    cur = to[cur];
                }
                ringCnt++;
                for (size_t j = 0; j < ring.size(); j++) {
                    int u = ring[j];
                    ringId[u] = ringCnt;
                    depth[u] = 0;
                    ringPos[u] = j;
                    parent[u][0] = 0;
                }
                ringSize[ringCnt] = ring.size();
            }
        }
        
        // 对环上每个节点，DFS 标记枝上的节点
        for (int i = 1; i <= n; i++) {
            if (onRing[i]) {
                for (int v : revGraph[i]) {
                    if (!onRing[v]) {
                        parent[v][0] = i;
                        dfs(v, compId[i], ringId[i], 1, ringPos[i]);
                    }
                }
            }
        }
        
        // 预处理 LCA 的倍增表
        for (int j = 1; j < LOGN; j++)
            for (int i = 1; i <= n; i++)
                if (parent[i][j - 1] != 0)
                    parent[i][j] = parent[parent[i][j - 1]][j - 1];
        
        // 处理查询
        cin >> q;
        while (q--) {
            int a, b;
            cin >> a >> b;
            if (compId[a] != compId[b]) {
                cout << "-1\n";
                continue;
            }
            if (ringId[a] != ringId[b]) {
                // 不同环，但在同一基环树？不可能，因为基环树只有一个环
                // 所以这里意味着在不同基环树，上面已经判断
                cout << "-1\n";
                continue;
            }
            if (onRing[a] && onRing[b]) {
                // 都在环上
                int p1 = ringPos[a], p2 = ringPos[b];
                int sz = ringSize[ringId[a]];
                int d = abs(p1 - p2);
                d = min(d, sz - d);
                cout << d << "\n";
            } else if (!onRing[a] && !onRing[b]) {
                // 都在枝上
                int l = lca(a, b);
                if (l != 0) {
                    // 在同一个枝上
                    cout << depth[a] + depth[b] - 2 * depth[l] << "\n";
                } else {
                    // 在不同枝上，LCA 是环上某个节点
                    int na = a, nb = b;
                    while (!onRing[na]) na = parent[na][0];
                    while (!onRing[nb]) nb = parent[nb][0];
                    int p1 = ringPos[na], p2 = ringPos[nb];
                    int sz = ringSize[ringId[na]];
                    int d = abs(p1 - p2);
                    d = min(d, sz - d);
                    cout << depth[a] + depth[b] + d << "\n";
                }
            } else {
                // 一个在环上一个在枝上
                if (!onRing[a]) swap(a, b); // 确保 a 在环上，b 在枝上
                // a 在环上，b 在枝上
                int nb = b;
                while (!onRing[nb]) nb = parent[nb][0];
                int p1 = ringPos[a], p2 = ringPos[nb];
                int sz = ringSize[ringId[a]];
                int d = abs(p1 - p2);
                d = min(d, sz - d);
                cout << depth[b] + d << "\n";
            }
        }
    }
    return 0;
}
