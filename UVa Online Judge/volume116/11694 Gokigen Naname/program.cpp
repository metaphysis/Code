// Gokigen Naname
// UVa ID: 11694
// Verdict: Accepted
// Submission Date: 2025-12-31
// UVa Run Time: 0.260s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n;                  // 网格边长
char board[10][10];     // 输入的数字/点
char ans[10][10];       // 输出结果（每个方格的对角线）
int parent[100];        // 并查集数组
int need[10][10];       // 数字需求，-1表示无需求
int cells;              // 总方格数

// 获取交叉点 (r, c) 对应的并查集节点编号
int getNodeId(int r, int c) {
    return r * (n + 1) + c;
}

// 并查集查找（带路径压缩）
int findSet(int x) {
    return parent[x] == x ? x : parent[x] = findSet(parent[x]);
}

// 计算交叉点 (r, c) 当前连接的对角线数
int getCurrentCount(int r, int c) {
    int cnt = 0;
    // 检查周围四个方格
    if (r > 0 && c > 0 && ans[r-1][c-1] == '\\') cnt++;      // 左上方格
    if (r > 0 && c < n && ans[r-1][c] == '/') cnt++;        // 右上方格
    if (r < n && c > 0 && ans[r][c-1] == '/') cnt++;        // 左下方格
    if (r < n && c < n && ans[r][c] == '\\') cnt++;         // 右下方格
    return cnt;
}

// 检查是否满足所有数字约束（不超限）
bool checkAllConstraints() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (need[i][j] != -1) {
                int cnt = getCurrentCount(i, j);
                if (cnt > need[i][j]) return false;  // 超过限制
            }
        }
    }
    return true;
}

// 前瞻性检查：检查当前状态是否可能最终满足所有数字约束
bool checkProspect(int r, int c) {
    // 受当前放置影响的四个交叉点
    int affected[4][2] = {{r, c}, {r, c+1}, {r+1, c}, {r+1, c+1}};
    
    for (int k = 0; k < 4; ++k) {
        int i = affected[k][0], j = affected[k][1];
        // 检查边界和是否为数字点
        if (i >= 0 && i <= n && j >= 0 && j <= n && need[i][j] != -1) {
            int current = getCurrentCount(i, j);
            // 计算该点周围还能放置对角线的方格数
            int possible = 0;
            if (i > 0 && j > 0 && ans[i-1][j-1] == 0) possible++;
            if (i > 0 && j < n && ans[i-1][j] == 0) possible++;
            if (i < n && j > 0 && ans[i][j-1] == 0) possible++;
            if (i < n && j < n && ans[i][j] == 0) possible++;
            
            // 如果当前已超过需求，或即使填满所有可能也达不到需求，则剪枝
            if (current > need[i][j] || current + possible < need[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// 深度优先搜索
bool dfs(int pos) {
    // 所有方格已填充，检查最终约束
    if (pos == cells) {
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                if (need[i][j] != -1 && getCurrentCount(i, j) != need[i][j])
                    return false;
        return true;
    }
    
    int r = pos / n;  // 当前方格的行
    int c = pos % n;  // 当前方格的列
    
    // 保存当前并查集状态，用于回溯恢复
    int parentCopy[100];
    memcpy(parentCopy, parent, sizeof(parentCopy));
    
    // 尝试放置 '/'
    int node1 = getNodeId(r, c + 1);  // 上方交叉点
    int node2 = getNodeId(r + 1, c);  // 下方交叉点
    if (findSet(node1) != findSet(node2)) {  // 检查是否形成环
        ans[r][c] = '/';
        parent[findSet(node1)] = findSet(node2);  // 合并集合
        
        // 检查约束并递归搜索
        if (checkAllConstraints() && checkProspect(r, c) && dfs(pos + 1)) {
            return true;
        }
        
        // 恢复状态
        ans[r][c] = 0;
        memcpy(parent, parentCopy, sizeof(parent));
    }
    
    // 尝试放置 '\'
    node1 = getNodeId(r, c);          // 左上交叉点
    node2 = getNodeId(r + 1, c + 1);  // 右下交叉点
    if (findSet(node1) != findSet(node2)) {
        ans[r][c] = '\\';
        parent[findSet(node1)] = findSet(node2);
        
        if (checkAllConstraints() && checkProspect(r, c) && dfs(pos + 1)) {
            return true;
        }
        
        // 恢复状态
        ans[r][c] = 0;
        memcpy(parent, parentCopy, sizeof(parent));
    }
    
    return false;  // 无解
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T; cin >> T;
    while (T--) {
        cin >> n;
        string line;
        getline(cin, line);  // 读取换行符
        
        // 读取交叉点数据
        for (int i = 0; i <= n; ++i) {
            getline(cin, line);
            for (int j = 0; j <= n; ++j) {
                board[i][j] = line[j];
                if (board[i][j] == '.') need[i][j] = -1;  // 无数字
                else need[i][j] = board[i][j] - '0';      // 数字需求
            }
        }
        
        // 初始化
        cells = n * n;  // 总方格数
        int totalNodes = (n + 1) * (n + 1);
        for (int i = 0; i < totalNodes; ++i) parent[i] = i;  // 并查集初始化
        memset(ans, 0, sizeof(ans));  // 清空答案
        
        // 执行深度优先搜索
        dfs(0);
        
        // 输出结果
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << ans[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}
