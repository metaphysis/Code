// Summing Digits
// UVa ID: 11332
// Verdict: Accepted
// Submission Date: 2017-12-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    
    while (cin >> n, n > 0)
    {
        while (n >= 10)
        {
            int nn = 0;
            while (n > 0)
            {
                nn += n % 10;
                n /= 10;
            }
            n = nn;
        }
        cout << n << '\n';
    }

    return 0;
}
