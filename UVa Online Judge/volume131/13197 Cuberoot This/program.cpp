// Cuberoot This
// UVa ID: 13197
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, p;
    while (cin >> a >> p) {
        bool first = true;
        for (int x = 0; x < p; ++x) {
            if ((1LL * x * x * x) % p == a) {
                if (!first) cout << ' ';
                cout << x;
                first = false;
            }
        }
        cout << '\n';
    }
    return 0;
}
