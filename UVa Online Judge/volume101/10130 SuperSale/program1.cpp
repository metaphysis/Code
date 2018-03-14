// SuperSale
// UVa ID: 10130
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

    int cases, prices[1024], weight[1024];
    int n, g, stand[128], value[32];
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> prices[i] >> weight[i];
            
        cin >> g;
        for (int i = 0; i < g; i++)
            cin >> stand[i];

        memset(value, 0, sizeof(value));

        for (int i = 1; i <= n; i++)
            for (int w = 30; w >= weight[i]; w--)
                value[w] = max(value[w - weight[i]] + prices[i], value[w]);
        
        int total = 0;
        for (int i = 0; i < g; i++)
            total += value[stand[i]];

        cout << total << '\n';
    }
    
    return 0;
}
