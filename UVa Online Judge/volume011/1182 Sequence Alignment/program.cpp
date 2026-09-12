// Sequence Alignment
// UVa ID: 1182
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.140s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        string firstString, secondString;
        cin >> firstString >> secondString;
        int firstLength = firstString.size();
        int secondLength = secondString.size();
        const int negativeInf = -1000000000;
        vector<vector<int>> diag(firstLength + 1, vector<int>(secondLength + 1, negativeInf));
        vector<vector<int>> gapA(firstLength + 1, vector<int>(secondLength + 1, negativeInf));
        vector<vector<int>> gapB(firstLength + 1, vector<int>(secondLength + 1, negativeInf));
        for (int i = 0; i <= firstLength; ++i)
            for (int j = 0; j <= secondLength; ++j)
                diag[i][j] = 0;
        for (int i = 1; i <= firstLength; ++i)
            for (int j = 1; j <= secondLength; ++j) {
                int previousDiag = max(diag[i - 1][j - 1], max(gapA[i - 1][j - 1], gapB[i - 1][j - 1]));
                diag[i][j] = max(diag[i][j], previousDiag + (firstString[i - 1] == secondString[j - 1] ? 2 : 0));
                gapA[i][j] = max(diag[i - 1][j] - 1, gapA[i - 1][j]);
                gapA[i][j] = max(gapA[i][j], gapB[i - 1][j] - 1);
                gapB[i][j] = max(diag[i][j - 1] - 1, gapB[i][j - 1]);
                gapB[i][j] = max(gapB[i][j], gapA[i][j - 1] - 1);
            }
        cout << max(diag[firstLength][secondLength], max(gapA[firstLength][secondLength], gapB[firstLength][secondLength])) << '\n';
    }
    return 0;
}
