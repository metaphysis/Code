// Extend to Palindromes
// UVa ID: 11475
// Verdict: Accepted
// Submission Date: 2017-03-29
// UVa Run Time: 2.070s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool isPalindrome(string &line)
{
    for (int i = 0, j = line.length() - 1; i < j; i++, j--)
        if (line[i] != line[j])
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        if (isPalindrome(line))
        {
            cout << line << '\n';
            continue;
        }

        string next;
        for (int i = 0; i < line.length() - 1; i++)
        {
            next += line[i];
            next += '|';
        }
        next += line.back();

        bool found = false;
        for (int i = next.length() / 2; i < next.length() - 1; i++)
        {
            bool flag = true;
            for (int j = next.length() - 1; j > i; j--)
                if (next[j] != next[2 * i - j])
                {
                    flag = false;
                    break;
                }

            if (flag)
            {
                cout << line;
                for (int k = 2 * i - next.length(); k >= 0; k--)
                    if (next[k] != '|')
                        cout << next[k];
                cout << '\n';
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << line;
            for (int i = line.length() - 2; i >= 0; i--)
                cout << line[i];
            cout << '\n';
        }
    }
    
    return 0;
}
