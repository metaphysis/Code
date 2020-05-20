// Emoogle Grid
// UVa ID: 11916
// Verdict: Accepted
// Submission Date: 2020-04-06
// UVa Run Time: 0.400s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll modPow(ll n, ll k, ll mod)
{
    if (k == 0) return 1LL % mod;
    ll r = modPow(n, k >> 1, mod);
    r = r * r % mod;
    if (k & 1) r = r * n % mod;
    return r;
}

ll discreteLog(ll x, ll n, ll p)
{
    map<ll, ll> hash;
    ll s = (ll)sqrt((double)p);
    while (s * s <= p) s++;
    ll baby = 1;
    for (ll r = 0; r < s; r++) hash[baby] = r, baby = baby * x % p;
    ll giant = 1;
    for (ll b = 0; b < s; b++) {
        ll xr = n * modPow(giant, p - 2, p) % p;
        if (hash.count(xr)) return b * s + hash[xr];
        giant = giant * baby % p;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    ll N, K, B, R, P = 100000007;
    
    int T;
    cin >> T;
    for (ll cs = 1; cs <= T; cs++)
    {
        cout << "Case " << cs << ": ";
        cin >> N >> K >> B >> R;

        map<int, set<int>> blocks;
        int bx[510], by[510], M = 1;
        for (int i = 0; i < B; i++)
        {
            cin >> bx[i] >> by[i];
            blocks[bx[i]].insert(by[i]);
            M = max(M, bx[i]);
        }

        int cnt = 0;
        for (int i = 0; i < B; i++)
            if (bx[i] != M && blocks[bx[i] + 1].count(by[i]) == 0)
                cnt++;

        cnt += N;
        for (int i = 0; i < B; i++)
            if (bx[i] == 1)
                cnt--;

        ll C = modPow(K, cnt, P) * modPow(K - 1, M * N - B - cnt, P) % P;
        if (C == R)
        {
            cout << M << '\n';
            continue;
        }

        cnt = 0;
        for (int i = 0; i < B; i++)
            if (bx[i] == M)
                cnt++;

        M++;
        C = C * modPow(K, cnt, P) % P;
        C = C * modPow(K - 1, N - cnt, P) % P;
        if (C == R)
        {
            cout << M << '\n';
            continue;
        }

        cout << discreteLog(modPow(K - 1, N, P), R * modPow(C, P - 2, P) % P, P) + M << '\n';
    }

    return 0;
}
