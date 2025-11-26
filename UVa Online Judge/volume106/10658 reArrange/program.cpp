// reArrange
// UVa ID: 10658
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

unsigned long long minMoves[66];

void precompute() {
    minMoves[0] = 0;
    bool pattern[] = {0, 1, 1, 0, 1, 1};
    for (int i = 1, k = 0; i < 66; i++, k = (k + 1) % 6) 
        minMoves[i] = 2 * minMoves[i - 1] + pattern[k];
}

int main() {
    precompute();
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << minMoves[n] << endl;
    }
    return 0;
}
