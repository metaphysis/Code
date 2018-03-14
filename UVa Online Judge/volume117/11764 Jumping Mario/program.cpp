// Jumping Mario
// UVa ID: 11764
// Verdict: Accepted
// Submission Date: 2017-12-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, h1, h2;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        int high = 0, low = 0;

        cin >> h1;
        for (int i = 1; i < n; i++)
        {
            cin >> h2;
            if (h2 > h1) high++;
            if (h2 < h1) low++;
            h1 = h2;
        }
        
        cout << "Case " << c << ": " << high << ' ' << low << '\n';
    }

    return 0;
}
