// Silly Sort
// UVa ID: 1016
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int caseNum = 1;
    int n;
    while (cin >> n && n != 0) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        vector<int> sortedArr = arr;
        sort(sortedArr.begin(), sortedArr.end());

        // 位置映射：值 -> 在排序后的索引
        vector<int> pos(1000, -1);
        for (int i = 0; i < n; i++) {
            pos[sortedArr[i]] = i;
        }

        vector<bool> visited(n, false);
        int globalMin = sortedArr[0];
        int totalCost = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || pos[arr[i]] == i) {
                continue;
            }

            // 找到一个循环
            int cycleMin = INT_MAX;
            int cycleSum = 0;
            int cycleLen = 0;
            int cur = i;

            while (!visited[cur]) {
                visited[cur] = true;
                cycleLen++;
                cycleSum += arr[cur];
                if (arr[cur] < cycleMin) {
                    cycleMin = arr[cur];
                }
                cur = pos[arr[cur]];
            }

            // 策略1：仅用循环内最小值交换
            int cost1 = cycleSum + (cycleLen - 2) * cycleMin;
            // 策略2：借助全局最小值交换
            int cost2 = cycleSum + cycleMin + (cycleLen + 1) * globalMin;

            totalCost += min(cost1, cost2);
        }

        cout << "Case " << caseNum << ": " << totalCost << "\n\n";
        caseNum++;
    }

    return 0;
}
