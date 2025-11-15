// RevolC FacLoN
// UVa ID: 10972
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
const int MAXM = 1000005;

struct Edge {
    int u, v;
    Edge(int u = 0, int v = 0) : u(u), v(v) {}
};

vector<int> graph[MAXN];
Edge edges[MAXM * 2];
int n, m, stamp;
int dfn[MAXN], low[MAXN], bccno[MAXN], bccCnt;
bool isBridge[MAXM * 2];

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++stamp;
    for (int i = 0; i < graph[u].size(); i++) {
        int edgeId = graph[u][i];
        int v = edges[edgeId].v;
        
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                isBridge[edgeId] = isBridge[edgeId ^ 1] = true;
            }
        } else if (dfn[v] < dfn[u] && v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void dfs(int u) {
    dfn[u] = 1;
    bccno[u] = bccCnt;
    for (int i = 0; i < graph[u].size(); i++) {
        int edgeId = graph[u][i];
        if (isBridge[edgeId]) continue;
        int v = edges[edgeId].v;
        if (!dfn[v]) {
            dfs(v);
        }
    }
}

void findEdgeBcc() {
    bccCnt = stamp = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(bccno, 0, sizeof(bccno));
    memset(isBridge, false, sizeof(isBridge));
    
    // 第一遍Tarjan找桥
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, -1);
        }
    }
    
    // 第二遍DFS找边双连通分量
    memset(dfn, 0, sizeof(dfn));
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            bccCnt++;
            dfs(i);
        }
    }
}

int main() {
    while (cin >> n >> m) {
        // 初始化
        for (int i = 1; i <= n; i++) {
            graph[i].clear();
        }
        
        // 读入图
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            edges[i * 2] = Edge(u, v);
            edges[i * 2 + 1] = Edge(v, u);
            graph[u].push_back(i * 2);
            graph[v].push_back(i * 2 + 1);
        }
        
        findEdgeBcc();
        
        if (bccCnt == 1) {
            cout << "0\n";
        } else {
            // 统计每个边双连通分量的度数
            vector<int> degree(bccCnt + 1, 0);
            for (int i = 0; i < m * 2; i += 2) {
                int u = edges[i].u, v = edges[i].v;
                if (bccno[u] != bccno[v]) {
                    degree[bccno[u]]++;
                    degree[bccno[v]]++;
                }
            }
            
            // 统计孤立分量和叶子分量
            int isolatedCount = 0;  // 度数为0的分量
            int leafCount = 0;      // 度数为1的分量
            
            for (int i = 1; i <= bccCnt; i++) {
                if (degree[i] == 0) {
                    isolatedCount++;
                } else if (degree[i] == 1) {
                    leafCount++;
                }
            }
            
            // 结果 = 孤立分量数 + (叶子分量数 + 1) / 2
            int result = isolatedCount + (leafCount + 1) / 2;
            cout << result << "\n";
        }
    }
    
    return 0;
}
