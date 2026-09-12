#include <bits/stdc++.h>
using namespace std;

void addPos(set<long long> &posSet, long long pos, long long total) {
    if (pos >= 0 && pos <= total) posSet.insert(pos);
}

int getVal(const vector<long long> &sta, const vector<int> &val, long long pos) {
    int id = upper_bound(sta.begin(), sta.end(), pos) - sta.begin() - 1;
    return val[id];
}

int getEdge(const vector<long long> &sta, const vector<int> &val, long long w, long long pos, long long total) {
    long long row = pos / w, col = pos % w;
    int cur = getVal(sta, val, pos), ans = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            long long nr = row + dr, nc = col + dc;
            if (nr < 0 || nc < 0 || nc >= w || nr * w + nc >= total) continue;
            int now = getVal(sta, val, nr * w + nc);
            ans = max(ans, abs(cur - now));
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long w;
    while (cin >> w && w) {
        vector<long long> sta;
        vector<int> val;
        long long total = 0, len;
        int color;
        while (cin >> color >> len) {
            if (color == 0 && len == 0) break;
            sta.push_back(total);
            val.push_back(color);
            total += len;
        }
        set<long long> posSet;
        addPos(posSet, 0, total);
        addPos(posSet, total, total);
        long long del[9] = {-w - 1, -w, -w + 1, -1, 0, 1, w - 1, w, w + 1};
        for (int i = 1; i < (int)sta.size(); i++) {
            long long b = sta[i];
            for (int j = 0; j < 9; j++) addPos(posSet, b - del[j], total);
            long long lo = max(0LL, b - w - 2), hi = min(total, b + w + 2);
            long long k0 = lo / w - 1, k1 = hi / w + 1;
            for (long long k = k0; k <= k1; k++) {
                addPos(posSet, k * w - 1, total);
                addPos(posSet, k * w, total);
                addPos(posSet, k * w + 1, total);
            }
        }
        vector<long long> pos(posSet.begin(), posSet.end());
        vector<pair<int, long long>> out;
        for (int i = 0; i + 1 < (int)pos.size(); i++) {
            long long left = pos[i], right = pos[i + 1];
            if (left >= right) continue;
            int edge = getEdge(sta, val, w, left, total);
            if (!out.empty() && out.back().first == edge) out.back().second += right - left;
            else out.push_back({edge, right - left});
        }
        cout << w << '\n';
        for (auto item : out) cout << item.first << ' ' << item.second << '\n';
        cout << "0 0\n";
    }
    cout << "0\n";
    return 0;
}
