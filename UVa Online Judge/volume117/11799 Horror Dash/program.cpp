// Horror Dash
// UVa ID: 11799
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

    int cases;
    
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int n, cm = 0, c;
        
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> c;
            cm = max(cm, c);
        }
        cout << "Case " << cs << ": " << cm << '\n';
    }

    return 0;
}
