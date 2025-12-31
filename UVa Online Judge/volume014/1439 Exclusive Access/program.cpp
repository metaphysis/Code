// Exclusive Access
// UVa ID: 1439
// Verdict: Accepted
// Submission Date: 2025-12-30
// UVa Run Time: 0.830s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 105;
const int MAX_C = 15;           // 最多15个资源
const int ALL = 1 << MAX_C;     // 所有资源的状态压缩
const int INF = 0x3f3f3f3f;

int n;                          // 进程数量
int processRes[MAX_N][2];       // 每个进程需要的两个资源
bool conflict[MAX_C][MAX_C];    // 冲突图：资源之间是否有进程同时使用
bool validSet[ALL];             // 标记哪些资源集合是合法的独立集
int dp[ALL];                    // dp[s]: 覆盖资源集合s的最小组数
int preState[ALL];              // 记录最优解的前一个状态
int resourcePos[MAX_C];         // 每个资源的位置值

int main() {
    while (cin >> n) {
        // 初始化
        memset(conflict, 0, sizeof conflict);
        // 读取输入并建立冲突图
        char a, b;
        for (int i = 0; i < n; i++) {
            cin >> a >> b;
            int res1 = a - 'L';
            int res2 = b - 'L';
            processRes[i][0] = res1;
            processRes[i][1] = res2;
            conflict[res1][res2] = conflict[res2][res1] = true;
        }
        // 预处理所有合法子集（独立集）
        for (int s = 0; s < ALL; s++) {
            bool isValid = true;
            // 检查集合中任意两个资源是否冲突
            for (int i = 0; i < MAX_C && isValid; i++) if (s & (1 << i))
                for (int j = i + 1; j < MAX_C && isValid; j++) if (s & (1 << j))
                    if (conflict[i][j]) isValid = false;
            validSet[s] = isValid;
        }
        // 状态压缩DP：求解最小分组数
        memset(dp, 0x3f, sizeof dp);
        dp[0] = 0;
        for (int s = 1; s < ALL; s++) {
            // 枚举s的所有子集作为上一状态
            for (int s0 = (s - 1) & s; ; s0 = (s0 - 1) & s) {
                if (validSet[s ^ s0])  // 新加入的集合是独立集
                    if (dp[s] > dp[s0] + 1) {
                        dp[s] = dp[s0] + 1;
                        preState[s] = s0;
                    }
                if (s0 == 0) break;
            }
            // 也可以直接从空集转移
            if (validSet[s])
                if (dp[s] > dp[0] + 1) {
                    dp[s] = dp[0] + 1;
                    preState[s] = 0;
                }
        }
        // 输出最小链长：组数-2（因为位置从1开始，且链长=组数-1）
        printf("%d\n", dp[ALL - 1] - 2);
        // 重建解：为每个资源分配位置值
        int currentLayer = dp[ALL - 1];  // 总层数
        for (int s = ALL - 1; s > 0; s = preState[s]) {
            int diff = s ^ preState[s];  // 本层包含的资源
            for (int i = 0; i < MAX_C; i++)
                if (diff & (1 << i))
                    resourcePos[i] = currentLayer;
            currentLayer--;
        }
        // 输出每个进程的资源获取顺序
        for (int i = 0; i < n; i++) {
            int res1 = processRes[i][0];
            int res2 = processRes[i][1];
            if (resourcePos[res1] < resourcePos[res2])
                printf("%c %c\n", 'L' + res1, 'L' + res2);
            else
                printf("%c %c\n", 'L' + res2, 'L' + res1);
        }
    }
    return 0;
}
