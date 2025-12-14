// Book Club
// UVa ID: 12880
// Verdict: Accepted
// Submission Date: 2025-12-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// Hopcroft-Karp 算法求二分图最大匹配
class HopcroftKarp {
private:
    int nLeft, nRight;          // 左部节点数、右部节点数
    vector<vector<int>> adj;    // 邻接表，adj[u] 存储左部节点u连接的右部节点
    vector<int> dist;           // BFS距离数组
    vector<int> matchLeft;      // matchLeft[u] = v 表示左部节点u匹配到右部节点v
    vector<int> matchRight;     // matchRight[v] = u 表示右部节点v匹配到左部节点u
    
    // BFS：构建层次图，返回是否存在增广路
    bool bfs() {
        queue<int> q;
        dist[0] = INF;  // 虚拟节点0，用于标记未匹配的左部节点
        
        // 初始化：将所有未匹配的左部节点加入队列
        for (int u = 1; u <= nLeft; u++) {
            if (matchLeft[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            
            // 只处理距离小于INF的节点（即可能找到增广路的节点）
            if (dist[u] < dist[0]) {
                for (int v : adj[u]) {
                    // 如果右部节点v的匹配节点还未被访问
                    if (dist[matchRight[v]] == INF) {
                        dist[matchRight[v]] = dist[u] + 1;
                        q.push(matchRight[v]);
                    }
                }
            }
        }
        
        // 如果虚拟节点0的距离被更新，说明存在增广路
        return dist[0] != INF;
    }
    
    // DFS：在层次图中寻找增广路
    bool dfs(int u) {
        if (u != 0) {
            for (int v : adj[u]) {
                // 按照层次图前进
                if (dist[matchRight[v]] == dist[u] + 1 && dfs(matchRight[v])) {
                    // 找到增广路，更新匹配
                    matchLeft[u] = v;
                    matchRight[v] = u;
                    return true;
                }
            }
            // 当前节点无法找到增广路，标记为无穷大（不再访问）
            dist[u] = INF;
            return false;
        }
        // 到达虚拟节点0，成功找到增广路
        return true;
    }
    
public:
    // 构造函数，初始化左右部节点数
    HopcroftKarp(int leftSize, int rightSize) : 
        nLeft(leftSize), nRight(rightSize), 
        adj(leftSize + 1), 
        dist(leftSize + 1), 
        matchLeft(leftSize + 1, 0), 
        matchRight(rightSize + 1, 0) {}
    
    // 添加边：左部节点u -> 右部节点v
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    // 计算最大匹配数
    int maxMatching() {
        int matching = 0;
        
        // 多次BFS+DFS，直到找不到增广路
        while (bfs()) {
            for (int u = 1; u <= nLeft; u++) {
                if (matchLeft[u] == 0 && dfs(u)) {
                    matching++;
                }
            }
        }
        
        return matching;
    }
    
    // 判断是否存在完美匹配
    bool isPerfectMatch() {
        return maxMatching() == nLeft;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    while (cin >> n >> m) {
        // 创建Hopcroft-Karp对象，注意使用1-based编号
        HopcroftKarp hk(n, n);
        
        // 读入边并建图
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            // 输入是0-based，转换为1-based
            hk.addEdge(a + 1, b + 1);
        }
        
        // 检查是否存在完美匹配
        if (hk.isPerfectMatch()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
