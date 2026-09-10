// Draw and Score
// UVa ID: 12474
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

using LongLong = long long;

LongLong sumPopcount(LongLong value) {
    if (value < 0)
        return 0;
    LongLong result = 0;
    for (LongLong bit = 1; bit <= value; bit <<= 1) {
        LongLong cycle = bit << 1;
        LongLong fullCycle = (value + 1) / cycle;
        LongLong remainder = (value + 1) % cycle;
        result += fullCycle * bit;
        if (remainder > bit)
            result += remainder - bit;
    }
    return result;
}

LongLong calculateAnswer(LongLong nodeCount) {
    if (nodeCount <= 2)
        return 0;
    LongLong highestBit = 1;
    LongLong exponent = 0;
    while ((highestBit << 1) <= nodeCount) {
        highestBit <<= 1;
        ++exponent;
    }
    LongLong baseAnswer = (exponent - 2) * (highestBit >> 1) + 1;
    LongLong remainder = nodeCount - highestBit;
    return baseAnswer + sumPopcount(remainder);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseNumber = 1; caseNumber <= testCount; ++caseNumber) {
        LongLong nodeCount;
        cin >> nodeCount;
        cout << "Case " << caseNumber << ": " << calculateAnswer(nodeCount) << '\n';
    }
    return 0;
}
