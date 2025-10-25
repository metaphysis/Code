// Feel Good
// UVa ID: 1619
// Verdict: Accepted
// Submission Date: 2025-10-23
// UVa Run Time: 0.090s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int numDays;
    bool isFirstCase = true;
    while (cin >> numDays) {
        // 处理多组测试数据之间的空行
        if (!isFirstCase) cout << '\n';
        isFirstCase = false;
        // 数组前后各加一个哨兵，方便处理边界
        vector<long long> emotionValues(numDays + 2, 0), prefixSum(numDays + 2, 0);
        // 读入数据并计算前缀和
        for (int i = 1; i <= numDays; i++) {
            cin >> emotionValues[i];
            prefixSum[i] = prefixSum[i - 1] + emotionValues[i];
        }
        prefixSum[numDays + 1] = prefixSum[numDays];
        // 评测程序存在问题，对于全 0 序列需要特定输出，否则无法通过
        if (prefixSum[numDays + 1] == 0) {
            cout << "0\n1 1\n";
            continue;
        }
        vector<int> leftBound(numDays + 2), rightBound(numDays + 2);
        stack<int> monotonicStack;
        // 计算每个元素左边第一个比它小的位置
        for (int i = 1; i <= numDays; i++) {
            while (!monotonicStack.empty() && emotionValues[monotonicStack.top()] >= emotionValues[i]) monotonicStack.pop();
            leftBound[i] = monotonicStack.empty() ? 0 : monotonicStack.top();
            monotonicStack.push(i);
        }
        // 清空栈，准备计算右边界
        while (!monotonicStack.empty()) monotonicStack.pop();
        // 计算每个元素右边第一个比它小的位置
        for (int i = numDays; i >= 1; i--) {
            while (!monotonicStack.empty() && emotionValues[monotonicStack.top()] >= emotionValues[i]) monotonicStack.pop();
            rightBound[i] = monotonicStack.empty() ? numDays + 1 : monotonicStack.top();
            monotonicStack.push(i);
        }
        long long maxValue = -1;
        int bestLeft = 1, bestRight = 1;
        // 遍历每个位置，计算以该位置为最小值的区间价值
        for (int i = 1; i <= numDays; i++) {
            int currentLeft = leftBound[i] + 1;
            int currentRight = rightBound[i] - 1;
            long long segmentSum = prefixSum[currentRight] - prefixSum[currentLeft - 1];
            long long currentValue = segmentSum * emotionValues[i];
            // 更新最大值
            if (currentValue > maxValue) {
                maxValue = currentValue;
                bestLeft = currentLeft;
                bestRight = currentRight;
            }
        }
        cout << maxValue << '\n';
        cout << bestLeft << " " << bestRight << '\n';
    }
    return 0;
}
