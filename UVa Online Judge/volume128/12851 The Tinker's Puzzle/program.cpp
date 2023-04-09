// The Tinker's Puzzle
// UVa ID: 12851
// Verdict: Accepted
// Submission Date: 2023-04-09
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
        double D, V;
        cin >> D >> V;
        cout << 2.0 * sqrt(12.0 * 282.0 * V / (7.0 * acos(-1) * D)) << '\n';
    }
    return 0;
}
