// Crazy Tea Party
// UVa ID: 1315
// Verdict: Accepted
// Submission Date: 2022-10-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int r[32768] = {0, 0, 0};
    for (int i = 3, j = 1; i <= 32767; i += 2, j++)
    {
        r[i] = r[i - 1] + j;
        r[i + 1] = r[i] + j;
    }
    int T, n;
    cin >> T;
    while (T--)
    {
        cin >> n;
        cout << r[n] << '\n';
    }

    return 0;
}
