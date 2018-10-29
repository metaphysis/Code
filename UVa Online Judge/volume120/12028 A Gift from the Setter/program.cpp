// A Gift from the Setter
// UVa ID: 12028
// Verdict: Accepted
// Submission Date: 2018-10-29
// UVa Run Time: 0.270s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, n;
    long long K, C, a[100010];

    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> K >> C >> n >> a[0];
        for (int i = 1; i < n; i++)
            a[i] = (K * a[i - 1] + C) % 1000007LL;
        sort(a, a + n);
        long long S = 0, R = 0;
        for (int i = 1; i <= n; i++)
        {
            S += a[i - 1];
            R += i * a[i - 1] - S;
        }
        cout << "Case " << cs << ": " << R << '\n';
    }

    return 0;
}
