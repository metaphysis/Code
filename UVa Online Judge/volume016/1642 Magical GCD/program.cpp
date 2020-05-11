// Magical GCD
// UVa ID: 1642
// Verdict: Accepted
// Submission Date: 2020-04-30
// UVa Run Time: 0.430s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;


int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        map<long long, int> gcd[2];
        int current = 0, next = (current + 1) % 2;
        long long r = 0, ai;
        for (int i = 0; i < n; i++)
        {
            cin >> ai;
            gcd[next].clear();
            for (auto p : gcd[current])
            {
                long long g = __gcd(p.first, ai);
                if (gcd[next].find(g) == gcd[next].end())
                {
                    gcd[next][g] = p.second;
                    r = max(r, g * (i - p.second + 1));
                }
            }
            if (gcd[next].find(ai) == gcd[next].end()) gcd[next][ai] = i;
            r = max(r, ai);
            current = (current + 1) % 2;
            next = (current + 1) % 2;
        }
        cout << r << '\n';
    }

    return 0;
}
