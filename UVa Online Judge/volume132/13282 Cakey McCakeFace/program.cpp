// Cakey McCakeFace
// UVa ID: 13282
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 1.090s
// https://blog.csdn.net/metaphysis/article/details/163173494

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N) {
        cin >> M;
        vector<int> entryTimes(N), exitTimes(M);
        for (int i = 0; i < N; ++i) cin >> entryTimes[i];
        for (int i = 0; i < M; ++i) cin >> exitTimes[i];
        vector<int> diffs;
        diffs.reserve((size_t)N * M);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j) {
                int d = exitTimes[j] - entryTimes[i];
                if (d >= 0) diffs.push_back(d);
            }
        if (diffs.empty()) {
            cout << 0 << '\n';
            continue;
        }
        sort(diffs.begin(), diffs.end());
        int bestDiff = diffs[0];
        int maxCount = 0;
        int curVal = diffs[0];
        int curCount = 0;
        for (size_t i = 0; i < diffs.size(); ++i) {
            if (diffs[i] == curVal) ++curCount;
            else {
                if (curCount > maxCount) {
                    maxCount = curCount;
                    bestDiff = curVal;
                }
                curVal = diffs[i];
                curCount = 1;
            }
        }
        if (curCount > maxCount) {
            maxCount = curCount;
            bestDiff = curVal;
        }
        cout << bestDiff << '\n';
    }
    return 0;
}
