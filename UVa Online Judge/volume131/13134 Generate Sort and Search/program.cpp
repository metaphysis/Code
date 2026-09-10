// Generate Sort and Search
// UVa ID: 13134
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, c, m, x, q;
    long long n;
    while (cin >> a >> c >> m >> x >> q >> n) {
        vector<long long> queries(q);
        for (int i = 0; i < q; ++i) cin >> queries[i];
        vector<int> firstPos(m, 0);
        vector<int> seqVal(m + 2);
        int cur = x;
        int idx = 0;
        int cycleStart, cycleLen, prefixLen;
        while (true) {
            cur = (a * cur + c) % m;
            ++idx;
            seqVal[idx] = cur;
            if (firstPos[cur] != 0) {
                cycleStart = firstPos[cur];
                cycleLen = idx - cycleStart;
                prefixLen = cycleStart - 1;
                break;
            }
            firstPos[cur] = idx;
        }
        vector<long long> cnt(m, 0);
        if (n <= prefixLen) {
            for (int i = 1; i <= n; ++i) cnt[seqVal[i]]++;
        } else {
            for (int i = 1; i <= prefixLen; ++i) cnt[seqVal[i]]++;
            vector<long long> cycleCnt(m, 0);
            for (int i = cycleStart; i < cycleStart + cycleLen; ++i) cycleCnt[seqVal[i]]++;
            long long rem = n - prefixLen;
            long long fullCycles = rem / cycleLen;
            long long extra = rem % cycleLen;
            for (int v = 0; v < m; ++v) cnt[v] += fullCycles * cycleCnt[v];
            for (int i = cycleStart; i < cycleStart + extra; ++i) cnt[seqVal[i]]++;
        }
        vector<long long> cum(m);
        cum[0] = cnt[0];
        for (int i = 1; i < m; ++i) cum[i] = cum[i - 1] + cnt[i];
        for (int i = 0; i < q; ++i) {
            long long pos = queries[i];
            int lo = 0, hi = m - 1;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (cum[mid] >= pos) hi = mid;
                else lo = mid + 1;
            }
            cout << lo << "\n";
        }
    }
    return 0;
}
