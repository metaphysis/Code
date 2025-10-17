// Race
// UVa ID: 12034
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 10056;  // 模数
const int MAXN = 1000;  // 最大n值

int C[MAXN + 5][MAXN + 5];  // 组合数表
int ways[MAXN + 5];         // dp数组，存储n匹马的结果数

void init() {
    // 预处理组合数C(n,k) mod MOD
    for (int i = 0; i <= MAXN; i++) {
        C[i][0] = C[i][i] = 1;  // 边界条件
        for (int j = 1; j < i; j++) {
            // 帕斯卡公式
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    // 动态规划计算ways数组
    ways[0] = 1;  // 没有马时算1种方式
    for (int i = 1; i <= MAXN; i++) {
        ways[i] = 0;
        for (int j = 1; j <= i; j++) {
            // 递推公式：枚举第一名有j匹马
            ways[i] = (ways[i] + C[i][j] * ways[i - j]) % MOD;
        }
    }
}

int main() {
    init();  // 预处理
    
    int T;
    cin >> T;  // 测试用例数
    for (int tc = 1; tc <= T; tc++) {
        int n;
        cin >> n;  // 马匹数
        // 输出结果
        cout << "Case " << tc << ": " << ways[n] << endl;
    }
    return 0;
}
