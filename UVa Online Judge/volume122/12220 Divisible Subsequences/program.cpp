// Divisible Subsequences
// UVa ID: 12220
// Verdict: Accepted
// Submission Date: 2025-11-29
// UVa Run Time: 0.150s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int testCaseCount;
    cin >> testCaseCount;
    while (testCaseCount--) {
        int divisor, sequenceLength;
        cin >> divisor >> sequenceLength;
        vector<long long> prefixModCount(divisor, 0);
        prefixModCount[0] = 1;  // 初始前缀和 0 的余数为 0
        long long prefixSum = 0;
        for (int i = 0; i < sequenceLength; i++) {
            long long num;
            cin >> num;
            prefixSum += num;
            int remainder = prefixSum % divisor;
            prefixModCount[remainder]++;
        }
        long long result = 0;
        for (int i = 0; i < divisor; i++) {
            long long count = prefixModCount[i];
            result += count * (count - 1) / 2;  // 组合数 C(count, 2)
        }
        cout << result << endl;
    }
    return 0;
}
