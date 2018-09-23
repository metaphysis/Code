// Happy Birthday
// UVa ID: 12002
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        vector<int> weight(n);
        for (int i = 0; i < n; i++)
            cin >> weight[i];

        if (n <= 2)
        {
            cout << n << '\n';
            continue;
        }

        vector<int> dp1(n, 1), dp2(n, 1);
        for (int i = n - 1; i >= 0; i--)
            for (int j = n - 1; j > i; j--)
            {
                if (weight[i] >= weight[j])
                    dp1[i] = max(dp1[i], dp1[j] + 1);
                if (weight[i] <= weight[j])
                    dp2[i] = max(dp2[i], dp2[j] + 1);
            }
            
        int longest = 0;
        for (int i = 0; i < n; i++)
            longest = max(longest, dp1[i] + dp2[i] - 1);
        cout << longest << '\n';
    }

    return 0;
}
