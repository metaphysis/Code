// Rogue One: Time to Impact
// UVa ID: 13248
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int numCases;
    cin >> numCases;
    while (numCases--) {
        long long A, B;
        cin >> A >> B;
        long long impactTime = (10 * B) / (B - A); // 整数除法自动截断
        cout << impactTime << '\n';
    }
    return 0;
}
