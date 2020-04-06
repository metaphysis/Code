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

    int x, n, p;
    while (cin >> x >> n >> p)  cout << discreteLog(x, n, p) << '\n';
    return 0;
}
