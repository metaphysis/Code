// Product of digits
// UVa ID: 993
// Verdict: Accepted
// Submission Date: 2016-01-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, n;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;

        if (n == 0 || n == 1)
        {
            cout << n << '\n';
            continue;
        }

        string digits;
        while (n > 1)
        {
            bool updated = false;
            for (int i = 9; i >= 2; i--)
                if (n % i == 0)
                {
                    digits.insert(digits.begin(), '0' + i);
                    n /= i;
                    updated = true;
                    break;
                }
            if (!updated) break;
        }
        
        if (n > 1) cout << "-1\n";
        else cout << digits << '\n';
    }
    
    return 0;
}
