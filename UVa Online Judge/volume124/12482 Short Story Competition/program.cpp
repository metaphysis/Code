// Short Story Competition
// UVa ID: 12482
// Verdict: Accepted
// Submission Date: 2018-01-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, L, C;
    while (cin >> N >> L >> C)
    {
        list<string> words;
        string word;
        for (int i = 1; i <= N; i++)
        {
            cin >> word;
            words.push_back(word);
        }

        int length = 0, lines = 0;        
        while (words.size())
        {
            if (length == 0)
            {
                length += words.front().length();
                words.pop_front();
            }
            else 
            {
                if (length + words.front().length() + 1 <= C)
                {
                    length += (1 + words.front().length());
                    words.pop_front();
                }
                else
                {
                    lines++;
                    length = 0;
                }
            }
        }
        lines++;

        cout << (lines / L + (lines % L != 0)) << '\n';
    }

    return 0;
}
