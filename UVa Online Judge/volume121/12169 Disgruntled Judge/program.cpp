// Disgruntled Judge
// UVa ID: 12169
// Verdict: Accepted
// Submission Date: 2022-01-26
// UVa Run Time: 0.320s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, odd[120], n[240];
    cin >> T;
    int working = 1;
    for (int i = 0; i < T; i++) cin >> odd[i];
    for (int a = 0; a <= 10000 && working; a++)
        for (int b = 0; b <= 10000; b++)
        {
            int valid = 1;
            n[0] = odd[0];
            for (int i = 1; i < 2 * T && valid; i++)
            {
                n[i] = (a * n[i - 1] + b) % 10001;
                if (i % 2 == 0 && n[i] != odd[i / 2])
                    valid = 0;
            }
            if (valid)
            {
                for (int i = 1; i < 2 * T; i += 2)
                    cout << n[i] << '\n';
                working = 0;
                break;
            }
        }
    return 0;
}
