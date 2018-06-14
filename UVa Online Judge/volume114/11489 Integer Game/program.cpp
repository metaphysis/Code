// Integer Game
// UVa ID: 11489
// Verdict: Accepted
// Submission Date: 2018-06-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, residual = 0, mod[3];
    string s;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case " << cs << ": ";

        cin >> s;

        residual = 0;
        memset(mod, 0, sizeof(mod));
        for (auto c : s) mod[(c - '0') % 3]++, residual += (c - '0');
        residual %= 3;

        int digits = mod[0] + mod[1] + mod[2];
        if (digits == 1) cout << "S\n";
        else if (residual == 0)
        {
            if (mod[0] % 2 == 1) cout << "S\n";
            else cout << "T\n";
        }
        else
        {
            if (mod[residual] == 0) cout << "T\n";
            else
            {
                if (digits == 2) cout << "T\n";
                else
                {
                    if (mod[0] % 2 == 1) cout << "T\n";
                    else cout << "S\n";
                }
            }
        }
    }

    return 0;
}
