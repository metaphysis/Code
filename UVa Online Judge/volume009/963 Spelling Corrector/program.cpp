// Spelling Corrector
// UVa ID: 963
// Verdict: Accepted
// Submission Date: 2018-11-08
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

set<string> words;

int dp[10][10];

int med(string &S, string &T)
{
    dp[0][0] = 0;
    int M = S.length(), N = T.length();
    for (int i = 1; i <= M; i++) dp[i][0] = i * 3;
    for (int j = 1; j <= N; j++) dp[0][j] = j * 3;
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
        {
            int deleted = dp[i - 1][j] + 3;
            int inserted = dp[i][j - 1] + 3;
            int replaced = dp[i - 1][j - 1];
            if (S[i - 1] != T[j - 1]) replaced = dp[i - 1][j - 1] + 5;
            dp[i][j] = min(min(deleted, inserted), replaced);
        }
    return dp[M][N];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m, cases = 0;
    string line, word, correct;
    while (cin >> n)
    {
        if (cases++) cout << '\n';
        words.clear();
        for (int i = 0; i < n; i++)
        {
            cin >> word;
            words.insert(word);
        }
        cin >> m;
        cin.ignore(256, '\n');
        while (getline(cin, line), line.length() > 0)
        {
            line += '\n';
            word.clear();
            for (int i = 0; i < line.length(); i++)
            {
                if (isblank(line[i]) || line[i] == '\n')
                {
                    if (word.length())
                    {
                        if (words.find(word) != words.end()) correct = word;
                        else
                        {
                            int r = 1024, next;
                            for (auto w : words)
                                if ((next = med(word, w)) < r)
                                {
                                    correct = w;
                                    r = next;
                                }
                        }
                        cout << correct;
                        word.clear();
                    }
                    cout << line[i];
                }
                else word += line[i];
            }
        }
    }

    return 0;
}
