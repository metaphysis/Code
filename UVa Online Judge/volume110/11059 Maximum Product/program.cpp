// Maximum Product
// UVa ID: 11059
// Verdict: Accepted
// Submission Date: 2017-11-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int n;
    
    while (cin >> n)
    {
        long long data, product, maxCurrent, minCurrent, nextMax, nextMin;
        cin >> data;
        product = maxCurrent = minCurrent = data;
        for (int i = 1; i < n; i++)
        {
            cin >> data;
            nextMax = data * maxCurrent, nextMin = data * minCurrent;
            maxCurrent = max(data, max(nextMax, nextMin));
            minCurrent = min(data, min(nextMax, nextMin));
            product = max(product, maxCurrent);
        }
        
        cout << "Case #" << ++cases << ": The maximum product is ";
        if (product < 0) cout << '0';
        else cout << product;
        cout << ".\n\n";
    }
    
    return 0;
}
