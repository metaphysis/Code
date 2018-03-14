// One-Two-Three
// UVa ID: 12289
// Verdict: Accepted
// Submission Date: 2017-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string word;
    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> word;
        if (word.length() == 5) cout << 3 << '\n';
        else
        {
            if (word[0] == 'o' && word[1] == 'n' ||
                word[1] == 'n' && word[2] == 'e' ||
                word[0] == 'o' && word[2] == 'e')
                cout << 1 << '\n';
            else
                cout << 2 << '\n';
                
        }
    }

    return 0;
}
