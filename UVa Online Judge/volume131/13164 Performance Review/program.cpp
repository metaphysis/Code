#include <bits/stdc++.h>
using namespace std;

struct Node {
    int left, right;
    long long sum;
};

vector<Node> seg;

int update(int pre, int l, int r, int pos, int val) {
    int cur = (int)seg.size();
    seg.push_back(seg[pre]);
    seg[cur].sum += val;
    if (l == r) return cur;
    int mid = l + r >> 1;
    if (pos <= mid) seg[cur].left = update(seg[pre].left, l, mid, pos, val);
    else seg[cur].right = update(seg[pre].right, mid + 1, r, pos, val);
    return cur;
}

long long query(int now, int pre, int l, int r, int ql, int qr) {
    if (ql > qr) return 0;
    if (ql <= l && r <= qr) return seg[now].sum - seg[pre].sum;
    if (qr < l || r < ql) return 0;
    int mid = l + r >> 1;
    return query(seg[now].left, seg[pre].left, l, mid, ql, qr) + query(seg[now].right, seg[pre].right, mid + 1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<vector<int>> child(n + 1);
        vector<int> rank(n + 1), time(n + 1), tin(n + 1), size(n + 1), euler(n + 1), order;
        int root = 1;
        for (int i = 1; i <= n; ++i) {
            int manager;
            cin >> manager >> rank[i] >> time[i];
            if (manager == -1) root = i;
            else child[manager].push_back(i);
        }
        vector<int> stk;
        stk.push_back(root);
        int timer = 0;
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            tin[u] = ++timer;
            euler[timer] = u;
            order.push_back(u);
            for (int i = (int)child[u].size() - 1; i >= 0; --i) stk.push_back(child[u][i]);
        }
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            size[u] = 1;
            for (int v : child[u]) size[u] += size[v];
        }
        vector<int> tout(n + 1), roots(n + 1, 0);
        for (int i = 1; i <= n; ++i) tout[euler[i]] = tin[euler[i]] + size[euler[i]] - 1;
        seg.clear();
        seg.reserve(n * 18 + 1);
        seg.push_back({0, 0, 0});
        for (int i = 1; i <= n; ++i) {
            int u = euler[i];
            roots[i] = update(roots[i - 1], 1, 100000, rank[u], time[u]);
        }
        for (int i = 1; i <= n; ++i) {
            int u = i;
            long long ans = query(roots[tout[u]], roots[tin[u] - 1], 1, 100000, 1, rank[u] - 1);
            cout << ans << '\n';
        }
    }
    return 0;
}
