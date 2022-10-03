// Raiders of the Lost Sign
// UVa ID: 12805
// Verdict: Accepted
// Submission Date: 2022-10-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int ps[1010] = {0}, cnt = 0;
    for (int i = 2; i < 1010; i++)
    {
        if (!ps[i]) ps[cnt++] = i;
        for (int j = 0; j < cnt && i * ps[j] < 1010; j++)
        {
            ps[i * ps[j]] = 1;
            if (i % ps[j] == 0) break;
        }
    }
    int T, d;
    cin >> T;
    while (T--)
    {
        cin >> d;
        int sign = 1;
        for (int i = 0; i < cnt; i++)
        {
            while (d % ps[i] == 0)
            {
                if (ps[i] % 4 == 1) sign = !sign;
                d /= ps[i];
            }
        }
        if (d > 1)
            if (d % 4 == 1)
                sign = !sign;
        cout << (sign ? '+' : '-') << '\n';
    }
    return 0;
}
