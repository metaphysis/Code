// Lap
// UVa ID: 12791
// Verdict: Accepted
// Submission Date: 2022-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    long long X, Y;
    while (cin >> X >> Y)
    {
        long long low = 1, high = 100000000, middle, r;
        while (low <= high)
        {
            middle = (low + high) >> 1;
            if (middle * (Y - X) >= X * Y)
            {
                r = middle;
                high = middle - 1;
            }
            else low = middle + 1;
        }
        cout << (r / X) + (r % X != 0) << '\n';
    }
    return 0;
}
