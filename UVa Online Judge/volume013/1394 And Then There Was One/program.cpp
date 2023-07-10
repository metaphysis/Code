// And Then There Was One
// UVa ID: 1394
// Verdict: Accepted
// Submission Date: 2023-07-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h> 
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, k, m;
    while (cin >> n >> k >> m) {
        if (!n) break;
        int last = 0;
        for (int i = 2; i <= n; i++) last = (last + k) % i;
        cout << ((last + (m - k) % n + n) % n + 1) << '\n';
    }
    return 0;
}
