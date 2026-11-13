// Tile Code
// UVa ID: 1224
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int MAXN = 30;
    long long f[MAXN + 1] = {};
    f[0] = 1;
    f[1] = 1;
    for (int n = 2; n <= MAXN; n++) f[n] = f[n - 1] + 2 * f[n - 2];
    int cases;
    cin >> cases;
    while (cases--) {
        int n;
        cin >> n;
        long long symmetric;
        if (n % 2 == 1) symmetric = f[n / 2];
        else {
            int k = n / 2;
            symmetric = f[k] + 2 * f[k - 1];
        }
        cout << (f[n] + symmetric) / 2 << '\n';
    }
    return 0;
}
