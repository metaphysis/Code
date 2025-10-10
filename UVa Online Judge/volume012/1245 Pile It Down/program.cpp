// Pile It Down
// UVa ID: 1245
// Verdict: Accepted
// Submission Date: 2025-10-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int N = 1010;  // 最大堆大小

// dp[x][y]: 1表示先手必胜，0表示先手必败
// dist[x][y]: 从状态(x,y)到游戏结束的步数
// visited[i]: 标记数字i是否已被使用，用于生成Wythoff必败态
int dp[N][N], dist[N][N], visited[2 * N];

/**
 * BFS函数：从必败态(x,y)出发，更新所有可达状态的步数
 * 对于必败态，更新所有能一步到达该状态的状态（逆向思维）
 */
void bfs(int x, int y) {
    if (x >= N || y >= N) return;  // 边界检查
    
    // 标记(x,y)为必败态，步数为0（游戏结束状态）
    dp[x][y] = 0;
    dist[x][y] = 0;
    
    // 对于必败态(x,y)，更新所有能通过一步操作到达(x,y)的状态
    // 这里使用逆向思维：从(x,y)向前推导
    
    // 情况1：从两堆取相同数量硬币的逆操作
    // 如果从(nx,ny)取k个硬币能到达(x,y)，则dist[nx][ny] = dist[x][y] + 1
    for (int i = 1; i <= min(x, y); i++) 
        dist[x][y] = max(dist[x][y], dist[x - i][y - i] + 1);
    
    // 情况2：从第一堆取硬币的逆操作
    for (int i = 0; i < x; i++) 
        dist[x][y] = max(dist[x][y], dist[i][y] + 1);
    
    // 情况3：从第二堆取硬币的逆操作  
    for (int i = 0; i < y; i++) 
        dist[x][y] = max(dist[x][y], dist[x][i] + 1);
    
    // 更新正向可达状态的最小步数（赢家策略）
    // 情况1：往两堆加相同数量（相当于从新状态取相同数量到达当前状态）
    for (int i = 1; x + i < N && y + i < N; i++) 
        dist[x + i][y + i] = min(dist[x + i][y + i], dist[x][y] + 1);
    
    // 情况2：往第一堆加数量
    for (int i = x + 1; i < N; i++) 
        dist[i][y] = min(dist[i][y], dist[x][y] + 1);
    
    // 情况3：往第二堆加数量
    for (int i = y + 1; i < N; i++) 
        dist[x][i] = min(dist[x][i], dist[x][y] + 1);
}

/**
 * 初始化函数：预处理所有游戏状态的胜负和步数
 * 基于Wythoff游戏的必败态生成和传播
 */
void initialize() {
    // 初始化：所有状态默认为必胜态，步数为无穷大
    memset(dp, 1, sizeof dp);
    memset(dist, 0x3f, sizeof dist);
    memset(visited, 0, sizeof visited);
    
    int x = 0;  // 从0开始寻找可用的数字
    
    // 生成Wythoff必败态序列
    for (int i = 0; i < N; i++) {
        // 找到最小的未被使用的数字
        while (visited[x]) x++;
        
        // 根据Wythoff游戏规则生成必败态对(x, y)
        int y = x + i;  // y = x + i 满足黄金比例关系
        
        // 标记这两个数字已被使用
        visited[x] = 1, visited[y] = 1;
        
        // 对必败态(x,y)和对称状态(y,x)进行BFS传播
        bfs(x, y); 
        bfs(y, x);
    }
}

int main(int argc, char* argv[]) {
    // 输入输出优化
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    // 预处理所有游戏状态
    initialize();
    
    // 处理测试用例
    int cases = 0; 
    cin >> cases;
    while (cases--) {
        int x, y, p; 
        cin >> x >> y >> p;
        
        // 计算总步数：基础步数 + 2 * Pass次数
        // 每次Pass增加2步（Pass操作 + 对方操作）
        int r = dist[x][y] + 2 * p;
        
        // 输出结果：根据初始状态判断胜负，考虑Pass的影响
        // 如果初始是必胜态，Sita赢；如果是必败态，根据Pass次数的奇偶性决定
        cout << (dp[x][y] ? "Sita " : "Gita ") << r << '\n';
    }
    return 0;
}
