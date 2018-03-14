// Boiled Eggs
// UVa ID: 11900
// Verdict: Accepted
// Submission Date: 2017-12-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int n, p, q;
    int eggs[40];
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> p >> q;
        cout << "Case " << c << ": ";
        
        for (int i = 0; i < n; i++) cin >> eggs[i];
        
        int boiled = 0, weight = 0;
        for (int i = 0; i < n; i++)
        {
            if (boiled >= p) break;
            if (weight + eggs[i] <= q) boiled++, weight += eggs[i];
        }
        cout << boiled << '\n';
    }

    return 0;
}
