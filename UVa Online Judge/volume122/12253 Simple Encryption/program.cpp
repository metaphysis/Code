// Simple Encryption
// UVa ID: 12253
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.120s

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using i128 = __int128_t;

const ull MOD12 = 1000000000000ULL;

ull modPow(ull base, ull exp, ull mod) {
    ull result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (ull)((i128)result * base % mod);
        base = (ull)((i128)base * base % mod);
        exp >>= 1;
    }
    return result;
}

ull findPrivateKey(ull publicKey) {
    vector<ull> candidates;
    for (ull x = 0; x < 100; ++x)
        if (modPow(publicKey, x + MOD12, 100) == x)
            candidates.push_back(x);
    ull currentMod = 100;
    while (currentMod < MOD12) {
        ull nextMod = currentMod * 10;
        vector<ull> nextCandidates;
        for (ull x : candidates)
            for (int digit = 0; digit <= 9; ++digit) {
                ull y = x + (ull)digit * currentMod;
                if (modPow(publicKey, y + MOD12, nextMod) == y)
                    nextCandidates.push_back(y);
            }
        candidates.swap(nextCandidates);
        currentMod = nextMod;
    }
    for (ull x : candidates)
        if (x >= 100000000000ULL && x < MOD12)
            return x;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ull publicKey;
    int caseNumber = 1;
    while (cin >> publicKey && publicKey != 0) {
        ull privateKey = findPrivateKey(publicKey);
        cout << "Case " << caseNumber
             << ": Public Key = " << publicKey
             << " Private Key = " << privateKey
             << '\n';
        ++caseNumber;
    }
    return 0;
}
