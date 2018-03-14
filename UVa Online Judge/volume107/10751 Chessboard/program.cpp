// Chessboard
// UVa ID: 10751
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

    int cases, n;
    cin >> cases;

    for (int c = 0; c < cases; c++)
    {
        cin >> n;
        if (c) cout << '\n';
        if (n == 1) cout << "0.000\n";
        else
        {
            // How to prove it?
            double path = (n * n + (sqrt(2) - 1) * (n - 2) * (n - 2));
            cout << fixed << setprecision(3) << path << '\n';
        }
    }

    return 0;
}
