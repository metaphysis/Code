// A Sequence of Numbers
// UVa ID: 1406
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.210s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, caseNo = 1;
    while (cin >> N && N != -1) {
        vector<int> cnt(65536, 0);
        for (int i = 0; i < N; ++i) {
            int x;
            cin >> x;
            ++cnt[x];
        }

        // ansTable[T][shift] 表示当位为 T 且全局偏移为 shift（模 2^(T+1)）时的答案
        vector<vector<long long>> ansTable(16, vector<long long>(65536, 0));

        for (int T = 0; T < 16; ++T) {
            int M = 1 << (T + 1);          // 模数
            int half = 1 << T;              // 区间长度（后半段）
            vector<long long> A(M, 0);

            for (int v = 0; v < 65536; ++v)
                if (cnt[v]) A[v % M] += cnt[v];

            // 循环前缀和（复制一份）
            vector<long long> pref(2 * M + 1, 0);
            for (int i = 0; i < 2 * M; ++i)
                pref[i + 1] = pref[i] + A[i % M];

            for (int shift = 0; shift < M; ++shift) {
                // 起点 s = (half - shift) mod M，区间长度为 half
                int s = (half - shift) % M;
                if (s < 0) s += M;
                ansTable[T][shift] = pref[s + half] - pref[s];
            }
        }

        long long total = 0;
        int offset = 0;          // 全局累加偏移（模 65536）
        string op;

        while (cin >> op) {
            if (op == "E") break;
            if (op == "C") {
                int delta;
                cin >> delta;
                offset = (offset + delta) % 65536;
            } else { // "Q"
                int T;
                cin >> T;
                int M = 1 << (T + 1);
                int shift = offset % M;
                total += ansTable[T][shift];
            }
        }

        cout << "Case " << caseNo << ": " << total << '\n';
        ++caseNo;
    }

    return 0;
}
