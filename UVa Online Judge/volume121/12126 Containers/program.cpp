#include <bits/stdc++.h>
using namespace std;

void updateAnswer(long long rowCount, long long columnCount, long long &bestLength, long long &bestWidth, long long &bestArea, long long &bestDifference) {
    long long length = 44 * rowCount + 4;
    long long width = 10 * columnCount + 2;
    if (length < width) swap(length, width);
    long long area = length * width;
    long long difference = length - width;
    if (area < bestArea || (area == bestArea && difference < bestDifference)) {
        bestLength = length;
        bestWidth = width;
        bestArea = area;
        bestDifference = difference;
    }
}

void solveCase() {
    long long containerCount;
    cin >> containerCount;
    long long stackCount = (containerCount + 4) / 5;
    long long bestLength = 0;
    long long bestWidth = 0;
    long long bestArea = LLONG_MAX;
    long long bestDifference = LLONG_MAX;
    for (long long small = 1; small * small <= stackCount; ++small) {
        long long large = (stackCount + small - 1) / small;
        updateAnswer(small, large, bestLength, bestWidth, bestArea, bestDifference);
        updateAnswer(large, small, bestLength, bestWidth, bestArea, bestDifference);
    }
    cout << bestLength << " X " << bestWidth << " = " << bestArea << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCaseCount;
    cin >> testCaseCount;
    while (testCaseCount--)
        solveCase();
    return 0;
}
