// Algorithm of Phil
// UVa ID: 12720
// Verdict: Accepted
// Submission Date: 2022-01-04
// UVa Run Time: 0.010s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T;
    long long MOD = 1000000007, Y;
    string A;
    cin >> T;
    for (int X = 1; X <= T; X++)
    {
        cout << "Case #" << X << ": ";
        cin >> A;
        Y = 0;
        int n = A.length();
        int x = (n - 1) / 2, y = n / 2;
        while (n > 0)
        {
            Y *= 2;
            if (n % 2)
            {
                Y += A[x] - '0';
                x--, y++;
                n--;
            }
            else
            {
                if (A[x] >= A[y])
                {
                    Y += A[x] - '0';
                    Y *= 2;
                    Y += A[y] - '0';
                    x--, y++;
                }
                else
                {
                    Y += A[y] - '0';
                    Y *= 2;
                    Y += A[x] - '0';
                    x--, y++;
                }
                n -= 2;
            }
            Y %= MOD;
        }
        cout << Y << '\n';
    }
    return 0;
}
