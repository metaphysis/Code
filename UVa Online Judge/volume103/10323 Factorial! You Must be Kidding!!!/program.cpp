// Factorial! You Must be Kidding!!!
// UVa ID: 10323
// Verdict: Accepted
// Submission Date: 2018-03-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long n = 1, x = 2, low, up, factorial[20];
    
    while (n * x <= 10000) n *= x, x++;
    low = x - 1;

    while (n * x <= 6227020800) n *= x, factorial[x] = n, x++;
    up = x;
    
    int a;
    while (cin >> a)
    {
        if (a >= 0)
        {
            if (a <= low) cout << "Underflow!\n";
            else if (a >= up) cout << "Overflow!\n";
            else cout << factorial[a] << '\n';
        }
        else
        {
            if (abs(a) % 2 == 0) cout << "Underflow!\n";
            else cout << "Overflow!\n";
        }
    }

    return 0;
}
