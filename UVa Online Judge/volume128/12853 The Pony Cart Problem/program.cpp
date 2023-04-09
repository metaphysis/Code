// The Pony Cart Problem
// UVa ID: 12853
// Verdict: Accepted
// Submission Date: 2023-04-09
// UVa Run Time: 0.110s
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
        double D, N;
        cin >> D >> N;
        cout << 2.0 * acos(-1) * D * N / (N - 1.0) << '\n';
    }
    return 0;
}
