// Dropping Balls
// UVa ID: 679
// Verdict: Accepted
// Submission Date: 2016-08-25
// UVa Run Time: 0.090s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int cases, D, I;
    cin >> cases;
    for (int c = 1; c <= cases; c++) {
        cin >> D >> I;
        int pos = 1;
        for (int depth = 1; depth < D; depth++) {
            if (I % 2 == 1) {
                pos = pos * 2;
                I = (I + 1) / 2;
            } else {
                pos = pos * 2 + 1;
                I = I / 2;
            }
        }
        cout << pos << '\n';
    }
    return 0;
}
