// Multiple of 17
// UVa ID: 11879
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (cin >> line, line != "0")
    {
        int r = 0;
        for (int i = 0; i < line.length(); i++)
        {
            r = r * 10 + line[i] - '0';
            r %= 17;
        }
        if (r == 0) cout << 1 <<'\n';
        else cout << 0 << '\n';
    }

    return 0;
}
