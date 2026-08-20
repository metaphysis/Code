// Exquisite Strings
// UVa ID: 12974
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 2.960s

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;
const long long MOD1 = 1000000007LL;
const long long MOD2 = 1000000009LL;
const long long BASE = 911382323LL;
const long long INV2 = 500000004LL; // (MOD+1)/2

struct PairHash {
    size_t operator()(const pair<long long, long long>& p) const {
        uint64_t x = (uint64_t)p.first * 1000003ULL ^ (uint64_t)p.second;
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return (size_t)(x ^ (x >> 31));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        string s;
        int k;
        cin >> s >> k;
        int n = (int)s.size();
        vector<long long> pow1(n + 1), pow2(n + 1);
        pow1[0] = pow2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pow1[i] = pow1[i - 1] * BASE % MOD1;
            pow2[i] = pow2[i - 1] * BASE % MOD2;
        }
        vector<long long> pref1(n + 1, 0), pref2(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int v = s[i - 1] - 'a' + 1;
            pref1[i] = (pref1[i - 1] * BASE + v) % MOD1;
            pref2[i] = (pref2[i - 1] * BASE + v) % MOD2;
        }
        auto getHash = [&](int l, int len) -> pair<long long, long long> {
            int r = l + len - 1;
            long long h1 = (pref1[r] - pref1[l - 1] * pow1[len] % MOD1 + MOD1) % MOD1;
            long long h2 = (pref2[r] - pref2[l - 1] * pow2[len] % MOD2 + MOD2) % MOD2;
            return {h1, h2};
        };
        unordered_map<pair<long long, long long>, long long, PairHash> groupSum;
        groupSum.reserve(n * 2);
        int maxStart = n - k + 1;
        for (int i = 1; i <= maxStart; ++i) {
            auto key = getHash(i, k);
            long long a = n - i - k + 2;
            groupSum[key] = (groupSum[key] + a) % MOD;
        }
        long long ans = 0;
        for (auto &kv : groupSum) {
            long long sum = kv.second;
            long long add = sum * ((sum - 1 + MOD) % MOD) % MOD * INV2 % MOD;
            ans = (ans + add) % MOD;
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
