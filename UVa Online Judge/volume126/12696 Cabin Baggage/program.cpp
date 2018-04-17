// Cabin Baggage
// UVa ID: 12696
// Verdict: Accepted
// Submission Date: 2018-04-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, value[4];
    string text;

    cin >> cases;
    int valid = 0;
    for (int c = 1; c <= cases; c++)
    {
        for (int i = 0; i < 4; i++)
        {
            cin >> text;
            value[i] = 0;
            for (auto letter : text)
                if (isdigit(letter))
                    value[i] = value[i] * 10 + letter - '0';
        }

        if (value[3] > 700 || ((value[0] > 5600 || value[1] > 4500 || value[2] > 2500) && value[0] + value[1] + value[2] > 12500))
            cout << 0 << '\n';
        else
        {
            cout << 1 << '\n';
            valid++;
        }
    }
    cout << valid << '\n';

    return 0;
}
