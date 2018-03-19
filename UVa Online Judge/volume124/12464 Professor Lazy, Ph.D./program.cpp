// Professor Lazy, Ph.D.
// UVa ID: 12464
// Verdict: Accepted
// Submission Date: 2018-03-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long a, b, n;
    while (cin >> a >> b >> n, a > 0)
    {
        n %= 5;
        if(n == 0) cout << a << '\n';
        if(n == 1) cout << b << '\n';
        if(n == 2) cout << (1 + b) / a << '\n';
        if(n == 3) cout << (1 + a + b) / a / b << '\n';
        if(n == 4) cout << (1 + a) / b << '\n';
    }

    return 0;
}
