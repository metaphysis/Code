// Humbertov and the Triangular Spiral
// UVa ID: 13189
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.110s

#include <bits/stdc++.h>
using namespace std;

pair<long long, long long> getPoint(long long number) {
    // 确定点所在的三角形层数
    long long layer = static_cast<long long>(sqrtl(number - 1) / 2) + 1;
    while (4 * layer * layer < number)
        ++layer;
    while (layer > 1 && 4 * (layer - 1) * (layer - 1) >= number)
        --layer;
    long long position = number - 4 * (layer - 1) * (layer - 1);
    long long baseLength = 4 * layer - 2;
    if (position <= baseLength)
        return {2 * layer - 2 - (position - 1), 1 - layer};
    position -= baseLength;
    if (position <= 2 * layer - 1)
        return {-2 * layer + 1 + position, 1 - layer + position};
    position -= 2 * layer - 1;
    return {position, layer - position};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        long long number;
        cin >> number;
        pair<long long, long long> point = getPoint(number);
        cout << point.first << ' ' << point.second << '\n';
    }
    return 0;
}
