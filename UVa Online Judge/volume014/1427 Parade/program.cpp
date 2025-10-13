// Parade
// UVa ID: 1427
// Verdict: Accepted
// Submission Date: 2025-10-13
// UVa Run Time: 0.190s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, m, k;
const int MAX_N = 110, MAX_M = 10010;
int timeCost[MAX_N][MAX_M];      // 时间成本前缀和
int welcomeSum[MAX_N][MAX_M];    // 欢迎值前缀和
int dequeArray[MAX_M];           // 单调队列数组
int dp[MAX_M];                   // DP数组，存储当前行的最优解
int tempDp[MAX_M];               // 临时存储上一行的DP值

int main(int argc, char* argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> n >> m >> k && (n || m || k)) {
        // 初始化数组
        memset(welcomeSum, 0, sizeof(welcomeSum));
        memset(timeCost, 0, sizeof(timeCost));
        for (int i = 0; i <= m; i++) dp[i] = 0;  // 初始DP值为0
        int tempValue;
        // 读入欢迎值并计算前缀和
        // welcomeSum[i][j] 表示第i行从位置0到位置j的欢迎值总和
        for (int i = 1; i <= n + 1; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> tempValue;
                welcomeSum[i][j] = welcomeSum[i][j - 1] + tempValue;
            }
        }
        // 读入时间成本并计算前缀和
        // timeCost[i][j] 表示第i行从位置0到位置j的时间成本总和
        for (int i = 1; i <= n + 1; i++)
            for (int j = 1; j <= m; j++) {
                cin >> tempValue;
                timeCost[i][j] = timeCost[i][j - 1] + tempValue;
            }
        // 从北向南进行DP
        for (int row = n + 1; row >= 1; row--) {
            // 保存上一行的DP值到临时数组
            for (int col = 0; col <= m; col++) tempDp[col] = dp[col];
            int front = 0, rear = -1;  // 单调队列的队首和队尾指针
            // 处理向右移动的情况
            for (int col = 0; col <= m; col++) {
                // 计算当前列的值：tempDp[col] - welcomeSum[row][col]
                // 这个值表示从上一行的col位置到当前行col位置的收益
                tempValue = tempDp[col] - welcomeSum[row][col];
                // 维护单调递减队列：队尾出队直到当前值小于等于队尾值
                while (front <= rear && tempValue >= tempDp[dequeArray[rear]] - welcomeSum[row][dequeArray[rear]]) rear--;
                // 当前列入队
                dequeArray[++rear] = col;
                // 维护时间窗口：如果当前列与队首列的时间差超过k，队首出队
                while (front <= rear && timeCost[row][col] - timeCost[row][dequeArray[front]] > k) front++;
                // 更新DP值：从队首列到当前列的路径收益
                tempValue = tempDp[dequeArray[front]] - welcomeSum[row][dequeArray[front]] + welcomeSum[row][col];
                dp[col] = max(dp[col], tempValue);
            }
            // 重置队列，处理向左移动的情况
            front = 0, rear = -1;
            // 处理向左移动的情况（从右向左扫描）
            for (int col = m; col >= 0; col--) {
                // 计算当前列的值：tempDp[col] + welcomeSum[row][col]
                // 这个值表示从上一行的col位置到当前行col位置的收益（向左移动方向）
                tempValue = tempDp[col] + welcomeSum[row][col];
                // 维护单调递减队列
                while (front <= rear && tempValue >= tempDp[dequeArray[rear]] + welcomeSum[row][dequeArray[rear]]) rear--;
                // 当前列入队
                dequeArray[++rear] = col;
                // 维护时间窗口：如果队首列与当前列的时间差超过k，队首出队
                while (front <= rear && timeCost[row][dequeArray[front]] - timeCost[row][col] > k) front++;
                // 更新DP值：从队首列到当前列的路径收益
                tempValue = tempDp[dequeArray[front]] + welcomeSum[row][dequeArray[front]] - welcomeSum[row][col];
                dp[col] = max(dp[col], tempValue);
            }
        }
        // 寻找最大欢迎值
        cout << *max_element(dp, dp + m + 1) << '\n';
    }
    return 0;
}
