// Trainsorting
// UVa ID: 11456
// Verdict: Accepted
// Submission Date: 2017-11-06
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        vector<int> weight(n);
        for (int i = 0; i < n; i++) cin >> weight[i];
        
        if (n <= 2)
        {
            cout << n << '\n';
            continue;
        }
        
        vector<int> dp1(n, 1), dp2(n, 1);
        for (int i = n - 1; i >= 0; i--)
            for (int j = n - 1; j > i; j--)
                if (weight[i] > weight[j])
                    dp1[i] = max(dp1[i], dp1[j] + 1);
                else
                    dp2[i] = max(dp2[i], dp2[j] + 1);
            
        int longest = 0;
        for (int i = 0; i < n; i++)
            longest = max(longest, dp1[i] + dp2[i] - 1);
        cout << longest << '\n';
    }

    return 0;
}
