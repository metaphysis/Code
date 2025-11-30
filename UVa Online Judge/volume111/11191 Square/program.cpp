// Square
// UVa ID: 11191
// Verdict: Accepted
// Submission Date: 2025-11-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

int getSignature(long long n) {
    int signature = 0;
    long long nn = abs(n);
    for (int i = 0; i < 10; i++) {
        int cnt = 0;
        while (nn % primes[i] == 0) { cnt++; nn /= primes[i]; }
        if (cnt % 2) signature |= (1 << i);
    }
    signature <<= 1;
    if (n < 0) signature |= 1;
    return signature;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> ns(n);
        for (int i = 0; i < n; i++) cin >> ns[i];
        map<int, long long> signatureCount;
        int zeroCount = 0;
        for (int i = 0; i < n; i++) {
            if (ns[i] == 0) zeroCount++;
            else {
                int sig = getSignature(ns[i]);
                signatureCount[sig]++;
            }
        }
        long long squarePairs = 0;
        for (auto& entry : signatureCount) squarePairs += entry.second * (entry.second - 1) / 2;
        squarePairs += 1LL * zeroCount * (zeroCount - 1) / 2;
        squarePairs += 1LL * zeroCount * (n - zeroCount);
        long long squareTriples = 0;
        long long nonZeroCount = n - zeroCount;
        squareTriples += 1LL * zeroCount * (zeroCount - 1) * (zeroCount - 2) / 6;
        squareTriples += 1LL * zeroCount * (zeroCount - 1) * nonZeroCount / 2;
        squareTriples += 1LL * zeroCount * nonZeroCount * (nonZeroCount - 1) / 2;
        for (auto& entry1 : signatureCount) {
            int sig1 = entry1.first;
            long long count1 = entry1.second;
            for (auto& entry2 : signatureCount) {
                if (entry2.first < sig1) continue;
                int sig2 = entry2.first;
                long long count2 = entry2.second;
                int sig3 = sig1 ^ sig2;
                if (sig3 < sig2) continue;
                if (!signatureCount.count(sig3)) continue;
                long long count3 = signatureCount[sig3];
                if (sig1 == sig2 && sig2 == sig3) squareTriples += count1 * (count1 - 1) * (count1 - 2) / 6;
                else if (sig2 == sig3) squareTriples += count1 * count2 * (count2 - 1) / 2;
                else squareTriples += count1 * count2 * count3;
            }
        }
        cout << squarePairs << " " << squareTriples << "\n";
    }
    return 0;
}
