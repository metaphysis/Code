// Hajj-e-Akbar
// UVa ID: 12577
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

    int cases = 0;
    string word;
    
    while (cin >> word, word.front() != '*')
    {
        cout << "Case " << ++cases << ": ";
        if (word == "Hajj") cout << "Hajj-e-Akbar\n";
        else cout << "Hajj-e-Asghar\n";
    }

    return 0;
}
