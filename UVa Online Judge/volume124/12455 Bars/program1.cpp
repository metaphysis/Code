// Bars
// UVa ID: 12455
// Verdict: Accepted
// Submission Date: 2017-11-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, bars[24], length[1024], n, p, total;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> p;
        
        total = 0;
        for (int i = 0; i < p; i++)
        {
            cin >> bars[i];
            total += bars[i];
        }
            
        memset(length, 0, sizeof(length));
        length[0] = 1;
        
        if (total >= n)
        {
            for (int i = 0; i < p; i++)
                for (int j = 1000; j >= 0; j--)
                    if (length[j] && (j + bars[i] <= 1000))
                        length[j + bars[i]] = 1;
        }
        
        if (length[n]) cout << "YES\n";
        else cout << "NO\n";
    }
    
    return 0;
}
