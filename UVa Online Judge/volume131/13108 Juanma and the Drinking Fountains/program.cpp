// Juanma and the Drinking Fountains
// UVa ID: 13108
// Verdict: Accepted
// Submission Date: 2023-04-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        cout << (n * n * n * n - 6 * n * n * n + 23 * n * n - 18 * n + 24) / 24 << '\n';
    }
    return 0;
}
