// Repeated Substitution with Sed
// UVa ID: 1251
// Verdict: Accepted
// Submission Date: 2018-07-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct package
{
    string text;
    int steps;
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string alpha[16], beta[16], gamma, delta;

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> alpha[i] >> beta[i];
        cin >> gamma >> delta;
        
        int best = -1;
        queue<package> q;
        q.push((package){gamma, 0});
        set<string> visited;
        visited.insert(gamma);

        while (!q.empty())
        {
            package pack = q.front(); q.pop();
            if (pack.text == delta)
            {
                best = pack.steps;
                break;
            }
            for (int i = 0; i < n; i++)
            {
                size_t pos = pack.text.find(alpha[i]);
                if (pos != string::npos)
                {
                    string next(pack.text);
                    pos = 0;
                    while ((pos = next.find(alpha[i], pos)) != string::npos)
                    {
                        next.replace(pos, alpha[i].length(), beta[i]);
                        pos += beta[i].length();
                        if (next.length() > delta.length()) break;
                    }
                    if (next.length() > delta.length()) continue;
                    if (visited.find(next) != visited.end()) continue;
                    visited.insert(next);
                    q.push((package){next, pack.steps + 1});
                }
            }
        }
        cout << best << '\n';
    }

    return 0;
}
