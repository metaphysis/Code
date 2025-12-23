// The K-League
// UVa ID: 1306
// Verdict: Accepted
// Submission Date: 2025-12-15
// UVa Run Time: 0.120s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;       // 目标节点, 反向边在邻接表中的索引
    int flow, cap;     // 当前流量, 容量
    Edge(int t, int r, int f, int c) : to(t), rev(r), flow(f), cap(c) {}
};

const int INF = 1e9;   // 无穷大常量

// Dinic 最大流算法实现
struct Dinic {
    vector<vector<Edge>> graph;  // 邻接表存图
    vector<int> level, iter;     // 分层图中的层级, 当前弧优化
    int n;                       // 节点数
    
    Dinic(int nodes) {
        n = nodes;
        graph.resize(nodes);
        level.resize(nodes);
        iter.resize(nodes);
    }
    
    // 添加有向边 from->to, 容量为cap
    void addEdge(int from, int to, int cap) {
        Edge a(to, graph[to].size(), 0, cap);
        Edge b(from, graph[from].size(), 0, 0); // 反向边初始容量为0
        graph[from].push_back(a);
        graph[to].push_back(b);
    }
    
    // BFS构建分层图
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (Edge& e : graph[cur]) {
                if (level[e.to] == -1 && e.flow < e.cap) {
                    level[e.to] = level[cur] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1; // 如果汇点可达, 返回true
    }
    
    // DFS寻找增广路
    int dfs(int cur, int t, int f) {
        if (cur == t) return f;
        for (int& i = iter[cur]; i < (int)graph[cur].size(); ++i) {
            Edge& e = graph[cur][i];
            if (e.flow < e.cap && level[e.to] == level[cur] + 1) {
                int pushed = dfs(e.to, t, min(f, e.cap - e.flow));
                if (pushed > 0) {
                    e.flow += pushed;
                    graph[e.to][e.rev].flow -= pushed; // 更新反向边
                    return pushed;
                }
            }
        }
        return 0;
    }
    
    // 计算从s到t的最大流
    int maxFlow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            while (int pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

// 判断指定队伍targetTeam是否可能夺冠
bool canWin(int targetTeam, vector<int>& wins, vector<vector<int>>& remain, int n) {
    // 计算目标队伍的最大可能胜场数（假设剩余比赛全胜）
    int maxWin = wins[targetTeam];
    for (int i = 0; i < n; ++i) {
        maxWin += remain[targetTeam][i];
    }
    
    // 快速检查：如果有队伍当前胜场已超过maxWin, 直接返回false
    for (int i = 0; i < n; ++i) {
        if (wins[i] > maxWin) return false;
    }
    
    // 统计剩余比赛：只考虑i<j的情况, 避免重复
    int matchCount = 0;
    vector<pair<int, int>> matches; // 存储比赛双方编号
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (remain[i][j] > 0) {
                matchCount++;
                matches.push_back({i, j});
            }
        }
    }
    
    // 节点编号分配：
    // 0 = 源点source
    // 1 ~ matchCount = 比赛节点
    // matchCount+1 ~ matchCount+n = 球队节点
    // matchCount+n+1 = 汇点sink
    int totalNodes = 2 + matchCount + n;
    int source = 0;
    int sink = totalNodes - 1;
    int matchStart = 1;
    int teamStart = matchStart + matchCount;
    
    // 创建Dinic实例
    Dinic dinic(totalNodes);
    
    // 计算总剩余比赛场数
    int totalRemainGames = 0;
    
    // 添加边：源点 -> 比赛节点
    for (int i = 0; i < matchCount; ++i) {
        int u = matches[i].first;
        int v = matches[i].second;
        int games = remain[u][v];
        dinic.addEdge(source, matchStart + i, games);
        totalRemainGames += games;
        
        // 比赛节点 -> 两支参赛队伍节点（容量为INF，表示可以任意分配）
        dinic.addEdge(matchStart + i, teamStart + u, INF);
        dinic.addEdge(matchStart + i, teamStart + v, INF);
    }
    
    // 添加边：球队节点 -> 汇点
    for (int i = 0; i < n; ++i) {
        int cap = maxWin - wins[i]; // 该队伍最多还能赢几场
        if (cap < 0) return false;  // 不应该发生（前面已检查过）
        dinic.addEdge(teamStart + i, sink, cap);
    }
    
    // 计算最大流
    int flow = dinic.maxFlow(source, sink);
    
    // 如果最大流等于总剩余比赛数，说明所有比赛都能被分配
    return flow == totalRemainGames;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); // 加速输入输出
    
    int testCases;
    cin >> testCases;
    
    while (testCases--) {
        int n;
        cin >> n;
        
        vector<int> wins(n);
        vector<int> defeats(n); // 负场数，实际上在解题中用不到
        
        // 读取胜场和负场
        for (int i = 0; i < n; ++i) {
            cin >> wins[i] >> defeats[i];
        }
        
        // 读取剩余比赛矩阵
        vector<vector<int>> remain(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> remain[i][j];
            }
        }
        
        // 检查每支队伍是否可能夺冠
        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (canWin(i, wins, remain, n)) {
                result.push_back(i + 1); // 队伍编号从1开始
            }
        }
        
        // 输出结果（按编号递增顺序）
        for (size_t i = 0; i < result.size(); ++i) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << endl;
    }
    
    return 0;
}
