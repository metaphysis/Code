// Is It Multiple of 3
// UVa ID: 13178
// Verdict: Accepted
// Submission Date: 2023-06-17
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
        if (n % 3 == 1) cout << "NO";
        else cout << "YES";
        cout << '\n';
    }
    return 0;
}
