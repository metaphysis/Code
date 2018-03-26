// Automatic Correction of Misspellings
// UVa ID: 11048
// Verdict: Accepted
// Submission Date: 2018-03-26
// UVa Run Time: 0.380s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int lcs(string &s, string &t)
{
    int dp[s.length() + 1][t.length() + 1] = {};
    for (int i = 1; i <= s.length(); i++)
        for (int j = 1; j <= t.length(); j++)
            if (s[i - 1] == t[j - 1])
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            else
                dp[i][j] = max(dp[i][j], max(dp[i - 1][j], dp[i][j - 1]));
    return dp[s.length()][t.length()];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, q;
    string word;

    while (cin >> n)
    {
        vector<string> words;
        set<string> dict;
    
        for (int i = 0; i < n; i++)
        {
            cin >> word;
            words.push_back(word);
            dict.insert(word);
        }
        cin >> q;
        for (int i = 0; i < q; i++)
        {
            cin >> word;
            if (dict.find(word) != dict.end())
            {
                cout << word << " is correct\n";
                continue;
            }
                
            bool printed = false;
            for (auto w : words)
            {
                int length1 = w.length(), length2 = word.length();
                if (length1 == length2)
                {
                    int diff = 0, exchange = 0;
                    for (int j = 0; j < length1; j++)
                    {
                        if (w[j] != word[j])
                        {
                            if (j < length1 - 1 && w[j] == word[j + 1] && w[j + 1] == word[j])
                            {
                                exchange++;
                                j++;
                            }
                            else diff++;
                            if (diff + exchange > 1) break;
                        }
                        
                    }
                    if (diff + exchange == 1)
                    {
                        cout << word << " is a misspelling of " << w << '\n';
                        printed = true;
                        break;
                    }
                }
                else if (abs(length1 - length2) == 1)
                {
                    if (lcs(w, word) == min(length1, length2))
                    {
                        cout << word << " is a misspelling of " << w << '\n';
                        printed = true;
                        break;
                    }
                }
            }
            if (!printed) cout << word << " is unknown\n";
        }
    }

    return 0;
}
