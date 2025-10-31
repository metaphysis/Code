// Traffic Real Time Query System
// UVa ID: 1464
// Verdict: Accepted
// Submission Date: 2025-10-30
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net
//
// https://blog.csdn.net/metaphysis/article/details/154170338

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20010;  // 扩大范围，包含圆方树节点
const int MAXM = 200010;

int n, m, totalNodes;
int edgeToBlock[MAXM];  // 边对应的点双分量ID

struct Graph {
    struct Edge {
        int to, next;
    } edges[MAXM * 2];
    int head[MAXN], edgeCount;
    
    void init() {
        memset(head, 0, sizeof(head));
        edgeCount = 1;  // 从1开始，方便异或操作
    }
    
    void addEdge(int u, int v) {
        edges[++edgeCount] = {v, head[u]};
        head[u] = edgeCount;
    }
    
    void addUndirected(int u, int v) {
        addEdge(u, v);
        addEdge(v, u);
    }
};

Graph originalGraph, blockCutTree;

// Tarjan相关
int dfn[MAXN], low[MAXN], dfsClock;
stack<int> nodeStack;
stack<int> edgeStack;
bool visited[MAXM * 2];

void tarjan(int u) {
    dfn[u] = low[u] = ++dfsClock;
    nodeStack.push(u);
    
    for (int i = originalGraph.head[u]; i; i = originalGraph.edges[i].next) {
        if (visited[i]) continue;
        visited[i] = visited[i ^ 1] = true;
        
        int edgeId = i >> 1;
        edgeStack.push(edgeId);
        
        int v = originalGraph.edges[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            
            if (low[v] >= dfn[u]) {
                // 找到点双分量，创建方点
                int blockId = ++totalNodes;
                blockCutTree.addUndirected(u, blockId);
                
                // 弹出节点直到v
                while (true) {
                    int x = nodeStack.top(); nodeStack.pop();
                    blockCutTree.addUndirected(x, blockId);
                    if (x == v) break;
                }
                
                // 弹出边直到当前边
                while (!edgeStack.empty()) {
                    int e = edgeStack.top(); edgeStack.pop();
                    edgeToBlock[e] = blockId;
                    if (e == edgeId) break;
                }
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// 树链剖分LCA
int depth[MAXN], parent[MAXN], size[MAXN], heavySon[MAXN], top[MAXN];
int roundNodeCount[MAXN];

void dfs1(int u, int fa) {
    parent[u] = fa;
    depth[u] = depth[fa] + 1;
    size[u] = 1;
    roundNodeCount[u] = roundNodeCount[fa] + (u <= n ? 1 : 0);
    heavySon[u] = 0;
    
    for (int i = blockCutTree.head[u]; i; i = blockCutTree.edges[i].next) {
        int v = blockCutTree.edges[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[heavySon[u]] < size[v]) {
            heavySon[u] = v;
        }
    }
}

void dfs2(int u, int chainTop) {
    top[u] = chainTop;
    if (!heavySon[u]) return;
    dfs2(heavySon[u], chainTop);
    
    for (int i = blockCutTree.head[u]; i; i = blockCutTree.edges[i].next) {
        int v = blockCutTree.edges[i].to;
        if (v != parent[u] && v != heavySon[u]) {
            dfs2(v, v);
        }
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        u = parent[top[u]];
    }
    return depth[u] < depth[v] ? u : v;
}

int query(int u, int v) {
    int x = lca(u, v);
    return roundNodeCount[u] + roundNodeCount[v] - 2 * roundNodeCount[x] + (x <= n ? 1 : 0);
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        
        // 初始化
        totalNodes = n;
        originalGraph.init();
        blockCutTree.init();
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(visited, 0, sizeof(visited));
        memset(edgeToBlock, 0, sizeof(edgeToBlock));
        dfsClock = 0;
        while (!nodeStack.empty()) nodeStack.pop();
        while (!edgeStack.empty()) edgeStack.pop();
        
        // 读入图
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            originalGraph.addUndirected(u, v);
        }
        
        // Tarjan算法求点双
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tarjan(i);
                // 处理栈中剩余节点
                if (!nodeStack.empty()) {
                    int blockId = ++totalNodes;
                    while (!nodeStack.empty()) {
                        int x = nodeStack.top(); nodeStack.pop();
                        blockCutTree.addUndirected(x, blockId);
                    }
                }
                // 处理栈中剩余边
                while (!edgeStack.empty()) {
                    int e = edgeStack.top(); edgeStack.pop();
                    if (edgeToBlock[e] == 0) {
                        edgeToBlock[e] = totalNodes;
                    }
                }
            }
        }
        
        // 构建树链剖分
        memset(depth, 0, sizeof(depth));
        memset(parent, 0, sizeof(parent));
        memset(size, 0, sizeof(size));
        memset(heavySon, 0, sizeof(heavySon));
        memset(top, 0, sizeof(top));
        memset(roundNodeCount, 0, sizeof(roundNodeCount));
        
        for (int i = 1; i <= totalNodes; i++) {
            if (depth[i] == 0) {
                dfs1(i, 0);
                dfs2(i, i);
            }
        }
        
        int q;
        cin >> q;
        while (q--) {
            int s, t;
            cin >> s >> t;
            cout << query(edgeToBlock[s], edgeToBlock[t]) << endl;
        }
    }
    
    return 0;
}
