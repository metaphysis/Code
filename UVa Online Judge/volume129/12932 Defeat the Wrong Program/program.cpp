// Defeat the Wrong Program
// UVa ID: 12932
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, caseNo = 1;
    while (cin >> n >> m) {
        vector<vector<int>> grid(n, vector<int>(m));
        vector<int> rowSum(n, 0), colSum(m, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                cin >> grid[i][j];
                rowSum[i] += grid[i][j];
                colSum[j] += grid[i][j];
            }
        int selectedRow = 0;
        for (int i = 1; i < n; ++i)
            if (rowSum[i] > rowSum[selectedRow]) selectedRow = i;
        int selectedCol = 0;
        for (int j = 1; j < m; ++j)
            if (colSum[j] > colSum[selectedCol]) selectedCol = j;
        int wrongSum = rowSum[selectedRow] + colSum[selectedCol] - grid[selectedRow][selectedCol];
        int bestSum = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                bestSum = max(bestSum, rowSum[i] + colSum[j] - grid[i][j]);
        cout << "Case " << caseNo++ << ": " << (wrongSum == bestSum ? "Weak" : "Strong") << '\n';
    }
    return 0;
}
