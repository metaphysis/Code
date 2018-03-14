// Soundex
// UVa ID: 10260
// Verdict: Accepted
// Submission Date: 2017-12-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int number[26] = {0, 1, 2, 3, 0, 1, 2, 0, 0, 2, 2, 4, 5, 5, 0, 1, 2, 6, 2, 3, 0, 1, 0, 2, 0, 2};
    
    string word;
    while (cin >> word)
    {
        int lastn = -1;
        for (auto c : word)
        {
            int n = number[c - 'A'];
            if (n && n != lastn) cout << n;
            lastn = n;
        }
        cout << '\n';
    }

    return 0;
}
