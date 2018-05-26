// Dividing Up
// UVa ID: 711
// Verdict: Accepted
// Submission Date: 2018-05-13
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n[10], sum;
    int cnt = 0, arrived[60010] = {}, piles[1024];

    while (true)
    {
        sum = 0;
        for (int i = 1; i <= 6; i++)
        {
            cin >> n[i];
            sum += i * n[i];
        }
        
        if (sum == 0) break;
        cout << "Collection #" << ++cases << ":\n";
        
        if (sum % 2)
        {
            cout << "Can't be divided.\n\n";
            continue;
        }

        // Binary optimizition.
        sum >>= 1, cnt = 0;
        for (int i = 1; i <= 6; i++)
        {
            int j = 1, k = n[i];
            while (j <= k)
            {
                piles[cnt++] = j * i;
                k -= j;
                j <<= 1;
            }
            if (k) piles[cnt++] = i * k;
        }

        // DP.
        arrived[0] = 1;
        for (int i = 0; i < cnt; i++)
            for (int v = sum; v >= piles[i]; v--)
                if (arrived[v - piles[i]])
                    arrived[v] = 1;

        if (arrived[sum]) cout << "Can be divided.\n\n";
        else cout << "Can't be divided.\n\n";
    }

    return 0;
}
