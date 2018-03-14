// Splitting Numbers
// UVa ID: 11933
// Verdict: Accepted
// Submission Date: 2018-01-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        int k = 0, a = 0, b = 0;
        for (int i = 0; i <= 30; i++)
        {
            if (n & (1 << i))
            {
                k++;
                if (k % 2 == 1) a |= (1 << i);
                else b |= (1 << i);
            }
        }
        cout << a << ' ' << b << '\n';
    }

    return 0;
}
