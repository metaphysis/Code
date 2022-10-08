// Hyper Box
// UVa ID: 12281
// Verdict: Accepted
// Submission Date: 2022-10-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    const long long MAXF = 2000000000LL;
    long long f[64] = {0, 1, 2};
    int cnt = 3;
    do f[cnt] = f[cnt - 1] + f[cnt - 2]; while (f[cnt++] <= MAXF);

    int T, N;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cout << "Case " << cs << ": ";
        cin >> N;
        long long r = 1;
        for (int i = 1, n; i <= N; i++)
        {
            cin >> n;
            int k = 0, c = cnt - 1;
            while (n)
            {
                if (n >= f[c]) n -= f[c], k++;
                else c--;
            }
            r *= k;
        }
        cout << r << '\n';
    }

    return 0;
}
