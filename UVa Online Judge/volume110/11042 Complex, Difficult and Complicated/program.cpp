// Complex, Difficult and Complicated
// UVa ID: 11042
// Verdict: Accepted
// Submission Date: 2018-03-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, a, b;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> a >> b;
        if (a == 0 || b == 0 || abs(a) == abs(b))
        {
            if (b == 0) cout << "1\n";
            else if (a == 0) cout << "2\n";
            else cout << "4\n";
        }
        else
        {
            cout << "TOO COMPLICATED\n";
        }
    }

    return 0;
}
