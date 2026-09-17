#include <bits/stdc++.h>
using namespace std;

struct Line {
    long long p, q;
};

struct Event {
    long long u, vl, vr;
    int delta;
    bool operator<(const Event &other) const {
        return u < other.u;
    }
};

struct Node {
    long long cnt[2], sum[2];
    int cover;
};

class SegTree {
private:
    vector<long long> coords;
    vector<Node> tree;
    pair<long long, long long> getInfo(long long l, long long r, int parity) {
        long long first = l, last = r, cnt, sum;
        if ((first & 1LL) != parity) first++;
        if ((last & 1LL) != parity) last--;
        if (first > last) return {0, 0};
        cnt = (last - first) / 2 + 1;
        sum = (first + last) * cnt / 2;
        return {cnt, sum};
    }
    void fillNode(int id, int l, int r) {
        long long left = coords[l], right = coords[r + 1] - 1;
        pair<long long, long long> info;
        for (int p = 0; p < 2; p++) {
            info = getInfo(left, right, p);
            tree[id].cnt[p] = info.first;
            tree[id].sum[p] = info.second;
        }
    }
    void pull(int id, int l, int r) {
        if (tree[id].cover > 0) {
            fillNode(id, l, r);
        } else if (l == r) {
            tree[id].cnt[0] = tree[id].cnt[1] = 0;
            tree[id].sum[0] = tree[id].sum[1] = 0;
        } else {
            for (int p = 0; p < 2; p++) {
                tree[id].cnt[p] = tree[id * 2].cnt[p] + tree[id * 2 + 1].cnt[p];
                tree[id].sum[p] = tree[id * 2].sum[p] + tree[id * 2 + 1].sum[p];
            }
        }
    }
    void update(int id, int l, int r, int ql, int qr, int delta) {
        if (ql <= l && r <= qr) {
            tree[id].cover += delta;
            pull(id, l, r);
            return;
        }
        int mid = (l + r) / 2;
        if (ql <= mid) update(id * 2, l, mid, ql, qr, delta);
        if (qr > mid) update(id * 2 + 1, mid + 1, r, ql, qr, delta);
        pull(id, l, r);
    }
    pair<long long, long long> query(int id, int l, int r, long long ql, long long qr, int parity) {
        long long left = coords[l], right = coords[r + 1] - 1;
        if (qr < left || right < ql) return {0, 0};
        if (ql <= left && right <= qr) return {tree[id].cnt[parity], tree[id].sum[parity]};
        if (tree[id].cover > 0) return getInfo(max(left, ql), min(right, qr), parity);
        if (l == r) return {0, 0};
        int mid = (l + r) / 2;
        pair<long long, long long> a = query(id * 2, l, mid, ql, qr, parity);
        pair<long long, long long> b = query(id * 2 + 1, mid + 1, r, ql, qr, parity);
        return {a.first + b.first, a.second + b.second};
    }
public:
    SegTree(const vector<long long> &values) {
        coords = values;
        tree.resize(coords.size() * 4);
    }
    void update(long long ql, long long qr, int delta) {
        int l = lower_bound(coords.begin(), coords.end(), ql) - coords.begin();
        int r = lower_bound(coords.begin(), coords.end(), qr + 1) - coords.begin() - 1;
        update(1, 0, (int)coords.size() - 2, l, r, delta);
    }
    pair<long long, long long> query(long long ql, long long qr, int parity) {
        if (ql > qr) return {0, 0};
        return query(1, 0, (int)coords.size() - 2, ql, qr, parity);
    }
};

long long floorDiv(long long a, long long b) {
    if (b < 0) {
        a = -a;
        b = -b;
    }
    long long result = a / b;
    if (a < 0 && a % b) result--;
    return result;
}

long long ceilDiv(long long a, long long b) {
    return -floorDiv(-a, b);
}

