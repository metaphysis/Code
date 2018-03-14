// Andy's Second Dictionary
// UVa ID: 11062
// Verdict: Accepted
// Submission Date: 2018-01-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    bool hyphenated = false;
    set<string> words;
    string word;
    char c;
    
    while (cin.get(c))
    {
        if (isalpha(c))
        {
            hyphenated = false;
            word += tolower(c);
        }
        else
        {
            if (c == '-')
            {
                word += '-';
                hyphenated = true;
            }
            else if (c == '\n' && hyphenated)
            {
                word.pop_back();
            }
            else
            {
                hyphenated = false;
                if (word.length())
                {
                    words.insert(word);
                    word.clear();
                }
            }
        }
    }
    
    for (auto w : words) cout << w << '\n';

    return 0;
}
