#include <bits/stdc++.h>
using namespace std;

const int inf = 1000000000;

struct Edge {
    int u, v, w;
};

struct Block {
    vector<int> nodes, edgeIds;
};

int n, m, dfsTime;
vector<Edge> edges;
vector<Block> blocks;
vector<vector<int>> adj, belong;
vector<int> dfn, low, edgeStack;
vector<array<int, 3>> dp;

void tarjan(int u, int parentEdge) {
    dfn[u] = low[u] = ++dfsTime;
    for (int edgeId : adj[u]) {
        if (edgeId == parentEdge) continue;
        int v = edges[edgeId].u ^ edges[edgeId].v ^ u;
        if (!dfn[v]) {
            edgeStack.push_back(edgeId);
            tarjan(v, edgeId);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                Block block;
                int curId;
                do {
                    curId = edgeStack.back();
                    edgeStack.pop_back();
                    block.edgeIds.push_back(curId);
                    int a = edges[curId].u, b = edges[curId].v;
                    if (find(block.nodes.begin(), block.nodes.end(), a) == block.nodes.end()) block.nodes.push_back(a);
                    if (find(block.nodes.begin(), block.nodes.end(), b) == block.nodes.end()) block.nodes.push_back(b);
                } while (curId != edgeId);
                blocks.push_back(block);
            }
        } else if (dfn[v] < dfn[u]) {
            edgeStack.push_back(edgeId);
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void solveVertex(int u, int parentBlock) {
    dp[u] = {{0, inf, inf}};
    for (int blockId : belong[u]) {
        if (blockId == parentBlock) continue;
        const Block &block = blocks[blockId];
        vector<int> nodes(1, u);
        for (int v : block.nodes) if (v != u) nodes.push_back(v);
        int nodeCount = (int)nodes.size(), edgeCount = (int)block.edgeIds.size();
        int stateCount = 1, ends[3][2];
        for (int i = 1; i < nodeCount; ++i) {
            solveVertex(nodes[i], blockId);
            stateCount *= 3;
        }
        for (int i = 0; i < edgeCount; ++i) {
            const Edge &edge = edges[block.edgeIds[i]];
            ends[i][0] = (int)(find(nodes.begin(), nodes.end(), edge.u) - nodes.begin());
            ends[i][1] = (int)(find(nodes.begin(), nodes.end(), edge.v) - nodes.begin());
        }
        array<int, 3> blockDp = {{inf, inf, inf}};
        for (int mask = 0; mask < (1 << edgeCount); ++mask) {
            int localActive = 0, edgeCost = 0;
            for (int i = 0; i < edgeCount; ++i) {
                if (mask & (1 << i)) {
                    localActive |= (1 << ends[i][0]) | (1 << ends[i][1]);
                    edgeCost += edges[block.edgeIds[i]].w;
                }
            }
            for (int code = 0; code < stateCount; ++code) {
                int curCode = code, active = localActive, cost = edgeCost;
                bool valid = true, need = false;
                for (int i = 1; i < nodeCount; ++i) {
                    int state = curCode % 3;
                    curCode /= 3;
                    if (dp[nodes[i]][state] == inf || (state == 2 && !(localActive & (1 << i)))) {
                        valid = false;
                        break;
                    }
                    cost += dp[nodes[i]][state];
                    if (state == 1) active |= 1 << i;
                }
                if (!valid) continue;
                for (int i = 0; i < edgeCount; ++i) {
                    int a = ends[i][0], b = ends[i][1];
                    if ((active & (1 << a)) || (active & (1 << b))) continue;
                    if (a == 0 || b == 0) need = true;
                    else {
                        valid = false;
                        break;
                    }
                }
                if (!valid) continue;
                int state = (active & 1) ? 1 : (need ? 2 : 0);
                blockDp[state] = min(blockDp[state], cost);
            }
        }
        array<int, 3> nextDp = {{inf, inf, inf}};
        for (int a = 0; a < 3; ++a) {
            if (dp[u][a] == inf) continue;
            for (int b = 0; b < 3; ++b) {
                if (blockDp[b] == inf) continue;
                int state = (a == 1 || b == 1) ? 1 : ((a == 2 || b == 2) ? 2 : 0);
                nextDp[state] = min(nextDp[state], dp[u][a] + blockDp[b]);
            }
        }
        dp[u] = nextDp;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        cin >> n >> m;
        edges.resize(m);
        adj.assign(n + 1, vector<int>());
        belong.assign(n + 1, vector<int>());
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        dp.resize(n + 1);
        blocks.clear();
        edgeStack.clear();
        dfsTime = 0;
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
            adj[edges[i].u].push_back(i);
            adj[edges[i].v].push_back(i);
        }
        tarjan(1, -1);
        for (int i = 0; i < (int)blocks.size(); ++i) for (int u : blocks[i].nodes) belong[u].push_back(i);
        solveVertex(1, -1);
        cout << "Case " << caseId << ": " << min(dp[1][0], dp[1][1]) << '\n';
    }
    return 0;
}
