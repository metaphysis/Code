// Perfecct Flag
// UVa ID: 12894
// Verdict: Accepted
// Submission Date: 2023-04-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int x0, y0, x1, y1, cx, cy, r;
        cin >> x0 >> y0 >> x1 >> y1 >> cx >> cy >> r;
        int L = abs(x0 - x1);
        int W = abs(y0 - y1);
        if (6 * L != 10 * W) {
            cout << "NO\n";
            continue;
        }
        if (5 * r != L) {
            cout << "NO\n";
            continue;
        }
        if (2 * abs(y0 - cy) != W) {
            cout << "NO\n";
            continue;
        }
        if (10 * 2 * abs(x0 - cx) != 9 * L) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
    return 0;
}
