// Jimmy's Balls
// UVa ID: 11480
// Verdict: Accepted
// Submission Date: 2018-06-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n;
    while (cin >> n, n > 0)
    {
        long long cnt = 0;
        for (int i = 1; i <= n / 3; i++)
        {
            int r = n - i;
            int low = i + 1, high = (r / 2) + (r % 2);
            if (low >= high) break;
            cnt += (high - low);
        }
        cout << "Case " << ++cases << ": " << cnt << '\n';
    }

    return 0;
}
