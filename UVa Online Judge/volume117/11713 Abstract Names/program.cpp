// Abstract Names
// UVa ID: 11713
// Verdict: Accepted
// Submission Date: 2018-03-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string word1, word2, vowels = "aeiou";

    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> word1 >> word2;
            if (word1.length() != word2.length())
                cout << "No\n";
            else
            {
                bool same = true;
                for (int j = 0; j < word1.length(); j++)
                    if (word1[j] != word2[j])
                    {
                        if (vowels.find(word1[j]) == vowels.npos ||
                            vowels.find(word2[j]) == vowels.npos)
                        {
                            same = false;
                            break;
                        }
                    }
                cout << (same ? "Yes" : "No") << '\n';
            }
        }
    }

    return 0;
}
