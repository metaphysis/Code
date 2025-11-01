// ENimEN
// UVa ID: 11892
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        bool allOne = true;
        int a;
        for (int i = 0; i < N; i++) {
            cin >> a;
            if (a > 1) allOne = false;
        }
        if (allOne) {
            if (N % 2 == 0) cout << "piloop\n";
            else cout << "poopi\n";
        } else cout << "poopi\n";
    }
    return 0;
}
