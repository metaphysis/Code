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
        int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
        for (int i = 0; i < S.size(); i++)
        {
            if (S[i] == '1' && T[i] == '0') c1++;
            if (S[i] == '0' && T[i] == '1') c2++;
            if (S[i] == '?' && T[i] == '0') c3++;
            if (S[i] == '?' && T[i] == '1') c4++;
        }
        cout << "Case " << cs << ": ";
        if (c2 + c4 < c1) cout << -1;
        else cout << c3 + c4 + max(c1, c2);
        cout << '\n';
    }

    return 0;
}
