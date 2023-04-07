// Polygonal Park
// UVa ID: 13215
// Verdict: Accepted
// Submission Date: 2023-04-07
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
        int N, L;
        cin >> N;
        int A = 0, CS = 0, W = 0, aS = 0, aT = 0;
        char ch;
        for (int i = 0; i < N; i++) {
            cin >> ch >> L;
            if (CS <= 1) W += L;
            if (ch == 'C') { CS++; A += 2 * L; }
            else A += L;
            if (ch == 'C' || ch == 'S') aS += L * L;
            if (ch == 'T') aT += L * L;
        }
        A /= 2;
        cout << fixed << setprecision(4) << 1.0 * W * (A - W) - aS - sqrt(3) * aT / 4.0 << '\n';
    }
    return 0;
}
