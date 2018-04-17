// Beautiful Flag
// UVa ID: 12611
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

    int cases, R;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> R;
        cout << "Case " << c << ":\n";
        cout << '-' << R * 9 / 4 << ' ' << R * 3 / 2 << '\n';
        cout << R * 11 / 4 << ' ' << R * 3 / 2 << '\n';
        cout << R * 11 / 4 << ' ' << '-' << R * 3 / 2 << '\n';
        cout << '-' << R * 9 / 4 << ' ' << '-' << R * 3 / 2 << '\n';
    }

    return 0;
}
