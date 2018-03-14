// Shopaholic
// UVa ID: 11369
// Verdict: Accepted
// Submission Date: 2017-10-15
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, dollars[20010];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> dollars[i];
            
        sort(dollars, dollars + n, greater<int>());
        
        int discount = 0;
        for (int i = 2; i < n; i += 3)
            discount += dollars[i];
        
        cout << discount << '\n';
    }

    return 0;
}
