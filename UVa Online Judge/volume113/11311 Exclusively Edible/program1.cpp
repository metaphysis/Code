// Exclusively Edible
// UVa ID: 11311
// Verdict: Accepted
// Submission Date: 2018-06-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, m, n, r, c;
    int left, right, top, down;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> m >> n >> r >> c;
        left = c, right = n - c - 1;
        top = r, down = m - r - 1;
        if ((left ^ right ^ top ^ down) == 0) cout << "Hansel\n";
        else cout << "Gretel\n";
    }

    return 0;
}
