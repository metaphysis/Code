// Character Recognition
// UVa ID: 12658
// Verdict: Accepted
// Submission Date: 2021-12-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    char g[8][64];
    cin >> n;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 4 * n; j++)
            cin >> g[i][j];
    for (int i = 0; i < n; i++)
    {
        if (g[3][4 * i] == '*') cout << 2;
        if (g[3][4 * i + 1] == '*') cout << 1;
        if (g[3][4 * i + 2] == '*') cout << 3;
    }
    cout << '\n';

    return 0;
}
