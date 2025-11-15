// Selling Land
// UVa ID: 12265
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

// 矩形结构体：start 表示起始列，height 表示矩形高度
struct rect { int start, height; };

int n, m;
char grid[MAXN][MAXN];    // 存储地图，'.' 表示草地，'#' 表示沼泽
int height[MAXN];         // 记录每列向上连续的草地高度
int answer[2 * MAXN];     // 统计半周长出现的次数，半周长 = 宽度 + 高度
rect stk[MAXN];           // 单调栈，用于维护候选矩形

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> grid[i];
    
    // 初始化高度数组和答案数组
    memset(height, 0, sizeof(height));
    memset(answer, 0, sizeof(answer));
    
    // 逐行处理
    for (int i = 0; i < n; i++) {
        int top = -1;  // 栈顶指针，-1 表示栈空
        
        // 逐列处理当前行
        for (int j = 0; j < m; j++) {
            // 更新当前列的高度：如果是沼泽则重置为 0，否则高度加 1
            height[j] = (grid[i][j] == '#') ? 0 : height[j] + 1;
            
            // 如果当前是沼泽，清空栈并跳过
            if (grid[i][j] == '#') {
                top = -1;
                continue;
            }
            
            // 创建当前矩形：起始列为 j，高度为 height[j]
            rect cur{j, height[j]};
            
            // 维护单调栈：弹出所有高度大于等于当前高度的矩形
            // 同时更新当前矩形的起始列为弹出矩形的最左起始列
            while (top >= 0 && stk[top].height >= cur.height) cur.start = stk[top--].start;
            
            // 压栈条件：栈为空 或 当前矩形比栈顶矩形有更大潜力
            // 潜力计算公式：height - start，表示矩形可能达到的最大半周长
            if (top < 0 || cur.height - cur.start > stk[top].height - stk[top].start) stk[++top] = cur;
            
            // 统计当前栈顶矩形的半周长
            // 宽度 = 当前列 - 起始列 + 1
            // 半周长 = 宽度 + 高度
            int width = j - stk[top].start + 1;
            answer[width + stk[top].height]++;
        }
    }
    // 输出结果：将半周长转换为实际周长（乘以2）
    for (int i = 1; i <= n + m; i++)
        if (answer[i])
            cout << answer[i] << " x " << 2 * i << endl;
}

int main() {
    // 加速IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
