// Structural Equivalence
// UVa ID: 10904
// Verdict: Accepted
// Submission Date: 2026-06-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int dp[256][256];       // 记忆化：1等价，-1不等，0未算；递归中设为1表示正在访问（环检测）
int typeDef[256][256];  // 每个类型的定义字符串
int done[256];          // 输出标记

// 判断类型 a 和 b 是否结构等价
bool dfs(int a, int b) {
    if (dp[a][b] == 1) return true;          // 在递归栈中，视为等价（环）
    if (dp[a][b] == -1) return false;        // 已计算为不等
    // 展开引用
    if (isupper(typeDef[a][0])) return dfs(typeDef[a][0], b);
    if (isupper(typeDef[b][0])) return dfs(a, typeDef[b][0]);
    // 基本类型不同
    if (typeDef[a][0] != typeDef[b][0]) return false;
    // 基本类型相同且非结构体（原始类型）
    if (typeDef[a][0] != 's') return true;
    // 均为结构体：先标记正在比较
    dp[a][b] = dp[b][a] = 1;
    // 逐个比较字段
    int idx = 1;
    while (typeDef[a][idx] && typeDef[b][idx] && dfs(typeDef[a][idx], typeDef[b][idx]))
        ++idx;
    // 两者字段同时结束则等价，否则不等
    int r = (!typeDef[a][idx] && !typeDef[b][idx]) ? 1 : -1;
    dp[a][b] = dp[b][a] = r;
    return r == 1;
}

int main() {
    char op[100], lhs, rhs;
    // 预定义原始类型（小写字母作为特殊节点）
    typeDef['i'][0] = 'i';
    typeDef['c'][0] = 'c';
    typeDef['r'][0] = 'r';
    for (int cs = 0; strcmp(op, "--"); ++cs) {
        if (cs) {
            printf("\n");
            memset(dp, 0, sizeof(dp));
            memset(typeDef, 0, sizeof(typeDef));
            memset(done, 0, sizeof(done));
            // 重新初始化原始类型
            typeDef['i'][0] = 'i';
            typeDef['c'][0] = 'c';
            typeDef['r'][0] = 'r';
        }
        // 读取本测试用例的所有定义
        while (scanf("%s", op) == 1 && *op != '-') {
            // op 应为 "type"
            scanf(" %c = %c%*[a-z(]", &lhs, &rhs);
            typeDef[(int)lhs][0] = rhs;
            if (rhs == 's') {   // 结构体，读取字段列表直到 ')'
                int j = 1;
                while (scanf(" %c", &typeDef[(int)lhs][j]) && typeDef[(int)lhs][j] != ')')
                    ++j;
                typeDef[(int)lhs][j] = 0;  // 字符串结束符
            }
        }
        // 输出所有等价类
        for (int i = 'A'; i <= 'Z'; ++i) {
            if (!typeDef[i][0] || done[i]) continue;
            printf("%c", i);
            for (int j = i + 1; j <= 'Z'; ++j) {
                if (done[j]) continue;
                if (dfs(i, j)) {
                    printf(" %c", j);
                    done[j] = 1;
                }
            }
            done[i] = 1;
            printf("\n");
        }
    }
    return 0;
}
