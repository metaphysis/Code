// Let's Dance!!
// UVa ID: 10218
// Verdict: Accepted
// Submission Date: 2018-06-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int M, W, C;
    while (cin >> M >> W >> C)
    {
        if (M == 0 && W == 0) break;
        double p = M * 1.0 / (M + W);
        cout << fixed << setprecision(7) << (1.0 + pow(1.0 - 2.0 * p, C)) / 2 << '\n';
    }

    return 0;
}
