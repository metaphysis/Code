// Choose and Divide
// UVa ID: 10375
// Verdict: Accepted
// Submission Date: 2018-03-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int p, q, r, s;
    while (cin >> p >> q >> r >> s)
    {
        long double e = 0;
        for (int up = p, down = 1; down <= q; up--, down++)
            e += log10(up) - log10(down);
        for (int up = r, down = 1; down <= s; up--, down++)
            e += log10(down) - log10(up);
        cout << fixed << setprecision(5) << pow(10, e) << '\n';
    }

    return 0;
}
