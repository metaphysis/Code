#include <bits/stdc++.h>
using namespace std;

int getSum(const vector<vector<int>> &pre, int x1, int y1, int x2, int y2) {
    return pre[x2 + 1][y2 + 1] - pre[x1][y2 + 1] - pre[x2 + 1][y1] + pre[x1][y1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int rowCount, colCount;
        cin >> rowCount >> colCount;
        vector<string> grid(rowCount);
        for (string &row : grid) cin >> row;
        int size = rowCount + colCount - 1;
        vector<vector<int>> pre(size + 1, vector<int>(size + 1, 0));
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < colCount; j++) {
                if (grid[i][j] == '#') pre[i + j + 1][i - j + colCount] = 1;
            }
        }
        for (int i = 1; i <= size; i++) {
            for (int j = 1; j <= size; j++) {
                pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
            }
        }
        int answer = 0;
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < colCount; j++) {
                if (grid[i][j] == '.') continue;
                int maxRadius = min(min(i, rowCount - 1 - i), min(j, colCount - 1 - j));
                int low = 0, high = maxRadius;
                while (low < high) {
                    int mid = (low + high + 1) / 2;
                    int centerU = i + j, centerV = i - j + colCount - 1;
                    int count = getSum(pre, centerU - mid, centerV - mid, centerU + mid, centerV + mid);
                    int area = 2 * mid * mid + 2 * mid + 1;
                    if (count == area) low = mid;
                    else high = mid - 1;
                }
                answer = max(answer, 2 * low + 1);
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
