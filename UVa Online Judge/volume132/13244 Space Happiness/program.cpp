// Space Happiness
// UVa ID: 13244
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
using namespace std;
int main() {
    int testCaseCount; // 测试用例数量
    cin >> testCaseCount;
    while (testCaseCount--) {
        long long maxSpeed; // 最大速度 s
        cin >> maxSpeed;
        long long totalCost = (maxSpeed * maxSpeed + 1) / 2; // 使用公式计算总花费
        cout << totalCost << endl;
    }
    return 0;
}
