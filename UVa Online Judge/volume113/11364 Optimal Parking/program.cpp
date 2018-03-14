// Optimal Parking
// UVa ID: 11364
// Verdict: Accepted
// Submission Date: 2017-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, stores[30], n;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> stores[i];
        
        int maxp = *max_element(stores, stores + n);
        int minp = *min_element(stores, stores + n);
        
        cout << 2 * (maxp - minp) << '\n';
    }

    return 0;
}
