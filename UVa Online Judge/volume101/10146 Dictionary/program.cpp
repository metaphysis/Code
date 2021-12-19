// Dictionary
// UVa ID: 10146
// Verdict: Accepted
// Submission Date: 2021-12-19
// UVa Run Time: 0.040s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    cin >> n;
    cin.ignore(256, '\n');
    string empty;
    getline(cin, empty);
    for (int cs = 0; cs < n; cs++)
    {
        if (cs) cout << '\n';
        string lastWord, word;
        int spaces = 0;
        while (getline(cin, word))
        {
            if (!word.length()) break;
            int same = 0;
            int length = min(lastWord.length(), word.length());
            for (int i = 0; i < length; i++)
            {
                if (lastWord[i] != word[i]) break;
                same++;
            }
            spaces = min(spaces + 1, same);
            for (int i = 0; i < spaces; i++) cout << ' ';
            cout << word << '\n';
            lastWord = word;
        }
    }

    return 0;
}
