// Ocean Deep! - Make it Shallow!!
// UVa ID: 10176
// Verdict: Accepted
// Submission Date: 2018-03-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MOD = 131071;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string all, line;
    while (getline(cin, line))
    {
        all += line;
        if (line.back() == '#')
        {
            all.pop_back();

            int digit = 0;
            for (auto c : all)
            {
                if (digit > MOD) digit %= MOD;
                digit = digit * 2 + c - '0';
            }
            digit %= MOD;
            cout << (digit == 0 ? "YES" : "NO") << '\n';

            all.clear();
        }
    }

    return 0;
}
