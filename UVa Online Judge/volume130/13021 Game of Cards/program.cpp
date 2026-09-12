// Game of Cards
// UVa ID: 13021
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

int getGrundy(const vector<int>& card, int maxRemove) {
    int pileSize = card.size() - 1, n, removeCount, nextSize, stamp;
    vector<int> grundy(pileSize + 1, 0), mark(maxRemove + 2, 0);
    for (n = 1; n <= pileSize; ++n) {
        stamp = n;
        for (removeCount = 0; removeCount <= maxRemove && removeCount < n; ++removeCount) {
            if (card[n - removeCount] <= n - removeCount) {
                nextSize = n - removeCount - card[n - removeCount];
                if (grundy[nextSize] <= maxRemove + 1) mark[grundy[nextSize]] = stamp;
            }
        }
        grundy[n] = 0;
        while (mark[grundy[n]] == stamp) ++grundy[n];
    }
    return grundy[pileSize];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int pileCount, maxRemove, pileSize, i, j, result;
    while (cin >> pileCount >> maxRemove) {
        result = 0;
        for (i = 0; i < pileCount; ++i) {
            cin >> pileSize;
            vector<int> card(pileSize + 1);
            for (j = 1; j <= pileSize; ++j) cin >> card[j];
            result ^= getGrundy(card, maxRemove);
        }
        if (result != 0) cout << "Alice can win.\n";
        else cout << "Bob will win.\n";
    }
    return 0;
}
