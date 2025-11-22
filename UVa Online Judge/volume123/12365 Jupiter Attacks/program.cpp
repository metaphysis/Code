// Jupiter Attacks
// UVa ID: 12365
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.160s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;

long long base, mod;
int len, n;

long long powBase[MAXN];

struct SegmentTree {
    vector<long long> tree;
    vector<int> length;
    
    SegmentTree(int size) {
        tree.resize(4 * size);
        length.resize(4 * size);
        build(1, 1, size);
    }
    
    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = 0;
            length[node] = 1;
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        length[node] = length[node * 2] + length[node * 2 + 1];
        tree[node] = 0;
    }
    
    void update(int node, int l, int r, int pos, long long val) {
        if (l == r) {
            tree[node] = val % mod;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) update(node * 2, l, mid, pos, val);
        else update(node * 2 + 1, mid + 1, r, pos, val);
        
        tree[node] = (tree[node * 2] * powBase[length[node * 2 + 1]] + tree[node * 2 + 1]) % mod;
    }
    
    pair<long long, int> query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return {tree[node], length[node]};
        
        int mid = (l + r) / 2;
        if (qr <= mid) return query(node * 2, l, mid, ql, qr);
        if (ql > mid) return query(node * 2 + 1, mid + 1, r, ql, qr);
        
        auto leftRes = query(node * 2, l, mid, ql, qr);
        auto rightRes = query(node * 2 + 1, mid + 1, r, ql, qr);
        
        long long hashVal = (leftRes.first * powBase[rightRes.second] + rightRes.first) % mod;
        int totalLen = leftRes.second + rightRes.second;
        return {hashVal, totalLen};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (true) {
        cin >> base >> mod >> len >> n;
        if (base == 0 && mod == 0 && len == 0 && n == 0) break;
        
        powBase[0] = 1;
        for (int i = 1; i <= len; i++)
            powBase[i] = powBase[i - 1] * base % mod;
        
        SegmentTree segTree(len);
        
        for (int i = 0; i < n; i++) {
            char cmd;
            cin >> cmd;
            if (cmd == 'E') {
                int pos; long long val;
                cin >> pos >> val;
                segTree.update(1, 1, len, pos, val);
            } else {
                int l, r;
                cin >> l >> r;
                auto res = segTree.query(1, 1, len, l, r);
                cout << res.first << "\n";
            }
        }
        cout << "-\n";
    }
    
    return 0;
}
