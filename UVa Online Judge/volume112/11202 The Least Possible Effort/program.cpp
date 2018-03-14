// The Least Possible Effort
// UVa ID: 11202
// Verdict: Accepted
// Submission Date: 2018-03-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m, cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        int nn = (n + 1) / 2;
        int mm = (m + 1) / 2;
        // How to prove it?
        if (n == m) cout << nn * (nn + 1) / 2 << '\n';
        else cout << nn * mm << '\n';
    }

    return 0;
}
