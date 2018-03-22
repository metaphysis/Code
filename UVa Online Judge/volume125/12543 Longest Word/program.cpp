// Longest Word
// UVa ID: 12543
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, all;
    while (getline(cin, line))
    {
        all += line;
        if (line.length() > 0 && line.back() != '-')
            all += '\n';
    }
    
    string word, longest;
    for (auto c : all)
    {
        if (isalpha(c) || c == '-')
        {
            word += c;
        }
        else
        {
            if (word == "E-N-D") break;
            if (word.length() > longest.length())
                longest = word;
            word.clear();
        }
    }

    for (auto c : longest)
        cout << (char)tolower(c);
    cout << '\n';

    return 0;
}
