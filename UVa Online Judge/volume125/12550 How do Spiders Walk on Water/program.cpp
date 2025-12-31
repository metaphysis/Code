// How do Spiders Walk on Water
// UVa ID: 12550
// Verdict: Accepted
// Submission Date: 2025-12-25
// UVa Run Time: 0.090s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

double speeds[10005];
const double EPS = 1e-6;

int main() {
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        int D, P;
        ss >> D >> P;
        int n = 0;
        while (ss >> speeds[n]) n++;
        // 检查第一个位置速度是否超过蜘蛛跳跃能力
        if (speeds[0] > P) { cout << "The spider is going to fall!\n"; continue; }
        // 如果速度序列不完整，需要扩展
        if (n <= D) {
            // 检查是否为等比数列（后四项满足等比关系）
            if (abs(speeds[n - 4] * speeds[n - 2] - speeds[n - 3] * speeds[n - 3]) == 0)
                // 等比递推：S_m = S_{m-1}² / S_{m-2}
                while (n <= D) {
                    speeds[n] = speeds[n - 1] * speeds[n - 1] / speeds[n - 2];
                    n++;
                }
            else {
                // 线性递推：S_m = a·S_{m-2} + b·S_{m-1}
                double a = (speeds[n - 2] * speeds[n - 2] - speeds[n - 1] * speeds[n - 3]) / 
                           (speeds[n - 4] * speeds[n - 2] - speeds[n - 3] * speeds[n - 3]);
                double b = (speeds[n - 2] - a * speeds[n - 4]) / speeds[n - 3];
                while (n <= D) {
                    speeds[n] = a * speeds[n - 2] + b * speeds[n - 1];
                    n++;
                }
            }
        }
        // 查找第一个速度超过蜘蛛跳跃能力的位置
        int firstExceed = -1;
        for (int i = 0; i < n; i++)
            if (speeds[i] - EPS > P) {
                firstExceed = i;
                break;
            }
        // 输出结果
        if (firstExceed == -1) cout << "The spider may fall!" << endl;
        else cout << D - firstExceed + 1 << endl;

        // 虽然题目描述中说明，所有序列为非递减序列，但是在线测试数据中，
        // 包含一些序列，这些序列中的某些元素是负值且并不满足非递减的约束，
        // 因此不能使用二分查找来输出答案，只能逐项搜索。
        // int p = upper_bound(speeds, speeds + n, P) - speeds;
        // if (p >= n) cout << "The spider may fall!\n";
        // else cout << D - p + 1 << '\n';
    }
    return 0;
}
