// The Turanga Leela Problem
// UVa ID: 12465
// Verdict: Accepted
// Submission Date: 2025-11-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int countDivisors(int n) {
    int count = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            count++;
            if (i != n / i) count++;
        }
    }
    return count;
}

int main() {
    int a, b;
    while (cin >> a >> b && (a || b)) {
        int diff = abs(a - b);
        cout << countDivisors(diff) << endl;
    }
    return 0;
}
