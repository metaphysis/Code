#include <bits/stdc++.h>
using namespace std;

long long getGcd(long long first, long long second) {
    first = abs(first);
    second = abs(second);
    while (second != 0) {
        long long remainder = first % second;
        first = second;
        second = remainder;
    }
    return first;
}

long long getDet(long long firstX, long long firstY, long long secondX, long long secondY) {
    return firstX * secondY - firstY * secondX;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        long long firstX, firstY, secondX, secondY, thirdX, thirdY;
        cin >> firstX >> firstY >> secondX >> secondY >> thirdX >> thirdY;
        long long firstDet = getDet(firstX, firstY, secondX, secondY);
        long long secondDet = getDet(firstX, firstY, thirdX, thirdY);
        long long thirdDet = getDet(secondX, secondY, thirdX, thirdY);
        long long answer = getGcd(getGcd(firstDet, secondDet), thirdDet);
        cout << "Case #" << caseId << ": " << answer << '\n';
    }
    return 0;
}
