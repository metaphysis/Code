// Danger Point
// UVa ID: 10649
// Verdict: Accepted
// Submission Date: 2025-11-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;
int main() {
    double jamalToKamal, dangerToHouse;
    while (cin >> jamalToKamal >> dangerToHouse) {
        // 终止条件
        if (jamalToKamal == 0 && dangerToHouse == 0) break;
        // 计算平方差
        // 注意：题目描述的几何模型和实际求解存在矛盾，题目设置有问题
        double squaredDifference = jamalToKamal * jamalToKamal / 2.0 - dangerToHouse * dangerToHouse;
        // 检查数据是否合法
        if (squaredDifference < -EPS) {
            printf("INCORRECT INFORMATION !!!\n");
            continue;
        }
        // 计算并输出另一个距离
        double otherDistance = sqrt(squaredDifference);
        cout << fixed << setprecision(6) << otherDistance << '\n';
    }
    return 0;
}
