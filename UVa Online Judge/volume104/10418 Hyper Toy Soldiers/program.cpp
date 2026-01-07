// Hyper Toy Soldiers
// UVa ID: 10418
// Verdict: Accepted
// Submission Date: 2026-01-04
// UVa Run Time: 0.140s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 士兵类型常量
#define RED 0    // 红色士兵
#define BLUE 1   // 绿色士兵（代码中使用 BLUE 表示绿色）

const int INF = 0x3f3f3f3f;        // 无穷大
const int MAXN = 105;              // 最大棋盘大小
const int MAXV = 305;              // 最大节点数
const int MAXE = 40010;            // 最大边数
const int dx[4] = {1, -1, 0, 0};   // 四个移动方向
const int dy[4] = {0, 0, 1, -1};

// 输入数据
int m, n, k, t;                    // 棋盘大小，红/绿士兵数，目标格子数
int height[MAXN][MAXN];            // 棋盘高度
int goalX[MAXN], goalY[MAXN];      // 目标格子坐标
int goalR[MAXN];                   // 目标格子需求数量
int startX[MAXN], startY[MAXN];    // 士兵起始坐标

// 链式前向星最大流数据结构
struct Arc { 
    int to;         // 目标节点
    int capacity;   // 边容量
    int next;       // 下一条边索引
} arcs[MAXE * 2];   // 正反两条边

int head[MAXV];     // 每个节点的第一条边
int idx;            // 当前边索引
int source, sink;   // 源点和汇点
int level[MAXV];    // 分层图层级
int current[MAXV];  // 当前弧优化

// 添加边
void addEdge(int from, int to, int capacity) {
    arcs[idx] = {to, capacity, head[from]};
    head[from] = idx++;
    arcs[idx] = {from, 0, head[to]};
    head[to] = idx++;
}

// BFS 构建分层图
bool bfs() {
    memset(level, -1, sizeof level);
    queue<int> q;
    level[source] = 0;
    q.push(source);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = arcs[i].next) {
            int v = arcs[i].to;
            if (arcs[i].capacity > 0 && level[v] == -1) {
                level[v] = level[u] + 1;
                q.push(v);
                if (v == sink) return true;
            }
        }
    }
    return level[sink] != -1;
}

// DFS 寻找增广路
int dfs(int u, int flow) {
    if (u == sink) return flow;
    int volume = 0;
    for (int& i = current[u]; ~i; i = arcs[i].next) {
        int v = arcs[i].to, r = arcs[i].capacity;
        if (level[v] == level[u] + 1 && r > 0) {
            int volume = dfs(v, min(r, flow));
            if (volume > 0) {
                arcs[i].capacity -= volume;
                arcs[i ^ 1].capacity += volume;
                return volume;
            }
        }
    }
    return 0;
}

// Dinic 最大流算法
int maxFlow() {
    int flow = 0;
    while (bfs()) {
        for (int i = 0; i < MAXV; i++) current[i] = head[i];
        while (int delta = dfs(source, INF))
            flow += delta;
    }
    return flow;
}

// 扩展 BFS：计算从起点到所有位置的最小魔法次数
int dist[MAXN][MAXN];  // 到达每个位置的最小魔法次数
void initialize(int sx, int sy, int type) {
    // 初始化距离为无穷大
    memset(dist, INF, sizeof dist);
    
    // 队列元素：(x, y, 当前类型, 已使用魔法次数)
    queue<tuple<int, int, int, int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy, type, 0});
    
    while (!q.empty()) {
        auto [x, y, type, casted] = q.front(); q.pop();
        
        // 尝试四个方向的移动
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 1 || nx > m || ny < 1 || ny > n) continue;
            
            // 如果已经有更优解，跳过
            if (dist[nx][ny] <= casted) continue;
            
            // 检查当前类型是否可以移动到这个位置
            bool continuing = false;
            if (type == RED) 
                continuing = height[nx][ny] >= height[x][y];  // 红色不能下降
            else 
                continuing = height[nx][ny] <= height[x][y];  // 绿色不能上升
            
            if (continuing) {
                // 可以不使用魔法直接移动
                dist[nx][ny] = casted;
                q.push({nx, ny, type, casted});
            } else {
                // 需要使用魔法改变类型后才能移动
                if (dist[nx][ny] > casted + 1) {
                    dist[nx][ny] = casted + 1;
                    q.push({nx, ny, 1 - type, casted + 1});
                }
            }
        }
    }
}

// magicNeeded[i][j]: 士兵 i 到达目标 j 所需的最小魔法次数
int magicNeeded[MAXN][MAXN];

// 检查是否可以在 magicUsed 次魔法内完成分配
bool check(int magicUsed) {
    int soldierCount = 2 * k;  // 红绿士兵总数
    int goalCount = t;         // 目标格子数
    
    // 初始化图
    idx = 0;
    memset(head, -1, sizeof head);
    source = 0;
    sink = soldierCount + goalCount + 1;
    
    // 源点连接到所有士兵
    for (int i = 1; i <= soldierCount; i++) 
        addEdge(source, i, 1);
    
    // 目标格子连接到汇点，容量为目标需求数
    for (int i = 0; i < goalCount; i++) 
        addEdge(soldierCount + i + 1, sink, goalR[i]);
    
    // 添加士兵到目标格子的边（如果所需魔法次数不超过限制）
    for (int i = 0; i < 2 * k; i++)
        for (int j = 0; j < goalCount; j++)
            if (magicNeeded[i][j] <= magicUsed)
                addEdge(i + 1, soldierCount + j + 1, 1);
    
    // 计算最大流
    int flow = maxFlow();
    
    // 检查条件：已匹配的士兵数 + 可用魔法次数 >= 总士兵数
    return flow + magicUsed >= 2 * k;
}

int main() {
    // 加速输入输出
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int T;
    cin >> T;
    
    while (T--) {
        // 读入数据
        cin >> m >> n >> k >> t;
        
        // 读入士兵位置：前 k 个红，中间 k 个绿，最后 1 个金
        for (int i = 0; i < 2 * k + 1; i++) 
            cin >> startX[i] >> startY[i];
        
        // 读入目标格子
        for (int i = 0; i < t; i++) 
            cin >> goalX[i] >> goalY[i] >> goalR[i];
        
        // 读入棋盘高度
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                cin >> height[i][j];
        
        // 预处理：计算每个红绿士兵到每个目标的最小魔法次数
        for (int i = 0; i < 2 * k; i++) {
            // 前 k 个是红色士兵，后 k 个是绿色士兵
            initialize(startX[i], startY[i], (i < k) ? RED : BLUE);
            
            // 记录到每个目标的魔法次数
            for (int j = 0; j < t; j++)
                magicNeeded[i][j] = dist[goalX[j]][goalY[j]];
        }
        
        // 二分答案：寻找最小魔法次数
        int left = 0, right = 2 * k + 1, answer = -1;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (check(middle)) {
                answer = middle;
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }
        
        cout << answer << '\n';
    }
    
    return 0;
}
