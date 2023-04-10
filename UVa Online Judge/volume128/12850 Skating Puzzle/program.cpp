// Skating Puzzle
// UVa ID: 12850
// Verdict: Accepted
// Submission Date: 2023-04-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << fixed << setprecision(3);
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        double r, t;
        cin >> r >> t;
        cout << t / (r - 1.0) + 1e-7 << ' ' << t * r / (r - 1.0) + 1e-7 << '\n';
    }
    return 0;
}
