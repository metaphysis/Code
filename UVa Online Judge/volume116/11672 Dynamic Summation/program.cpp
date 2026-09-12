#include <bits/stdc++.h>
using namespace std;

const int maxNode = 2000005;

struct Node {
    int left, right, sz;
    unsigned pri;
    long long val, sum;
} tr[maxNode];

int tot;
unsigned seed = 123456789;

unsigned rnd() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

int getSz(int x) {
    return x ? tr[x].sz : 0;
}

long long getSum(int x) {
    return x ? tr[x].sum : 0;
}

void pull(int x) {
    tr[x].sz = getSz(tr[x].left) + getSz(tr[x].right) + 1;
    tr[x].sum = getSum(tr[x].left) + getSum(tr[x].right) + tr[x].val;
}

int newNode(long long val) {
    ++tot;
    tr[tot].left = tr[tot].right = 0;
    tr[tot].sz = 1;
    tr[tot].pri = rnd();
    tr[tot].val = tr[tot].sum = val;
    return tot;
}

void split(int root, int k, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }
    if (getSz(tr[root].left) < k) {
        x = root;
        split(tr[root].right, k - getSz(tr[root].left) - 1, tr[root].right, y);
        pull(x);
    } else {
        y = root;
        split(tr[root].left, k, x, tr[root].left);
        pull(y);
    }
}

int mergeTree(int x, int y) {
    if (!x || !y) return x ? x : y;
    if (tr[x].pri < tr[y].pri) {
        tr[x].right = mergeTree(tr[x].right, y);
        pull(x);
        return x;
    }
    tr[y].left = mergeTree(x, tr[y].left);
    pull(y);
    return y;
}

int buildTree(vector<long long> &arr) {
    vector<int> stk, order;
    int root = 0;
    for (long long val : arr) {
        int cur = newNode(val), last = 0;
        while (!stk.empty() && tr[stk.back()].pri > tr[cur].pri) {
            last = stk.back();
            stk.pop_back();
        }
        tr[cur].left = last;
        if (!stk.empty()) tr[stk.back()].right = cur;
        else root = cur;
        stk.push_back(cur);
    }
    stk.clear();
    stk.push_back(root);
    while (!stk.empty()) {
        int x = stk.back();
        stk.pop_back();
        order.push_back(x);
        if (tr[x].left) stk.push_back(tr[x].left);
        if (tr[x].right) stk.push_back(tr[x].right);
    }
    for (int i = (int)order.size() - 1; i >= 0; --i) pull(order[i]);
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, cas = 0;
    while (cin >> c && c) {
        int root = 0;
        tot = 0;
        cout << "Scenario " << ++cas << ":\n";
        while (c--) {
            string op;
            int i, j;
            cin >> op >> i;
            if (op == "insert") {
                int n, r;
                long long m, a, d;
                cin >> n >> r >> m >> a >> d;
                vector<long long> arr(n);
                for (int k = 0; k < r; ++k) cin >> arr[k];
                for (int k = r; k < n; ++k) {
                    long long cur = arr[k - r] * a + d;
                    arr[k] = cur % m;
                    d = (cur / m) % m;
                }
                int x, y;
                split(root, i, x, y);
                root = mergeTree(mergeTree(x, buildTree(arr)), y);
            } else {
                cin >> j;
                int x, y, z;
                split(root, i, x, y);
                split(y, j - i + 1, y, z);
                if (op == "sum") {
                    cout << getSum(y) << '\n';
                    root = mergeTree(mergeTree(x, y), z);
                } else root = mergeTree(x, z);
            }
        }
        cout << '\n';
    }
    return 0;
}
