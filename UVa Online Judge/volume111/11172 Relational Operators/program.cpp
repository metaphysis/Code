// Relational Operators
// UVa ID: 11172
// Verdict: Accepted
// Submission Date: 2017-08-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    
    while (cin >> cases)
    {
        long long a, b;
        for (int c = 1; c <= cases; c++)
        {
            cin >> a >> b;
            
            if (a > b) cout << '>';
            else if (a < b) cout << '<';
            else cout << '=';
            
            cout << '\n';
        }
    }
    
    return 0;
}