bool restrictLessEqual(long long a, long long b, long long &left, long long &right) {
    if (a > 0) {
        right = min(right, floorDiv(b, a));
    } else if (a < 0) {
        left = max(left, ceilDiv(b, a));
    } else if (b < 0) {
        return false;
    }
    return left <= right;
}

bool getActiveRange(const vector<Line> &lowerLines, const vector<Line> &upperLines, int lowerId, int upperId, long long &left, long long &right) {
    Line lower = lowerLines[lowerId], upper = upperLines[upperId];
    for (int i = 0; i < (int)lowerLines.size(); i++) {
        if (i == lowerId) continue;
        Line line = lowerLines[i];
        long long limit = lower.q - line.q;
        if (i < lowerId) limit--;
        if (!restrictLessEqual(line.p - lower.p, limit, left, right)) return false;
    }
    for (int i = 0; i < (int)upperLines.size(); i++) {
        if (i == upperId) continue;
        Line line = upperLines[i];
        long long limit = line.q - upper.q;
        if (i < upperId) limit--;
        if (!restrictLessEqual(upper.p - line.p, limit, left, right)) return false;
    }
    if (!restrictLessEqual(lower.p - upper.p, upper.q - lower.q, left, right)) return false;
    return left <= right;
}

long long countRange(const Line &lower, const Line &upper, long long vl, long long vr, int parity, SegTree &segTree) {
    pair<long long, long long> info = segTree.query(vl, vr, parity);
    long long cnt = info.first, sum = info.second;
    if (!cnt) return 0;
    long long lowerAtParity = lower.p * parity + lower.q;
    long long upperAtParity = upper.p * parity + upper.q;
    long long firstAdd = ((parity - lowerAtParity) % 2 + 2) % 2;
    long long lastSub = ((upperAtParity - parity) % 2 + 2) % 2;
    long long base = (upperAtParity - lastSub - lowerAtParity - firstAdd) / 2 + 1;
    long long step = upper.p - lower.p;
    long long sumT = (sum - parity * cnt) / 2;
    return base * cnt + step * sumT;
}

long long countSlab(long long leftU, long long rightU, long long n, long long m, SegTree &segTree) {
    leftU = max(leftU, 2LL);
    rightU = min(rightU, n + m);
    if (leftU > rightU) return 0;
    long long minV = 1 - m, maxV = n - 1, answer = 0;
    vector<Line> lowerLines = {{0, leftU}, {-1, 2}, {1, 2}};
    vector<Line> upperLines = {{0, rightU}, {-1, 2 * n}, {1, 2 * m}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            long long vl = minV, vr = maxV;
            if (!getActiveRange(lowerLines, upperLines, i, j, vl, vr)) continue;
            for (int parity = 0; parity < 2; parity++)
                answer += countRange(lowerLines[i], upperLines[j], vl, vr, parity, segTree);
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, m;
    int k, caseNumber = 0;
    while (cin >> n && n) {
        cin >> m >> k;
        vector<Event> events;
        vector<long long> coords;
        for (int i = 0; i < k; i++) {
            long long x, y, r, u, v, vl, vr;
            cin >> x >> y >> r;
            u = x + y;
            v = x - y;
            vl = v - r;
            vr = v + r;
            events.push_back({u - r, vl, vr, 1});
            events.push_back({u + r + 1, vl, vr, -1});
            coords.push_back(vl);
            coords.push_back(vr + 1);
        }
        sort(events.begin(), events.end());
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        SegTree segTree(coords);
        long long answer = 0;
        int i = 0;
        while (i < (int)events.size()) {
            int j = i;
            while (j < (int)events.size() && events[j].u == events[i].u) {
                segTree.update(events[j].vl, events[j].vr, events[j].delta);
                j++;
            }
            if (j < (int)events.size()) answer += countSlab(events[i].u, events[j].u - 1, n, m, segTree);
            i = j;
        }
        cout << "Case " << ++caseNumber << ": " << answer << '\n';
    }
    return 0;
}
