// Wordfish
// UVa ID: 1209
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, username1, username2, password;
    while (getline(cin, line))
    {
        vector<string> candidate;
        candidate.push_back(line);

        username1 = line, username2 = line;
        while (candidate.size() < 21)
        {
            bool updated = false;
            if (prev_permutation(username1.begin(), username1.end()))
            {
                candidate.push_back(username1);
                updated = true;
            }
            if (next_permutation(username2.begin(), username2.end()))
            {
                candidate.push_back(username2);
                updated = true;
            }
            if (!updated) break;
        }
        
        sort(candidate.begin(), candidate.end());

        int maxminDist = -1;
        for (auto s : candidate)
        {
            int minDist = 1024;
            for (int i = 1; i < s.length(); i++)
                minDist = min(minDist, abs(s[i] - s[i - 1]));
            if (minDist > maxminDist)
            {
                maxminDist = minDist;
                password = s;
            }
        }
        cout << password << maxminDist << '\n';
    }

    return 0;
}
