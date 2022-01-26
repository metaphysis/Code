// Tobby and Seven
// UVa ID: 13103
// Verdict: Accepted
// Submission Date: 2022-01-27
// UVa Run Time: 0.020s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    long long n;
    while (cin >> n)
    {
        int k, p[24];
        cin >> k;
        for (int i = 0; i < k; i++) cin >> p[i];
        sort(p, p + k);
        queue<long long> q;
        q.push(n);
        long long best = 0;
        set<long long> cache;
        cache.insert(n);
        while (!q.empty())
        {
            n = q.front(); q.pop();
            for (int i = 0; i < k; i++)
                for (int j = i + 1; j < k; j++)
                {
                    long long nn = n;
                    if (n & (1LL << p[i])) nn |= 1LL << p[j];
                    else nn &= ~(1LL << p[j]);
                    if (n & (1LL << p[j])) nn |= 1LL << p[i];
                    else nn &= ~(1LL << p[i]);
                    if (nn <= best) continue;
                    if (nn % 7 == 0) best = max(best, nn);
                    if (cache.count(nn)) continue;
                    cache.insert(nn);
                    q.push(nn);
                }
        }
        cout << best << '\n';
    }
    return 0;
}
