// Joseph's Problem
// UVa ID: 1363
// Verdict: Accepted
// Submission Date: 2025-10-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n, k;
    while (cin >> n >> k) {
        long long totalSum = 0;
        long long maxIndex = min(n, k);
        
        // 分段计算 sum_{i=1..maxIndex} i * floor(k/i)
        long long currentIndex = 1;
        while (currentIndex <= maxIndex) {
            long long quotient = k / currentIndex;
            long long nextIndex = min(maxIndex, k / quotient);
            // 在区间 [currentIndex, nextIndex] 内 floor(k/t) = quotient
            long long segmentSum = quotient * (currentIndex + nextIndex) * (nextIndex - currentIndex + 1) / 2;
            totalSum += segmentSum;
            currentIndex = nextIndex + 1;
        }
        
        long long result = n * k - totalSum;
        cout << result << endl;
    }
    return 0;
}
