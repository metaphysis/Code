// I am Dumb 3
// UVa ID: 12499
// Verdict: Accepted
// Submission Date: 2019-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, coins[64], n, L;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> L;
        for (int i = 0; i < n; i++) cin >> coins[i];
        coins[n] = L;
        int sg = 0;
        for (int i = 0; i < n; i += 2) sg ^= coins[i + 1] - coins[i];
        cout << "Case " << cs << ": " << (sg ? "First Player" : "Second Player") << '\n';
    }

    return 0;
}
