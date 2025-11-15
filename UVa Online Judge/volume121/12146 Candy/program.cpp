// Candy
// UVa ID: 12146
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numRows, numCols;
    while (cin >> numRows >> numCols && (numRows != 0 || numCols != 0)) {
        vector<int> rowValues(numRows);

        for (int i = 0; i < numRows; ++i) {
            vector<int> currentRow(numCols);
            for (int j = 0; j < numCols; ++j) {
                cin >> currentRow[j];
            }

            // 计算这一行的最大值 (House Robber 问题)
            int dp0 = 0; // 不取当前元素时的最大值
            int dp1 = 0; // 取当前元素时的最大值
            for (int candies : currentRow) {
                int newDp0 = max(dp0, dp1);
                int newDp1 = dp0 + candies;
                dp0 = newDp0;
                dp1 = newDp1;
            }
            rowValues[i] = max(dp0, dp1);
        }

        // 在行最大值数组上再次应用 House Robber
        int finalDp0 = 0;
        int finalDp1 = 0;
        for (int value : rowValues) {
            int newFinalDp0 = max(finalDp0, finalDp1);
            int newFinalDp1 = finalDp0 + value;
            finalDp0 = newFinalDp0;
            finalDp1 = newFinalDp1;
        }

        cout << max(finalDp0, finalDp1) << "\n";
    }

    return 0;
}
