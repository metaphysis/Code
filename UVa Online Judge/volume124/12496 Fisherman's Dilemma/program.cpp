// Fisherman's Dilemma
// UVa ID: 12496
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.040s

#include <bits/stdc++.h>
using namespace std;

long long gcdValue(long long firstValue, long long secondValue) {
    while (secondValue != 0) {
        long long remainder = firstValue % secondValue;
        firstValue = secondValue;
        secondValue = remainder;
    }
    return firstValue;
}

long long countSubarraysAtLeast(const vector<long long>& values, long long threshold) {
    int length = static_cast<int>(values.size());
    if (threshold <= 0) return 1LL * length * (length + 1) / 2;
    long long currentSum = 0;
    long long result = 0;
    int left = 0;
    for (int right = 0; right < length; right++) {
        currentSum += values[right];
        while (left <= right && currentSum >= threshold) {
            currentSum -= values[left];
            left++;
        }
        result += left;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    for (int caseNumber = 1; caseNumber <= testCases; caseNumber++) {
        int n, m;
        long long k;
        cin >> n >> m >> k;
        vector<vector<int>> originalGrid(n, vector<int>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> originalGrid[i][j];
        vector<vector<int>> fishGrid;
        if (n <= m) {
            fishGrid = originalGrid;
        } else {
            fishGrid.assign(m, vector<int>(n));
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    fishGrid[j][i] = originalGrid[i][j];
            swap(n, m);
        }
        long long validCount = 0;
        vector<long long> columnSum(m, 0);
        for (int top = 0; top < n; top++) {
            fill(columnSum.begin(), columnSum.end(), 0);
            for (int bottom = top; bottom < n; bottom++) {
                for (int column = 0; column < m; column++)
                    columnSum[column] += fishGrid[bottom][column];
                validCount += countSubarraysAtLeast(columnSum, k);
            }
        }
        long long totalCount = 1LL * n * (n + 1) / 2 * m * (m + 1) / 2;
        long long divisor = gcdValue(validCount, totalCount);
        validCount /= divisor;
        totalCount /= divisor;
        cout << "Case " << caseNumber << ": " << validCount << "/" << totalCount << '\n';
    }
    return 0;
}
