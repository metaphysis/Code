// Cybercrime Donut Investigation
// UVa ID: 12389
// Verdict: Accepted
// Submission Date: 2026-08-07
// UVa Run Time: 0.360s

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long u, v;
};

struct Node {
    long long u, v, minU, maxU, minV, maxV;
    int left, right;
};

vector<Point> pts;
vector<Node> tree;
int curAxis;

bool cmpPoint(const Point& a, const Point& b) {
    if (curAxis == 0) return a.u < b.u;
    return a.v < b.v;
}

inline long long calcBound(int id, long long u0, long long v0) {
    long long dU = 0, dV = 0;
    if (u0 < tree[id].minU) dU = tree[id].minU - u0;
    else if (u0 > tree[id].maxU) dU = u0 - tree[id].maxU;
    if (v0 < tree[id].minV) dV = tree[id].minV - v0;
    else if (v0 > tree[id].maxV) dV = v0 - tree[id].maxV;
    return dU > dV ? dU : dV;
}

int build(int l, int r, int depth) {
    if (l > r) return -1;
    int mid = (l + r) / 2;
    curAxis = depth & 1;
    nth_element(pts.begin() + l, pts.begin() + mid, pts.begin() + r + 1, cmpPoint);
    int id = (int)tree.size();
    tree.push_back(Node());
    tree[id].u = pts[mid].u;
    tree[id].v = pts[mid].v;
    tree[id].left = build(l, mid - 1, depth + 1);
    tree[id].right = build(mid + 1, r, depth + 1);
    tree[id].minU = tree[id].maxU = tree[id].u;
    tree[id].minV = tree[id].maxV = tree[id].v;
    if (tree[id].left != -1) {
        tree[id].minU = min(tree[id].minU, tree[tree[id].left].minU);
        tree[id].maxU = max(tree[id].maxU, tree[tree[id].left].maxU);
        tree[id].minV = min(tree[id].minV, tree[tree[id].left].minV);
        tree[id].maxV = max(tree[id].maxV, tree[tree[id].left].maxV);
    }
    if (tree[id].right != -1) {
        tree[id].minU = min(tree[id].minU, tree[tree[id].right].minU);
        tree[id].maxU = max(tree[id].maxU, tree[tree[id].right].maxU);
        tree[id].minV = min(tree[id].minV, tree[tree[id].right].minV);
        tree[id].maxV = max(tree[id].maxV, tree[tree[id].right].maxV);
    }
    return id;
}

void query(int id, long long u0, long long v0, long long &ans) {
    if (id == -1) return;
    if (ans == 0) return;
    if (calcBound(id, u0, v0) >= ans) return;
    long long du = u0 - tree[id].u;
    long long dv = v0 - tree[id].v;
    if (du < 0) du = -du;
    if (dv < 0) dv = -dv;
    long long dist = du > dv ? du : dv;
    if (dist < ans) ans = dist;
    int lc = tree[id].left, rc = tree[id].right;
    if (lc != -1 && rc != -1) {
        long long lbL = calcBound(lc, u0, v0);
        long long lbR = calcBound(rc, u0, v0);
        if (lbL < lbR) {
            query(lc, u0, v0, ans);
            query(rc, u0, v0, ans);
        } else {
            query(rc, u0, v0, ans);
            query(lc, u0, v0, ans);
        }
    } else {
        if (lc != -1) query(lc, u0, v0, ans);
        if (rc != -1) query(rc, u0, v0, ans);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    bool first = true;
    while (cin >> n) {
        if (n == -1) break;
        if (!first) cout << '\n';
        first = false;
        pts.resize(n);
        for (int i = 0; i < n; ++i) {
            long long l, w;
            cin >> l >> w;
            pts[i].u = l + w;
            pts[i].v = l - w;
        }
        tree.clear();
        tree.reserve(n);
        int root = build(0, n - 1, 0);
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            long long l, w;
            cin >> l >> w;
            long long u0 = l + w, v0 = l - w;
            long long ans = LLONG_MAX;
            query(root, u0, v0, ans);
            cout << ans << '\n';
        }
    }
    return 0;
}
