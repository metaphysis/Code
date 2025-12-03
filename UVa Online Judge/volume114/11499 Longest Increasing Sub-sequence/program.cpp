// Longest Increasing Sub-sequence
// UVa ID: 11499
// Verdict: Accepted
// Submission Date: 2025-12-03
// UVa Run Time: 0.660s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int g[605][605]; // 存储矩阵
int sum[605];    // sum[k]：对于当前列区间，第k行连续递增的长度
int n, m;

int main() {
    while (scanf("%d %d", &n, &m) == 2) {
        if (n + m == 0) break;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &g[i][j]);

        int ret = 1; // 答案至少为1（单个元素）
        // 枚举子矩阵的左边界
        for (int left = 0; left < m; left++) {
            memset(sum, 0, sizeof(sum)); // 每次左边界变化时重置sum数组
            // 枚举子矩阵的右边界
            for (int right = left; right < m; right++) {
                int width = right - left + 1; // 当前子矩阵的列数（宽度）
                int l = 0; // 滑动窗口的左边界（行号），表示当前候选子矩阵的顶边
                // 遍历每一行作为子矩阵的底边
                for (int k = 0; k < n; k++) {
                    // 更新当前行在列区间[left, right]内的连续递增长度
                    if (width == 1) {
                        // 单列总是递增的
                        sum[k] = 1;
                    } else {
                        // 如果当前列比前一列大，则递增序列可以延长
                        if (g[k][right] > g[k][right - 1])
                            sum[k]++; // 增加连续递增长度
                        else
                            sum[k] = 1; // 否则从头开始（仅当前列）
                    }

                    // 检查行间衔接是否满足递增：当前行左端元素 > 上一行右端元素
                    if (k > 0 && g[k][left] <= g[k - 1][right]) {
                        // 不满足，则窗口必须从当前行重新开始
                        l = k;
                    }

                    // 检查当前行在列区间内是否完全递增
                    if (sum[k] != width) {
                        // 不完全递增，则当前行不能作为子矩阵的一部分，
                        // 窗口左边界移到下一行
                        l = k + 1;
                    }

                    // 收缩窗口：如果当前行的连续递增长度不足宽度，
                    // 则需要不断抬高窗口顶边，直到满足条件或窗口为空
                    while (l <= k && sum[k] < width) {
                        l++;
                    }

                    // 如果窗口非空，计算面积并更新答案
                    if (l <= k) {
                        int height = k - l + 1; // 子矩阵的行数（高度）
                        ret = max(ret, height * width);
                    }
                }
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
