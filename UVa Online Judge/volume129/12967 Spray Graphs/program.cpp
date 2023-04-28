// Spray Graphs
// UVa ID: 12967
// Verdict: Accepted
// Submission Date: 2023-04-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    long long c[32] = {0, 1, 4};
    for (int i = 3; i <= 30; i++) c[i] = c[i - 1] * 2 + 4;
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        cout << c[n] << '\n';
    }
    return 0;
}
