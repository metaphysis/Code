// What is the Probability?
// UVa ID: 10056
// Verdict: Accepted
// Submission Date: 2018-06-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, r;
    double p, win;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> p >> r;
        win = p;
        if (p > 0.0) win *= pow(1.0 - p, r - 1) / (1.0 - pow(1.0 - p, n));
        cout << fixed << setprecision(4) << win << '\n';
    }

    return 0;
}
