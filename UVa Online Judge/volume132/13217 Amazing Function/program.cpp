// Amazing Function
// UVa ID: 13217
// Verdict: Accepted
// Submission Date: 2022-10-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double f[32];
    f[0] = sqrt(2) + sqrt(3) + sqrt(6);
    for (int i = 1; i <= 20; i++)
        f[i] = (f[i - 1] * f[i - 1] - 5) / (2 * f[i - 1] + 4);
    cout << fixed << setprecision(10);
    string line;
    while (getline(cin, line))
    {
        if (line.length() == 1) cout << f[line.back() - '0'];
        else cout << f[4 - (line.back() - '0') % 2];
        cout << '\n';
    }

    return 0;
}
