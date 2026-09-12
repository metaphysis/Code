// Bit Stream
// UVa ID: 11179
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.160s

#include <bits/stdc++.h>
using namespace std;

void calcPowSum(unsigned long long nMod, unsigned long long m, unsigned long long k, unsigned long long &p, unsigned long long &s) {
    if (k == 0) {
        p = 1 % m;
        s = 0;
        return;
    }
    if (k == 1) {
        p = nMod % m;
        s = 1 % m;
        return;
    }
    if (k % 2 == 0) {
        unsigned long long pHalf, sHalf;
        calcPowSum(nMod, m, k / 2, pHalf, sHalf);
        p = (pHalf * pHalf) % m;
        s = (sHalf * (1 + pHalf)) % m;
    } else {
        unsigned long long pPrev, sPrev;
        calcPowSum(nMod, m, k - 1, pPrev, sPrev);
        p = (pPrev * nMod) % m;
        s = (sPrev + pPrev) % m;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned long long L;
    int caseNum = 1;
    while (cin >> L && L != 0) {
        unsigned long long b, n, m, C;
        cin >> b >> n >> m >> C;
        int B = (int)b;
        vector<unsigned long long> runs;
        unsigned long long first;
        cin >> first;
        runs.push_back(first);
        while (true) {
            unsigned long long y;
            cin >> y;
            if (y == 0) break;
            runs.push_back(y);
        }
        unsigned long long totalLen = 0;
        for (auto d : runs) totalLen += d;
        if (totalLen != L) {
            cout << "Bitstream " << caseNum << ": Invalid Length\n";
            ++caseNum;
            continue;
        }
        unsigned long long chk = 0;
        int bit = 0;
        int cnt = 0;
        unsigned long long curVal = 0;
        unsigned long long nMod = n % m;
        for (auto d : runs) {
            if (d > 0) {
                unsigned long long len = d;
                while (len > 0) {
                    if (cnt == 0) {
                        unsigned long long full = len / B;
                        unsigned long long rem = len % B;
                        if (full > 0) {
                            unsigned long long v = bit ? ((1ULL << B) - 1ULL) : 0ULL;
                            unsigned long long p, s;
                            calcPowSum(nMod, m, full, p, s);
                            chk = ((chk * p) % m + ((v % m) * s) % m) % m;
                        }
                        if (rem > 0) {
                            curVal = bit ? ((1ULL << rem) - 1ULL) : 0ULL;
                            cnt = (int)rem;
                        }
                        len = 0;
                    } else {
                        int need = B - cnt;
                        if (len <= (unsigned long long)need) {
                            curVal = (curVal << len) | (bit ? ((1ULL << len) - 1ULL) : 0ULL);
                            cnt += (int)len;
                            len = 0;
                        } else {
                            curVal = (curVal << need) | (bit ? ((1ULL << need) - 1ULL) : 0ULL);
                            chk = (chk * nMod + curVal) % m;
                            cnt = 0;
                            curVal = 0;
                            len -= need;
                        }
                    }
                }
            }
            bit ^= 1;
        }
        if (cnt > 0) {
            unsigned long long blockVal = curVal << (B - cnt);
            chk = (chk * nMod + blockVal) % m;
        }
        if (chk == C)
            cout << "Bitstream " << caseNum << ": Compression OK\n";
        else
            cout << "Bitstream " << caseNum << ": Invalid Checksum\n";
        ++caseNum;
    }
    return 0;
}
