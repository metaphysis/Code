// A New Function
// UVa ID: 10830
// Verdict: Accepted
// Submission Date: 2023-07-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1, n;
    while (cin >> n, n) {
        cout << "Case " << cases++ << ": ";
        long long s = 0;
        for (int l = 2, r; l <= n; l = r + 1) {
            r = n / (n / l);
            s += 1LL * (n / l - 1) * (l + r) * (r - l + 1) / 2;
        }
        cout << s << '\n';
    }
    return 0;
}
