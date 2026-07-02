// Randomly Wired Neural Nets
// UVa ID: 582
// Verdict: Accepted
// Submission Date: 2026-06-27
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, v, w;
vector<vector<int>> rawAdj;                 // 原始邻接表，用于输出顺序
vector<vector<pair<int,int>>> adj;          // 带边号的邻接表
vector<pair<int,int>> edges;                // 所有边
vector<int> dfn, low;
vector<bool> isCut, inResult;
vector<vector<int>> bcc;                    // 每个块存储顶点列表
vector<int> belongBlock;                    // 非割点所属的块 id
vector<int> cutNodeId;                      // 割点对应的树节点 id，-1 表示非割点
vector<int> cutVertexOfNode;                // 树节点对应的割点顶点，-1 表示非割点
vector<vector<int>> blockTree;              // 块割树邻接表
vector<pair<int,int>> edgeStack;            // Tarjan 边栈
int timer, bccCnt, cutCnt;

// Tarjan 求点双连通分量，同时标记割点
void dfsTarjan(int u, int parentEdge) {
    dfn[u] = low[u] = ++timer;
    int child = 0;
    for (auto &pr : adj[u]) {
        int w = pr.first, eid = pr.second;
        if (eid == parentEdge) continue;
        if (!dfn[w]) {
            edgeStack.push_back({u, w});
            ++child;
            dfsTarjan(w, eid);
            low[u] = min(low[u], low[w]);
            if (low[w] >= dfn[u]) {
                if (parentEdge != -1) isCut[u] = true;   // 非根
                // 弹出边直到 (u, w)
                vector<int> comp;
                while (true) {
                    auto e = edgeStack.back(); edgeStack.pop_back();
                    comp.push_back(e.first);
                    comp.push_back(e.second);
                    if ((e.first == u && e.second == w) || (e.first == w && e.second == u))
                        break;
                }
                sort(comp.begin(), comp.end());
                comp.erase(unique(comp.begin(), comp.end()), comp.end());
                bcc.push_back(comp);
            }
        } else if (dfn[w] < dfn[u]) {   // 回边
            edgeStack.push_back({u, w});
            low[u] = min(low[u], dfn[w]);
        }
    }
    if (parentEdge == -1 && child >= 2) isCut[u] = true;   // 根节点特殊判断
}

// 检查 v 和 w 是否连通
bool isConnected() {
    vector<bool> vis(n, false);
    queue<int> q;
    vis[v] = true; q.push(v);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == w) return true;
        for (auto &pr : adj[u]) {
            int to = pr.first;
            if (!vis[to]) { vis[to] = true; q.push(to); }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入
    cin >> v >> w;
    cin >> n;
    rawAdj.resize(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        rawAdj[i].resize(k);
        for (int j = 0; j < k; ++j) cin >> rawAdj[i][j];
    }

    // 构建带边号的邻接表（去重，只保留 u < v 的边）
    adj.assign(n, {});
    for (int u = 0; u < n; ++u)
        for (int to : rawAdj[u])
            if (u < to) {
                int eid = (int)edges.size();
                edges.push_back({u, to});
                adj[u].push_back({to, eid});
                adj[to].push_back({u, eid});
            }

    // 若不连通，所有顶点都不在路径上
    if (!isConnected()) {
        for (int i = 0; i < n; ++i) cout << "X\n";
        return 0;
    }

    // Tarjan 求块和割点
    dfn.assign(n, 0); low.assign(n, 0);
    isCut.assign(n, false);
    belongBlock.assign(n, -1);
    timer = 0;
    for (int i = 0; i < n; ++i)
        if (!dfn[i]) dfsTarjan(i, -1);

    // 构建块割树
    bccCnt = (int)bcc.size();
    cutNodeId.assign(n, -1);
    cutCnt = 0;
    for (int i = 0; i < n; ++i)
        if (isCut[i]) cutNodeId[i] = bccCnt + (cutCnt++);

    int totalNodes = bccCnt + cutCnt;
    blockTree.assign(totalNodes, {});
    cutVertexOfNode.assign(totalNodes, -1);
    for (int i = 0; i < n; ++i)
        if (isCut[i]) cutVertexOfNode[cutNodeId[i]] = i;

    // 连接块与割点
    for (int bid = 0; bid < bccCnt; ++bid) {
        for (int x : bcc[bid]) {
            if (isCut[x]) {
                int cnode = cutNodeId[x];
                blockTree[bid].push_back(cnode);
                blockTree[cnode].push_back(bid);
            } else {
                // 非割点只属于一个块
                belongBlock[x] = bid;
            }
        }
    }

    // 确定起点和终点在块割树中的节点
    int startNode, endNode;
    if (isCut[v]) startNode = cutNodeId[v];
    else startNode = belongBlock[v];
    if (isCut[w]) endNode = cutNodeId[w];
    else endNode = belongBlock[w];

    // 在树中找路径（DFS）
    vector<int> parent(totalNodes, -1);
    function<bool(int,int)> dfsTree = [&](int u, int p) -> bool {
        parent[u] = p;
        if (u == endNode) return true;
        for (int nb : blockTree[u])
            if (nb != p && dfsTree(nb, u)) return true;
        return false;
    };
    dfsTree(startNode, -1);

    // 回溯得到路径节点
    vector<int> path;
    for (int cur = endNode; cur != -1; cur = parent[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());

    // 收集结果顶点
    inResult.assign(n, false);
    for (int node : path) {
        if (node < bccCnt) {   // 块节点
            for (int x : bcc[node]) inResult[x] = true;
        } else {              // 割点节点
            int x = cutVertexOfNode[node];
            if (x != -1) inResult[x] = true;
        }
    }

    // 输出
    for (int i = 0; i < n; ++i) {
        if (!inResult[i]) {
            cout << "X\n";
        } else {
            bool first = true;
            for (int nb : rawAdj[i]) {
                if (inResult[nb]) {
                    if (!first) cout << ' ';
                    first = false;
                    cout << nb;
                }
            }
            cout << '\n';
        }
    }

    return 0;
}
