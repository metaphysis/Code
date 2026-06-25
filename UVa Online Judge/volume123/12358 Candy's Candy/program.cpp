// Candy's Candy
// UVa ID: 12358
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcdll(ll a, ll b) {
    while (b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// 统计满足 1 <= v <= limit 且 v % mod == remainder 的 v 的个数
ll countV(ll limit, ll remainder, ll mod) {
    if (limit <= 0) return 0;
    if (remainder == 0) return limit / mod;
    if (limit < remainder) return 0;
    return (limit - remainder) / mod + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int flavorCnt;
    while (cin >> flavorCnt && flavorCnt != 0) {
        vector<ll> candy(flavorCnt);
        ll totalGcd = 0;

        for (int i = 0; i < flavorCnt; ++i) {
            cin >> candy[i];
            totalGcd = gcdll(totalGcd, candy[i]);
        }

        vector<ll> a(flavorCnt);
        ll minA = LLONG_MAX;

        for (int i = 0; i < flavorCnt; ++i) {
            a[i] = candy[i] / totalGcd;
            if (a[i] < minA) minA = a[i];
        }

        // 求 F 的所有因子
        vector<ll> factorsF;
        for (ll i = 1; i * i <= flavorCnt; ++i) {
            if (flavorCnt % i == 0) {
                factorsF.push_back(i);
                if (i * i != flavorCnt) factorsF.push_back(flavorCnt / i);
            }
        }

        // remForMod[M] = 所有 a[i] 模 M 的公共余数，若不完全相同则为 -1
        vector<ll> remForMod(flavorCnt + 1, -2);

        for (ll modVal : factorsF) {
            ll r = a[0] % modVal;
            bool ok = true;

            for (int i = 1; i < flavorCnt; ++i) {
                if (a[i] % modVal != r) {
                    ok = false;
                    break;
                }
            }

            if (ok) remForMod[modVal] = r;
            else remForMod[modVal] = -1;
        }

        // 求 G = gcd(C_i) 的所有因子，这里 h 是 G 的因子
        vector<ll> factorsG;
        ll G = totalGcd;

        for (ll i = 1; i * i <= G; ++i) {
            if (G % i == 0) {
                factorsG.push_back(i);
                if (i * i != G) factorsG.push_back(G / i);
            }
        }

        ll ans = 0;

        for (ll factorH : factorsG) {
            ll gHf = gcdll(factorH, flavorCnt);
            ll modVal = flavorCnt / gHf;

            // 所有 a[i] 模 modVal 必须相同
            if (remForMod[modVal] == -1) continue;

            // q_i = a[i] * factorH 模 F 的公共余数
            ll remainder = (a[0] * factorH) % flavorCnt;

            // minQ = min_i q_i
            ll minQ = minA * factorH;

            // 需要 v <= minQ - F
            ll limit = minQ - flavorCnt;

            ans += countV(limit, remainder, flavorCnt);
        }

        cout << ans << '\n';
    }

    return 0;
}
