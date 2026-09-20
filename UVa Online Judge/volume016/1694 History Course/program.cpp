#include <bits/stdc++.h>
using namespace std;

const int maxN = 50005;
const int infId = maxN - 1;

struct Interval {
    int l, r;
    bool operator < (const Interval &other) const {
        if (l != other.l) return l < other.l;
        return r < other.r;
    }
};

struct SegNode {
    int sum, preMin, best;
};

Interval intervals[maxN];
SegNode tree[maxN * 4];
int n, answer[maxN], limitPos[maxN], rightLimit[maxN];
bool marked[maxN];
vector<tuple<int, int, int>> parts;

int betterId(int x, int y) {
    if (intervals[x].r != intervals[y].r) return intervals[x].r < intervals[y].r ? x : y;
    return x < y ? x : y;
}

void pull(int id) {
    int lc = id * 2, rc = lc + 1;
    tree[id].sum = tree[lc].sum + tree[rc].sum;
    tree[id].preMin = min(tree[lc].preMin, tree[lc].sum + tree[rc].preMin);
    tree[id].best = betterId(tree[lc].best, tree[rc].best);
}

void build(int id, int l, int r) {
    if (l == r) {
        tree[id].sum = tree[id].preMin = 1;
        tree[id].best = l;
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    pull(id);
}

void addPoint(int id, int l, int r, int pos, int val) {
    if (l == r) {
        tree[id].sum += val;
        tree[id].preMin += val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) addPoint(id * 2, l, mid, pos, val);
    else addPoint(id * 2 + 1, mid + 1, r, pos, val);
    pull(id);
}

void removeInterval(int id, int l, int r, int pos) {
    if (l == r) {
        tree[id].best = infId;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) removeInterval(id * 2, l, mid, pos);
    else removeInterval(id * 2 + 1, mid + 1, r, pos);
    tree[id].best = betterId(tree[id * 2].best, tree[id * 2 + 1].best);
}

int queryBest(int id, int l, int r, int qr) {
    if (r <= qr) return tree[id].best;
    int mid = (l + r) / 2;
    if (qr <= mid) return queryBest(id * 2, l, mid, qr);
    return betterId(tree[id * 2].best, queryBest(id * 2 + 1, mid + 1, r, qr));
}

void collectParts(int id, int l, int r, int ql) {
    if (ql <= l) {
        parts.emplace_back(id, l, r);
        return;
    }
    int mid = (l + r) / 2;
    if (ql <= mid) collectParts(id * 2, l, mid, ql);
    collectParts(id * 2 + 1, mid + 1, r, ql);
}

int findBoundary(int start) {
    parts.clear();
    collectParts(1, 0, n - 1, start);
    int base = 0, id = 0, l = 0, r = 0;
    bool found = false;
    for (auto part : parts) {
        tie(id, l, r) = part;
        if (tree[id].preMin < base) return -1;
        if (tree[id].preMin == base) {
            found = true;
            break;
        }
        base -= tree[id].sum;
    }
    if (!found) return n - 1;
    while (l < r) {
        int mid = (l + r) / 2, lc = id * 2;
        if (tree[lc].preMin == base) {
            id = lc;
            r = mid;
        } else {
            base -= tree[lc].sum;
            id = lc + 1;
            l = mid + 1;
        }
    }
    return l;
}

bool check(int k) {
    int scan = 0;
    fill(limitPos, limitPos + n, n - 1);
    fill(rightLimit, rightLimit + n, 0);
    fill(marked, marked + n, false);
    rightLimit[n - 1] = n - 1;
    build(1, 0, n - 1);
    for (int pos = 0; pos < n; pos++) {
        int boundary = findBoundary(pos);
        if (boundary == -1) return false;
        int id = queryBest(1, 0, n - 1, rightLimit[boundary]);
        if (id == infId) return false;
        answer[pos] = id;
        marked[id] = true;
        addPoint(1, 0, n - 1, pos, -1);
        if (limitPos[id] < n - 1) addPoint(1, 0, n - 1, limitPos[id], 1);
        removeInterval(1, 0, n - 1, id);
        if (pos + k < n - 1) {
            while (scan < n && intervals[scan].l <= intervals[id].r) {
                if (!marked[scan]) {
                    if (k == 0) return false;
                    marked[scan] = true;
                    limitPos[scan] = pos + k;
                    addPoint(1, 0, n - 1, limitPos[scan], -1);
                }
                scan++;
            }
            rightLimit[pos + k] = scan - 1;
        }
    }
    return true;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> intervals[i].l >> intervals[i].r;
    sort(intervals, intervals + n);
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }
    check(left);
    cout << left << '\n';
    for (int i = 0; i < n; i++) cout << intervals[answer[i]].l << ' ' << intervals[answer[i]].r << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    intervals[infId].r = INT_MAX;
    int testCases;
    cin >> testCases;
    while (testCases--) solve();
    return 0;
}
