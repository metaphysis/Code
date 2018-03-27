// Compound Words
// UVa ID: 10391
// Verdict: Accepted
// Submission Date: 2018-03-27
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string word;
    set<string> words;
    while (cin >> word)
    {
        words.insert(word);
    }

    for (auto w : words)
    {
        for (int i = 1; i < w.length() - 1; i++)
        {
            string f = w.substr(0, i), s = w.substr(i);
            if (words.find(f) != words.end() && words.find(s) != words.end())
            {
                cout << w << '\n';
                break;
            }
        }
    }

    return 0;
}
