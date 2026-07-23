// Zero-Knowledge Protocol
// UVa ID: 12706
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<long long> S(N), P(M);
        for (int i = 0; i < N; ++i) cin >> S[i];
        for (int i = 0; i < M; ++i) cin >> P[i];
        long long ans = 0;
        if (M > N) {
            cout << 0 << '\n';
            continue;
        }
        unordered_map<long long, int> freqP;
        for (long long x : P) freqP[x]++;
        int distinctP = (int)freqP.size();
        unordered_map<long long, int> freqWin;
        int diff = distinctP;
        auto add = [&](long long x) {
            int oldWin = 0;
            auto itWin = freqWin.find(x);
            if (itWin != freqWin.end()) oldWin = itWin->second;
            int oldP = 0;
            auto itP = freqP.find(x);
            if (itP != freqP.end()) oldP = itP->second;
            bool wasEq = (oldWin == oldP);
            freqWin[x] = oldWin + 1;
            int newWin = oldWin + 1;
            bool nowEq = (newWin == oldP);
            if (wasEq && !nowEq) diff++;
            else if (!wasEq && nowEq) diff--;
        };
        auto remove = [&](long long x) {
            int oldWin = freqWin[x];
            int oldP = 0;
            auto itP = freqP.find(x);
            if (itP != freqP.end()) oldP = itP->second;
            bool wasEq = (oldWin == oldP);
            int newWin = oldWin - 1;
            freqWin[x] = newWin;
            bool nowEq = (newWin == oldP);
            if (wasEq && !nowEq) diff++;
            else if (!wasEq && nowEq) diff--;
            if (newWin == 0) freqWin.erase(x);
        };
        for (int i = 0; i < M; ++i) add(S[i]);
        if (diff == 0) ans += 1LL * 1 * 1;
        for (int start = 1; start <= N - M; ++start) {
            remove(S[start - 1]);
            add(S[start + M - 1]);
            if (diff == 0) {
                long long idx = start + 1;
                ans += idx * idx;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
