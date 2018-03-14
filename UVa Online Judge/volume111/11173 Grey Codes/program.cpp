// Grey Codes
// UVa ID: 11173
// Verdict: Accepted
// Submission Date: 2018-01-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int getR(int b1, int b2, int n, int k)
{
    if (n < 0) return 0;

    int r = 0;
    if (k < (1 << n))
    {
        r += (b1 << n);
        b1 = 0, b2 = 1;
    }
    else
    {
        r += (b2 << n);
        k -= (1 << n);
        b1 = 1, b2 = 0;
    }

    return r + getR(b1, b2, n - 1, k);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, n, k;
    cin >> N;
    for (int c = 1; c <= N; c++)
    {
        cin >> n >> k;
        cout << getR(0, 1, n - 1, k) << '\n';
    }

    return 0;
}
