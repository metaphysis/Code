// Lucky Numbers
// UVa ID: 11970
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ":";
        cin >> n;
        int up = sqrt(n) + 1;
        for (int i = up; i >= 1; i--)
        {
            int x = n - i * i;
            if (x > 0 && x % i == 0)
                cout << ' ' << x;
        }
        cout << '\n';
    }

    return 0;
}
