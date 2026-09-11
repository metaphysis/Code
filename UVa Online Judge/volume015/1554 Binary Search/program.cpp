// Binary Search
// UVa ID: 1554
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

bool isValid(int targetIndex, int targetCount, int arraySize) {
    if (targetIndex >= arraySize)
        return false;
    int leftBorder = 0;
    int rightBorder = arraySize - 1;
    int compareCount = 0;
    while (leftBorder <= rightBorder) {
        int middleIndex = (leftBorder + rightBorder) / 2;
        ++compareCount;
        if (middleIndex == targetIndex)
            return compareCount == targetCount;
        if (middleIndex < targetIndex)
            leftBorder = middleIndex + 1;
        else
            rightBorder = middleIndex - 1;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int targetIndex, targetCount;
    while (cin >> targetIndex >> targetCount) {
        vector<pair<int, int>> intervals;
        bool inInterval = false;
        int intervalStart = 0;
        int intervalEnd = 0;
        for (int arraySize = 1; arraySize <= 10000; ++arraySize) {
            if (!isValid(targetIndex, targetCount, arraySize)) {
                if (inInterval) {
                    intervals.push_back({intervalStart, intervalEnd});
                    inInterval = false;
                }
                continue;
            }
            if (!inInterval) {
                intervalStart = arraySize;
                intervalEnd = arraySize;
                inInterval = true;
            } else if (arraySize == intervalEnd + 1) {
                intervalEnd = arraySize;
            } else {
                intervals.push_back({intervalStart, intervalEnd});
                intervalStart = arraySize;
                intervalEnd = arraySize;
            }
        }
        if (inInterval)
            intervals.push_back({intervalStart, intervalEnd});
        cout << intervals.size() << '\n';
        for (const auto& interval : intervals)
            cout << interval.first << ' ' << interval.second << '\n';
    }
    return 0;
}
