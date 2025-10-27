// Activation
// UVa ID: 1498
// Verdict: Accepted
// Submission Date: 2025-10-27
// UVa Run Time: 0.140s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net
//
// https://blog.csdn.net/metaphysis/article/details/153974922

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

const int MAXN = 2005;
const double EPS = 1e-9;

double dp[MAXN][MAXN];  // dp[i][j]: 队列有i个人，番茄在第j个位置时的概率
double powp1[MAXN];     // 存储p21的幂次，用于快速计算
double c[MAXN];         // 辅助数组，存储中间计算结果

int main() {
    int N, M, K;
    double p1, p2, p3, p4;
    
    // 处理多组测试数据
    while (scanf("%d%d%d%lf%lf%lf%lf", &N, &M, &K, &p1, &p2, &p3, &p4) == 7) {
        // 如果服务器宕机概率为0，直接输出0
        if (fabs(p4) < EPS) {
            printf("0.00000\n");
            continue;
        }
        
        // 预处理概率系数
        double p21 = p2 / (1 - p1);
        double p31 = p3 / (1 - p1);
        double p41 = p4 / (1 - p1);
        
        // 计算p21的幂次，用于后续计算
        powp1[0] = 1.0;
        for (int i = 1; i <= N; i++) {
            powp1[i] = powp1[i-1] * p21;
        }
        
        // 初始化边界条件
        dp[1][1] = p41 / (1 - p21);
        c[1] = p41;
        
        // 动态规划求解
        for (int i = 2; i <= N; i++) {
            // 计算c数组
            for (int j = 2; j <= i; j++) {
                c[j] = p31 * dp[i-1][j-1];
                if (j <= K) {
                    c[j] += p41;  // 前K个位置，服务器宕机时满足条件
                }
            }
            
            // 解出dp[i][i]
            double sum = 0.0;
            for (int j = 1; j <= i; j++) {
                sum += powp1[i - j] * c[j];
            }
            dp[i][i] = sum / (1 - powp1[i]);
            
            // 回代计算其他dp[i][j]
            dp[i][1] = p21 * dp[i][i] + c[1];
            for (int j = 2; j < i; j++) {
                dp[i][j] = p21 * dp[i][j-1] + c[j];
            }
        }
        
        // 输出结果，保留5位小数
        printf("%.5f\n", dp[N][M]);
    }
    return 0;
}
