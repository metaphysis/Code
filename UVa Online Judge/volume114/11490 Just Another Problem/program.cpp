// Just Another Problem
// UVa ID: 11490
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
    long long S;
    while (cin >> S, S)
    {
        long long MOD = 100000007;
        bool printed = 0;
        long long y = 1;
        while (true)
        {
            if (6 * y * y >= S) break;
            long long x = S - 6 * y * y;
            if (x <= 0) break;
            if (x % (7 * y) == 0)
            {
                x /= 7 * y;
                cout << "Possible Missing Soldiers = " << (2 * x % MOD) * x % MOD << '\n';
                printed = 1;
            }
            y++;
        }
        if (!printed) cout << "No Solution Possible\n";
        cout << '\n';
    }
    return 0;
}
