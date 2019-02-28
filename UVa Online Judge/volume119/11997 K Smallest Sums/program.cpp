// K Smallest Sums
// UVa ID: 11997
// Verdict: Accepted
// Submission Date: 2019-02-28
// UVa Run Time: 0.530s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int k;
    int sum1[760], sum2[760], s, *t;
    while (cin >> k)
    {
        sum1[0] = 0;
        for (int i = 0; i < k; i++)
        {
            memset(sum2, 0x7f, sizeof(sum2));
            for (int j = 0, n; j < k; j++)
            {
                cin >> n;
                for (int x = 0; x < (i ? k : 1); x++)
                {
                    s = sum1[x] + n;
                    if (s >= sum2[k - 1]) break;
                    int y = k - 1;
                    while (y >= 0 && s < sum2[y]) sum2[y + 1] = sum2[y], y--;
                    sum2[y + 1] = s;  
                }
            }
            swap(sum1, sum2);
        }
        for (int i = 0; i < k; i++)
        {
            if (i) cout << ' ';
            cout << sum1[i];
        }
        cout << '\n';
    }

    return 0;
}
