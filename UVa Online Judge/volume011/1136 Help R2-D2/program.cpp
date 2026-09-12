#include <bits/stdc++.h>
using namespace std;

class SegTree {
public:
    int n, base;
    vector<int> tree;
    SegTree(int size, int cap) {
        n = size;
        base = 1;
        while (base < n) base <<= 1;
        tree.assign(base << 1, -1);
        for (int i = 0; i < n; i++) tree[base + i] = cap;
        for (int i = base - 1; i > 0; i--) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
    }
    int findFirst(int val) {
        int pos = 1;
        while (pos < base) {
            if (tree[pos << 1] >= val) pos <<= 1;
            else pos = pos << 1 | 1;
        }
        return pos - base;
    }
    void update(int idx, int val) {
        int pos = base + idx;
        tree[pos] -= val;
        pos >>= 1;
        while (pos > 0) {
            tree[pos] = max(tree[pos << 1], tree[pos << 1 | 1]);
            pos >>= 1;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cap, n;
    bool first = true;
    while (cin >> cap >> n) {
        SegTree seg(n, cap);
        long long sum = 0;
        int ships = 0;
        for (int i = 0; i < n;) {
            string cmd;
            cin >> cmd;
            int cnt, val;
            if (cmd == "b") cin >> cnt >> val;
            else {
                cnt = 1;
                val = stoi(cmd);
            }
            for (int j = 0; j < cnt; j++) {
                int idx = seg.findFirst(val);
                seg.update(idx, val);
                ships = max(ships, idx + 1);
                sum += val;
                i++;
            }
        }
        if (!first) cout << '\n';
        first = false;
        cout << ships << ' ' << 1LL * ships * cap - sum << '\n';
    }
    return 0;
}
