// Zipf's Law
// UVa ID: 10126
// Verdict: Accepted
// Submission Date: 2018-03-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n)
    {
        if (cases++ > 0) cout << '\n';

        cin.ignore(1024, '\n');
        map<string, int> cnt;
        string line;
        while (getline(cin, line))
        {
            if (line == "EndOfText") break;
            string block;
            for (auto c : line)
            {
                if (isalpha(c))
                {
                    block += (char)(tolower(c));
                }
                else
                {
                    cnt[block]++;
                    block.clear();
                }
            }
            cnt[block]++;
        }

        bool printed = false;
        for (auto p : cnt)
        {
            if (p.second == n)
            {
                cout << p.first << '\n';
                printed = true;
            }
        }
        if (!printed) cout << "There is no such word.\n";
    }

    return 0;
}
