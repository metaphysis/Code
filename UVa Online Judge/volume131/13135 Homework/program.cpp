// Homework
// UVa ID: 13135
// Verdict: Accepted
// Submission Date: 2019-04-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, S;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> S;
        S = 8 * S + 1;
        int s = sqrt(S);
        bool yes = false;
        for (int k = s - 1; k <= s + 1; k++)
            if (k * k == S)
            {
                yes = true;
                S = k;
            }
        if (yes) cout << (S - 3) / 2 << '\n';
        else cout << "No solution\n";
    }

    return 0;
}
