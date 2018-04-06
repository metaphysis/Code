// Banglawash
// UVa ID: 12700
// Verdict: Accepted
// Submission Date: 2018-04-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char r;
    int cases, n;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        int b = 0, w = 0, t = 0, a = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> r;
            if (r == 'B') b++;
            if (r == 'W') w++;
            if (r == 'T') t++;
            if (r == 'A') a++;
        }
        
        cout << "Case " << c << ": ";
        if (a == n) cout << "ABANDONED\n";
        else if (b == w) cout << "DRAW " << b << ' ' << t << '\n';
        else if (b + a == n) cout << "BANGLAWASH\n";
        else if (w + a == n) cout << "WHITEWASH\n";
        else if (b > w) cout << "BANGLADESH " << b << " - " << w << '\n';
        else if (w > b) cout << "WWW " << w << " - " << b << '\n';
    }

    return 0;
}
