#include <bits/stdc++.h>
using namespace std;

struct Bar {
    int x1, y1, x2, y2, score, delay, readyAt;
};

vector<Bar> bars;

bool isLower(int aId, int bId) {
    const Bar &a = bars[aId], &b = bars[bId];
    if (a.x1 >= b.x1) return 1LL * (a.y1 - b.y1) * (b.x2 - b.x1) - 1LL * (b.y2 - b.y1) * (a.x1 - b.x1) < 0;
    return 1LL * (a.y1 - b.y1) * (a.x2 - a.x1) + 1LL * (a.y2 - a.y1) * (b.x1 - a.x1) < 0;
}

bool isBelow(int barId, long long x, long long y) {
    const Bar &bar = bars[barId];
    if (y > max(bar.y1, bar.y2)) return true;
    if (y <= min(bar.y1, bar.y2)) return false;
    return (bar.y1 - y) * (bar.x2 - bar.x1) + 1LL * (bar.y2 - bar.y1) * (x - bar.x1) < 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNo = 0;
    while (cin >> n) {
        bars.resize(n);
        vector<int> coords;
        coords.reserve(2 * n);
        for (int i = 0; i < n; i++) {
            Bar &bar = bars[i];
            cin >> bar.x1 >> bar.y1 >> bar.x2 >> bar.y2 >> bar.score >> bar.delay;
            bar.readyAt = 0;
            coords.push_back(bar.x1);
            coords.push_back(bar.x2 + 1);
        }
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        int leafCount = coords.size() - 1, base = 1;
        while (base < leafCount) base <<= 1;
        vector<vector<int>> tree(2 * base);
        for (int i = 0; i < n; i++) {
            int left = lower_bound(coords.begin(), coords.end(), bars[i].x1) - coords.begin();
            int right = lower_bound(coords.begin(), coords.end(), bars[i].x2 + 1) - coords.begin();
            left += base;
            right += base;
            while (left < right) {
                if (left & 1) tree[left++].push_back(i);
                if (right & 1) tree[--right].push_back(i);
                left >>= 1;
                right >>= 1;
            }
        }
        for (int i = 1; i < 2 * base; i++) sort(tree[i].begin(), tree[i].end(), isLower);
        int ballCount;
        long long totalScore = 0;
        cin >> ballCount;
        cout << "Case " << ++caseNo << ":\n";
        for (int step = 1; step <= ballCount; step++) {
            long long x, y;
            cin >> x >> y;
            x ^= totalScore;
            y ^= totalScore;
            int bestId = -1;
            if (x >= coords.front() && x < coords.back()) {
                int pos = upper_bound(coords.begin(), coords.end(), x) - coords.begin() - 1;
                for (int node = pos + base; node > 0; node >>= 1) {
                    const vector<int> &ids = tree[node];
                    int left = 0, right = ids.size();
                    while (left < right) {
                        int mid = left + (right - left) / 2;
                        if (isBelow(ids[mid], x, y)) left = mid + 1;
                        else right = mid;
                    }
                    int idx = left - 1;
                    while (idx >= 0 && bars[ids[idx]].readyAt > step) idx--;
                    if (idx >= 0) {
                        int barId = ids[idx];
                        if (bestId == -1 || isLower(bestId, barId)) bestId = barId;
                    }
                }
            }
            if (bestId != -1) {
                totalScore += bars[bestId].score;
                bars[bestId].readyAt = step + bars[bestId].delay;
            }
            cout << totalScore << '\n';
        }
        cout << '\n';
    }
    return 0;
}
