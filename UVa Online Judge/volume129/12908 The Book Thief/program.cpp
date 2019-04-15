// The Book Thief
// UVa ID: 12908
// Verdict: Accepted
// Submission Date: 2019-04-14
// UVa Run Time: 0.110s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 15010;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int lows[MAXN] = {0}, highs[MAXN] = {0};
    int s = 1;
    for (int i = 2; i < MAXN; i++)
    {
        s += i;
        lows[i] = s - i;
        highs[i] = s - 1;
    }
    int n;
    while (cin >> n, n > 0)
    {
        int low = 1, high = MAXN, middle, r;
        while (true)
        {
            middle = (low + high) / 2;
            if (lows[middle] <= n && n <= highs[middle])
            {
                r = middle;
                break;
            }
            else if (lows[middle] > n)
            {
                high = middle - 1;
            }
            else if (highs[middle] < n)
            {
                low = middle + 1;
            }
        }
        int t = (1 + r) * r / 2;
        cout << (t - n) << ' ' << r << '\n';
    }

    return 0;
}
