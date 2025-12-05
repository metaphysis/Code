// Hamming Base
// UVa ID: 11979
// Verdict: Accepted
// Submission Date: 2025-12-05
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int testCases;
    cin >> testCases;
    for (int caseNo = 1; caseNo <= testCases; caseNo++) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> digits(n, vector<int>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> digits[i][j];
        long long totalSteps = 0;
        // 对每个位置独立处理
        for (int pos = 0; pos < m; pos++) {
            vector<int> currentDigits(n);
            for (int i = 0; i < n; i++)
                currentDigits[i] = digits[i][pos];
            sort(currentDigits.begin(), currentDigits.end());
            // 排序后一一匹配到 0,1,...,n-1
            for (int i = 0; i < n; i++)
                totalSteps += abs(currentDigits[i] - i);
        }
        cout << "Case " << caseNo << ": " << totalSteps << endl;
    }
    return 0;
}
