// Nested Rectangles
// UVa ID: 11263
// Verdict: Wrong Answer
// Submission Date: 2026-09-25
// UVa Run Time: 0.330s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long getRectSum(const vector<vector<long long>>& prefixSum, int top, int left, int bottom, int right) {
    return prefixSum[bottom][right] - prefixSum[top][right] - prefixSum[bottom][left] + prefixSum[top][left];
}

vector<vector<long long>> getWindowMax(const vector<vector<long long>>& value, int height, int width) {
    int rowCount = value.size();
    int colCount = value[0].size();
    int targetRows = rowCount - height + 1, targetCols = colCount - width + 1;
    vector<vector<long long>> rowMax(rowCount, vector<long long>(targetCols));
    for (int i = 0; i < rowCount; i++) {
        deque<int> que;
        for (int j = 0; j < colCount; j++) {
            while (!que.empty() && value[i][que.back()] <= value[i][j])
                que.pop_back();
            que.push_back(j);
            while (!que.empty() && que.front() < j - width + 1)
                que.pop_front();
            if (j >= width - 1)
                rowMax[i][j - width + 1] = value[i][que.front()];
        }
    }
    vector<vector<long long>> result(targetRows, vector<long long>(targetCols));
    for (int j = 0; j < targetCols; j++) {
        deque<int> que;
        for (int i = 0; i < rowCount; i++) {
            while (!que.empty() && rowMax[que.back()][j] <= rowMax[i][j])
                que.pop_back();
            que.push_back(i);
            while (!que.empty() && que.front() < i - height + 1)
                que.pop_front();
            if (i >= height - 1)
                result[i - height + 1][j] = rowMax[que.front()][j];
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int rowCount, colCount, n;
        cin >> rowCount >> colCount >> n;
        vector<int> rowSize(n + 1), colSize(n + 1);
        vector<long long> multiplier(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> rowSize[i];
        for (int i = 1; i <= n; i++)
            cin >> colSize[i];
        for (int i = 0; i <= n; i++)
            cin >> multiplier[i];
        vector<vector<long long>> prefixSum(rowCount + 1, vector<long long>(colCount + 1, 0));
        for (int i = 1; i <= rowCount; i++) {
            for (int j = 1; j <= colCount; j++) {
                long long value;
                cin >> value;
                prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + value;
            }
        }
        long long answer = multiplier[0] * prefixSum[rowCount][colCount];
        int currentRows = rowCount - rowSize[n] + 1, currentCols = colCount - colSize[n] + 1;
        long long coefficient = multiplier[n] - multiplier[n - 1];
        vector<vector<long long>> dp(currentRows, vector<long long>(currentCols));
        for (int i = 0; i < currentRows; i++) {
            for (int j = 0; j < currentCols; j++) {
                long long rectangleSum = getRectSum(prefixSum, i, j, i + rowSize[n], j + colSize[n]);
                dp[i][j] = coefficient * rectangleSum;
            }
        }
        for (int level = n - 1; level >= 1; level--) {
            int rowDiff = rowSize[level] - rowSize[level + 1];
            int colDiff = colSize[level] - colSize[level + 1];
            vector<vector<long long>> best = getWindowMax(dp, rowDiff + 1, colDiff + 1);
            currentRows = rowCount - rowSize[level] + 1;
            currentCols = colCount - colSize[level] + 1;
            coefficient = multiplier[level] - multiplier[level - 1];
            vector<vector<long long>> currentDp(currentRows, vector<long long>(currentCols));
            for (int i = 0; i < currentRows; i++) {
                for (int j = 0; j < currentCols; j++) {
                    long long rectangleSum = getRectSum(prefixSum, i, j, i + rowSize[level], j + colSize[level]);
                    currentDp[i][j] = coefficient * rectangleSum + best[i][j];
                }
            }
            dp.swap(currentDp);
        }
        long long bestValue = dp[0][0];
        for (int i = 0; i < currentRows; i++)
            for (int j = 0; j < currentCols; j++)
                bestValue = max(bestValue, dp[i][j]);
        cout << answer + bestValue << '\n';
    }
    return 0;
}
