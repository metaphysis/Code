#include <bits/stdc++.h>
using namespace std;

long long getCost(long long hs, long long vs, long long cnt, long long all) {
    return llabs(2 * cnt * hs * vs - all);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long R, C, r, c, cnt, all, maxHs, maxVs, bestHs, bestVs, bestCost, hs, vs, base, curCost, cand;
    string s;
    int tc = 0;
    while (cin >> R >> C >> r >> c) {
        cnt = 0;
        for (int i = 0; i < r; i++) {
            cin >> s;
            for (char ch : s)
                if (ch == '#') cnt++;
        }
        tc++;
        maxHs = C / c;
        maxVs = R / r;
        if (cnt == 0) {
            cout << "Case " << tc << ": " << maxHs << " 1\n";
            continue;
        }
        all = R * C;
        bestHs = 1;
        bestVs = 1;
        bestCost = LLONG_MAX;
        for (hs = 1; hs <= maxHs; hs++) {
            base = all / (2 * cnt * hs);
            cand = max(1LL, min(maxVs, base));
            curCost = getCost(hs, cand, cnt, all);
            if (curCost < bestCost || (curCost == bestCost && (hs > bestHs || (hs == bestHs && cand < bestVs)))) {
                bestCost = curCost;
                bestHs = hs;
                bestVs = cand;
            }
            cand = max(1LL, min(maxVs, base + 1));
            curCost = getCost(hs, cand, cnt, all);
            if (curCost < bestCost || (curCost == bestCost && (hs > bestHs || (hs == bestHs && cand < bestVs)))) {
                bestCost = curCost;
                bestHs = hs;
                bestVs = cand;
            }
        }
        cout << "Case " << tc << ": " << bestHs << " " << bestVs << "\n";
    }
    return 0;
}
