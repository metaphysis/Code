// Closest Sums
// UVa ID: 10487
// Verdict: Accepted
// Submission Date: 2017-11-07
// UVa Run Time: 0.050s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, data[1010], sum[1000010], m, q;
    int cases = 0;
    
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ":\n";
        
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> data[i];
            for (int j = 0; j < i; j++)
                if (data[j] != data[i])
                    sum[cnt++] = data[j] + data[i];
        }
        
        sort(sum, sum + cnt);
        cnt = unique(sum, sum + cnt) - sum;

        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> q;

            int k = upper_bound(sum, sum + cnt, q) - sum;
            if (k == cnt) k = cnt - 1;
            int diff = abs(q - sum[k]);
            int answer = sum[k];
            for (int j = k - 1; j >= 0; j--)
                if (abs(q - sum[j]) < diff)
                {
                    diff = abs(q - sum[j]);
                    answer = sum[j];
                }
                else break;
                
            cout << "Closest sum to " << q << " is " << answer << ".\n";         
        }
    }
    
    return 0;
}
