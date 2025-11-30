// Rip Van Winkle's Code
// UVa ID: 12436
// Verdict: Accepted
// Submission Date: 2025-11-30
// UVa Run Time: 0.200s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250005;

struct Node {
    long long sum;          // 区间和
    long long cover;        // 覆盖标记，INF表示未覆盖
    long long k, b;         // 线性标记：k*i + b
    int len;                // 区间长度
} tree[MAXN * 4];

const long long INF = 1e18;

void build(int node, int l, int r) {
    tree[node] = {0, INF, 0, 0, r - l + 1};
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build(node << 1 | 1, mid + 1, r);
}

// 计算线性函数在区间[l, r]上的和
inline long long calcLinearSum(int l, int r, long long k, long long b) {
    return k * (l + r) * (r - l + 1) / 2 + b * (r - l + 1);
}

// 应用覆盖标记
void applyCover(int node, int l, int r, long long val) {
    tree[node].sum = (r - l + 1) * val;
    tree[node].cover = val;
    tree[node].k = tree[node].b = 0;
}

// 应用线性标记
void applyLinear(int node, int l, int r, long long k, long long b) {
    tree[node].sum += calcLinearSum(l, r, k, b);
    tree[node].k += k;
    tree[node].b += b;
}

// 下推懒标记
void pushDown(int node, int l, int r) {
    if (l == r) return;
    
    int mid = (l + r) >> 1;
    int left = node << 1, right = node << 1 | 1;
    
    // 先处理覆盖标记（优先级最高）
    if (tree[node].cover != INF) {
        applyCover(left, l, mid, tree[node].cover);
        applyCover(right, mid + 1, r, tree[node].cover);
        tree[node].cover = INF;
    }
    
    // 再处理线性标记
    if (tree[node].k != 0 || tree[node].b != 0) {
        applyLinear(left, l, mid, tree[node].k, tree[node].b);
        applyLinear(right, mid + 1, r, tree[node].k, tree[node].b);
        tree[node].k = tree[node].b = 0;
    }
}

// 区间覆盖更新
void updateCover(int node, int l, int r, int ql, int qr, long long val) {
    if (ql <= l && r <= qr) {
        applyCover(node, l, r, val);
        return;
    }
    pushDown(node, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) updateCover(node << 1, l, mid, ql, qr, val);
    if (qr > mid) updateCover(node << 1 | 1, mid + 1, r, ql, qr, val);
    tree[node].sum = tree[node << 1].sum + tree[node << 1 | 1].sum;
}

// 区间线性更新
void updateLinear(int node, int l, int r, int ql, int qr, long long k, long long b) {
    if (ql <= l && r <= qr) {
        applyLinear(node, l, r, k, b);
        return;
    }
    pushDown(node, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) updateLinear(node << 1, l, mid, ql, qr, k, b);
    if (qr > mid) updateLinear(node << 1 | 1, mid + 1, r, ql, qr, k, b);
    tree[node].sum = tree[node << 1].sum + tree[node << 1 | 1].sum;
}

// 区间查询
long long query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node].sum;
    pushDown(node, l, r);
    int mid = (l + r) >> 1;
    long long res = 0;
    if (ql <= mid) res += query(node << 1, l, mid, ql, qr);
    if (qr > mid) res += query(node << 1 | 1, mid + 1, r, ql, qr);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    build(1, 1, 250000);
    
    while (t--) {
        char op;
        cin >> op;
        if (op == 'A') {
            int st, nd;
            cin >> st >> nd;
            updateLinear(1, 1, 250000, st, nd, 1, -st + 1);
        } else if (op == 'B') {
            int st, nd;
            cin >> st >> nd;
            updateLinear(1, 1, 250000, st, nd, -1, nd + 1);
        } else if (op == 'C') {
            int st, nd, x;
            cin >> st >> nd >> x;
            updateCover(1, 1, 250000, st, nd, x);
        } else {
            int st, nd;
            cin >> st >> nd;
            cout << query(1, 1, 250000, st, nd) << '\n';
        }
    }
    
    return 0;
}
