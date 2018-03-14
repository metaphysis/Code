// Blocks
// UVa ID: 10365
// Verdict: Accepted
// Submission Date: 2017-11-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, cache[1010] = {0};
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;

        if (cache[n])
        {
            cout << cache[n] << '\n';
            continue;
        }
        
        int least = 0x3fffffff;
        for (int x = 1; x <= n; x++)
        {
            if ((n % x) != 0) continue;
            int upy = n / x;
            for (int y = 1; y <= upy; y++)
            {
                if ((n % (x * y)) != 0) continue;
                int z = n / x / y;
                least = min(least, 2 * (x * y + y * z + x * z));
            }
        }
        
        cout << least << '\n';
        
        cache[n] = least;
    }
    
    return 0;
}
