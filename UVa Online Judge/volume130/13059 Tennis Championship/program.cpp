// Tennis Championship
// UVa ID: 13059
// Verdict: Accepted
// Submission Date: 2022-01-26
// UVa Run Time: 0.060s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    long long n;
    while (cin >> n)
    {
        long long cnt = 0;
        while (n > 1)
        {
            cnt += n / 2;
            if (n % 2)
            {
                n /= 2;
                n++;
            }
            else n /= 2;
        }
        cout << cnt << '\n';
    }
    return 0;
}
