// Bits Equalizer
// UVa ID: 12545
// Verdict: Accepted
// Submission Date: 2021-12-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{    
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    string S, T;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> S >> T;
        int one_vs_zero = 0, zero_vs_one = 0;
        string D;
        for (int i = 0; i < S.size(); i++)
        {
            if (S[i] == T[i]) continue;
            if (S[i] == '?') D += T[i];
            else
            {
                if (S[i] == '1') one_vs_zero++;
                else zero_vs_one++;
            }
        }
        int moves = 0;
        moves += min(one_vs_zero, zero_vs_one);
        if (one_vs_zero >= zero_vs_one) { one_vs_zero -= zero_vs_one; zero_vs_one = 0; }
        else { zero_vs_one -= one_vs_zero; one_vs_zero = 0; }
        moves += zero_vs_one;
        for (int i = 0; i < D.size(); i++)
        {
            moves++;
            if (D[i] == '1' && one_vs_zero)
            {
                one_vs_zero--;
                moves++;
            }
        }
        if (one_vs_zero) moves = -1;
        cout << "Case " << cs << ": " << moves << '\n';
    }

    return 0;
}
