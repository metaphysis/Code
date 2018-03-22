// Word Length and Frequency
// UVa ID: 10293
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
        all.clear();
        
        bool ended = false;
        if (line.front() != '#')
        {
            all += line;
            if (line.back() != '-') all += '\n';
            while (getline(cin, line))
            {
                if (line.front() == '#') 
                {
                    ended = true;
                    break;
                }
                all += line;
                if (line.back() != '-') all += '\n';
            }
        }
        else ended = true;

        if (ended)
        {
            map<int, int> cnt;
            int length = 0;
            for (auto c : all)
            {
                if (isalpha(c) || c == '\'' || c == '-')
                {
                    if (isalpha(c)) length++;
                }
                else
                {
                    if (length) cnt[length]++;
                    length = 0;
                }
            }
            if (length) cnt[length]++;

            for (auto p : cnt)
                cout << p.first << ' ' << p.second << '\n';
            cout << '\n';
        }
    }

    return 0;
}
