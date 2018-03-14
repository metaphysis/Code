// Sales
// UVa ID: 1260
// Verdict: Accepted
// Submission Date: 2017-11-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, sales[1010], n;
    int amount;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> sales[i];
            
            for (int j = 0; j < i; j++)
                if (sales[j] <= sales[i])
                    sum++;
        }
        cout << sum << '\n';
    }
    
    return 0;
}
