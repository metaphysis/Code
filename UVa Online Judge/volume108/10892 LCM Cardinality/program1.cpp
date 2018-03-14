// LCM Cardinality
// UVa ID: 10892
// Verdict: Accepted
// Submission Date: 2017-03-18
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int main(int argc, char *argv[])
{
    ll n;
    while (cin >> n && n)
    {
        vector<ll> p;
        for (ll i = 1; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                p.push_back(i);
                if (n / i != i)
                    p.push_back(n / i);
            }
        }

        int answer = 0;
        for (ll i = 0; i < p.size(); i++)
        {
            for (ll j = i; j < p.size(); j++)
            {
                if ((p[i] * p[j] / gcd(p[i], p[j])) == n)
                    answer++;
            }
        }
        printf("%lld %d\n", n, answer);
    }

    return 0;
}
