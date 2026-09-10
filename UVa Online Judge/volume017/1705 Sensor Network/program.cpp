// Sensor Network
// UVa ID: 1705
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, bestSize;
long long limitDist2;
bitset<MAXN> adjBits[MAXN];
bitset<MAXN> bestCliqueBits;

void expandMaxClique(bitset<MAXN> R, bitset<MAXN> P, bitset<MAXN> X) {
    if (P.none() && X.none()) {
        int cnt = (int)R.count();
        if (cnt > bestSize) {
            bestSize = cnt;
            bestCliqueBits = R;
        }
        return;
    }
    if ((int)R.count() + (int)P.count() <= bestSize) return;
    vector<int> pList;
    for (int i = 0; i < n; ++i)
        if (P.test(i)) pList.push_back(i);
    sort(pList.begin(), pList.end(), [&](int a, int b) {
        int da = (int)adjBits[a].count();
        int db = (int)adjBits[b].count();
        if (da != db) return da > db;
        return a < b;
    });
    vector<int> color(n, -1);
    int usedColors = 0;
    for (int v : pList) {
        bool used[105] = {false};
        for (int w : pList) {
            if (color[w] != -1 && adjBits[v].test(w))
                used[color[w]] = true;
        }
        int c = 0;
        while (used[c]) ++c;
        color[v] = c;
        if (c + 1 > usedColors) usedColors = c + 1;
    }
    if ((int)R.count() + usedColors <= bestSize) return;
    bitset<MAXN> U = P | X;
    int u = -1;
    int minDiff = n + 1;
    for (int i = 0; i < n; ++i) {
        if (U.test(i)) {
            bitset<MAXN> nonNei = P & ~adjBits[i];
            int cnt = (int)nonNei.count();
            if (cnt < minDiff) {
                minDiff = cnt;
                u = i;
            }
        }
    }
    if (u == -1) return;
    bitset<MAXN> cand = P & ~adjBits[u];
    vector<int> candList;
    for (int i = 0; i < n; ++i)
        if (cand.test(i)) candList.push_back(i);
    sort(candList.begin(), candList.end(), [&](int a, int b) {
        int da = (int)adjBits[a].count();
        int db = (int)adjBits[b].count();
        if (da != db) return da > db;
        return a < b;
    });
    bitset<MAXN> curP = P;
    bitset<MAXN> curX = X;
    for (int v : candList) {
        if (!curP.test(v)) continue;
        bitset<MAXN> newP = curP & adjBits[v];
        bitset<MAXN> newX = curX & adjBits[v];
        R.set(v);
        expandMaxClique(R, newP, newX);
        R.reset(v);
        curP.reset(v);
        curX.set(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int d;
    while (cin >> n >> d) {
        limitDist2 = 1LL * d * d;
        for (int i = 0; i < MAXN; ++i) adjBits[i].reset();
        bestCliqueBits.reset();
        bestSize = 0;
        vector<pair<int, int>> pts(n);
        for (int i = 0; i < n; ++i)
            cin >> pts[i].first >> pts[i].second;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                long long dx = pts[i].first - pts[j].first;
                long long dy = pts[i].second - pts[j].second;
                if (dx * dx + dy * dy <= limitDist2) {
                    adjBits[i].set(j);
                    adjBits[j].set(i);
                }
            }
        }
        bitset<MAXN> all;
        for (int i = 0; i < n; ++i) all.set(i);
        expandMaxClique(bitset<MAXN>(), all, bitset<MAXN>());
        vector<int> ans;
        for (int i = 0; i < n; ++i)
            if (bestCliqueBits.test(i)) ans.push_back(i + 1);
        cout << bestSize << '\n';
        for (size_t i = 0; i < ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
