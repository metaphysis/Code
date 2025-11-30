// Pinary
// UVa ID: 1350
// Verdict: Accepted
// Submission Date: 2025-11-26
// UVa Run Time: 0.150s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 50;  // 90,000,000对应的斐波那契索引
long long fib[MAX_N];

void precomputeFibonacci() {
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < MAX_N; i++)
        fib[i] = fib[i-1] + fib[i-2];
}

string findPinaryNumber(long long k) {
    // 找到最大的斐波那契数不超过k
    int maxIndex = 0;
    while (fib[maxIndex] <= k) maxIndex++;
    maxIndex--;
    
    string result = "";
    bool lastWasOne = false;
    
    for (int i = maxIndex; i >= 0; i--) {
        if (fib[i] <= k && !lastWasOne) {
            result += '1';
            k -= fib[i];
            lastWasOne = true;
        } else {
            result += '0';
            lastWasOne = false;
        }
    }
    
    return result;
}

int main() {
    precomputeFibonacci();
    
    int t;
    cin >> t;
    
    while (t--) {
        long long k;
        cin >> k;
        cout << findPinaryNumber(k) << endl;
    }
    
    return 0;
}
