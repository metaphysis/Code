// Prime Time
// UVa ID: 10200
// Verdict: Accepted
// Submission Date: 2018-04-15
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool isPrime(int a)
{
    if (a <= 1) return false;
    if (a == 2) return true;
    if (!(a & 1)) return false;
    
    int factor = (int)sqrt(a);
    for (int i = 3; i <= factor; i += 2)
        if (a % i == 0)
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int s[10010] = {0, 1};
    for (int i = 2; i <= 10001; i++)
    {
        s[i] = s[i - 1];
        if (isPrime((i - 1) * (i - 1) + (i - 1) + 41))
            s[i] += 1;
    }
    
    int a, b;
    while (cin >> a >> b)
    {
        a++, b++;
        cout << fixed << setprecision(2) << ((s[b] - s[a - 1]) * 100.0 / (b - a + 1) + 1e-6) << '\n';
    }

    return 0;
}
