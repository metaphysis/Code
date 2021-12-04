// Amalgamated Artichokes
// UVa ID: 1709
// Verdict: Accepted
// Submission Date: 2021-12-02
// UVa Run Time: 1.840s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int p, a, b, c, d, n;

double inline getPrice(int k)
{
    return p * (sin(a * k + b) + cos(c * k + d) + 2);
}

int main(int argc, char *argv[])
{   
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> p >> a >> b >> c >> d >> n)
    {
        double maxDecline = 0, currentPrice, lowestPrice = getPrice(n);
        for (int i = n - 1; i >= 1; i--)
        {
            currentPrice = getPrice(i);
            maxDecline = max(maxDecline, currentPrice - lowestPrice);
            lowestPrice = min(lowestPrice, currentPrice);
        }
        cout << fixed << setprecision(8) << maxDecline << '\n';
    }

    return 0;
}
