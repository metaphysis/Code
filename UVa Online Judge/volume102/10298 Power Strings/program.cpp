// Power Strings
// UVa ID: 10298
// Verdict: Accepted
// Submission Date: 2018-03-28
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        if (line == ".") break;
        bool printed = false;
        for (int i = 1; i < line.length(); i++)
        {
            if (line.length() % i == 0)
            {
                bool same = true;
                for (int j = i; j < line.length(); j += i)
                {
                    for (int k = 0; k < i; k++)
                        if (line[k] != line[k + j])
                        {
                            same = false;
                            break;
                        }
                    if (!same) break;
                }
                if (same)
                {
                    printed = true;
                    cout << line.length() / i << '\n';
                    break;
                }
            }
        }
        if (!printed) cout << 1 << '\n';
    }

    return 0;
}
