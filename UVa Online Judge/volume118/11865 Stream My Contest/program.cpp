// Stream My Contest
// UVa ID: 11865
// Verdict: Accepted
// Submission Date: 2025-11-15
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int u, v, b, c;
};

// 可靠的朱刘算法实现
class DirectedMST {
private:
    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    
public:
    DirectedMST(int n, const vector<Edge>& edges, const vector<vector<int>>& adj) 
        : n(n), edges(edges), adj(adj) {}

    // 连通性检查
    bool checkConnectivity(int root, int minBandwidth) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(root);
        visited[root] = true;
        int count = 1;
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int idx : adj[u]) {
                const Edge& e = edges[idx];
                if (e.b >= minBandwidth && !visited[e.v]) {
                    visited[e.v] = true;
                    q.push(e.v);
                    count++;
                }
            }
        }
        return count == n;
    }

    // 朱刘算法求解最小树形图
    int solve(int root, int minBandwidth) {
        // 首先检查连通性
        if (!checkConnectivity(root, minBandwidth)) {
            return -1;
        }
        
        int m = edges.size();
        
        // 构建有效边集
        vector<int> from, to, cost;
        for (int i = 0; i < m; i++) {
            if (edges[i].b >= minBandwidth) {
                from.push_back(edges[i].u);
                to.push_back(edges[i].v);
                cost.push_back(edges[i].c);
            }
        }
        
        if (from.empty()) return -1;
        
        return chuLiuEdmonds(root, n, from, to, cost);
    }

private:
    // 朱刘算法核心实现
    int chuLiuEdmonds(int root, int n, const vector<int>& from, 
                     const vector<int>& to, const vector<int>& cost) {
        int m = from.size();
        if (m == 0) return -1;
        
        vector<int> minIncoming(n, -1);
        vector<int> minCost(n, INT_MAX);
        
        // Step 1: 为每个节点找到最小入边
        for (int i = 0; i < m; i++) {
            int u = from[i], v = to[i], c = cost[i];
            if (u == v) continue; // 跳过自环
            
            if (c < minCost[v]) {
                minCost[v] = c;
                minIncoming[v] = i;
            }
        }
        
        minCost[root] = 0;
        minIncoming[root] = -1;
        
        // 检查是否所有节点都有入边（除了根节点）
        for (int i = 0; i < n; i++) {
            if (i != root && minIncoming[i] == -1) {
                return -1; // 有节点不可达
            }
        }
        
        // Step 2: 检测环
        vector<int> comp(n, -1);
        vector<int> vis(n, -1);
        int compCount = 0;
        
        for (int i = 0; i < n; i++) {
            if (comp[i] != -1) continue;
            
            int cur = i;
            while (cur != -1 && comp[cur] == -1) {
                if (vis[cur] == i) { // 找到环
                    int start = cur;
                    do {
                        comp[cur] = compCount;
                        cur = from[minIncoming[cur]];
                    } while (cur != start);
                    compCount++;
                    break;
                }
                
                vis[cur] = i;
                if (minIncoming[cur] == -1) {
                    comp[cur] = compCount++;
                    break;
                }
                cur = from[minIncoming[cur]];
            }
            
            if (cur == -1) continue;
            
            // 标记路径上的其他节点
            cur = i;
            while (cur != -1 && comp[cur] == -1) {
                comp[cur] = compCount++;
                cur = from[minIncoming[cur]];
            }
        }
        
        // 如果没有环，直接返回总成本
        if (compCount == n) {
            int total = 0;
            for (int i = 0; i < n; i++) {
                if (i != root) {
                    total += minCost[i];
                }
            }
            return total;
        }
        
        // Step 3: 缩点并构建新图
        vector<int> newFrom, newTo, newCost;
        
        // 添加跨组件边
        for (int i = 0; i < m; i++) {
            int u = from[i], v = to[i], c = cost[i];
            if (comp[u] == comp[v]) continue; // 组件内边跳过
            
            newFrom.push_back(comp[u]);
            newTo.push_back(comp[v]);
            // 关键：权值调整
            int adjustedCost = c;
            if (minIncoming[v] != -1) {
                adjustedCost -= minCost[v];
            }
            newCost.push_back(adjustedCost);
        }
        
        // 递归求解
        int newRoot = comp[root];
        int subCost = chuLiuEdmonds(newRoot, compCount, newFrom, newTo, newCost);
        if (subCost == -1) return -1;
        
        // 计算总成本
        int total = subCost;
        for (int i = 0; i < n; i++) {
            if (i != root && minIncoming[i] != -1) {
                total += minCost[i];
            }
        }
        return total;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int N, M, C;
        cin >> N >> M >> C;
        
        vector<Edge> edges(M);
        vector<vector<int>> adj(N);
        
        int minB = INT_MAX, maxB = 0;
        
        for (int i = 0; i < M; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].b >> edges[i].c;
            adj[edges[i].u].push_back(i);
            minB = min(minB, edges[i].b);
            maxB = max(maxB, edges[i].b);
        }
        
        // 二分答案
        int left = minB, right = maxB;
        int answer = -1;
        
        DirectedMST mst(N, edges, adj);
        
        // 检查最小带宽是否可行
        if (mst.solve(0, minB) == -1) {
            cout << "streaming not possible." << endl;
            continue;
        }
        
        // 二分查找最大可行带宽
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int cost = mst.solve(0, mid);
            if (cost != -1 && cost <= C) {
                answer = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        if (answer == -1) {
            cout << "streaming not possible." << endl;
        } else {
            cout << answer << " kbps" << endl;
        }
    }
    
    return 0;
}
