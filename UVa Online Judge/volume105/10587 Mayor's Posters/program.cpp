// Mayor's Posters
// UVa ID: 10587
// Verdict: Accepted
// Submission Date: 2025-10-21
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000; // 最大海报数量

struct Poster {
    int l, r; // 海报覆盖的左右端点
} posters[MAXN + 5];

vector<int> vals; // 存储所有端点坐标用于离散化
unordered_map<int, int> mapping; // 原始坐标到离散化索引的映射

// 线段树相关
const int MAXM = 20000; // 离散化后的最大坐标数量
bool tree[4 * MAXM]; // 线段树，记录区间是否完全被覆盖
bool lazy[4 * MAXM]; // 懒标记，表示该区间需要被覆盖

// 下推懒标记
void push_down(int idx) {
    if (lazy[idx]) {
        tree[idx * 2] = true;
        tree[idx * 2 + 1] = true;
        lazy[idx * 2] = true;
        lazy[idx * 2 + 1] = true;
        lazy[idx] = false;
    }
}

// 查询区间 [ql, qr] 是否全部被覆盖
bool query(int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return true; // 无交集，视为已覆盖
    if (tree[idx]) return true; // 整个区间已被覆盖
    if (ql <= l && r <= qr) {
        return tree[idx]; // 当前区间完全在查询范围内
    }
    push_down(idx); // 下推懒标记
    int mid = (l + r) / 2;
    bool left_covered = true, right_covered = true;
    if (ql <= mid)
        left_covered = query(idx * 2, l, mid, ql, qr);
    if (qr > mid)
        right_covered = query(idx * 2 + 1, mid + 1, r, ql, qr);
    return left_covered && right_covered; // 左右子树都覆盖才算完全覆盖
}

// 更新区间 [ql, qr] 为已覆盖
void update(int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return; // 无交集，直接返回
    if (ql <= l && r <= qr) {
        tree[idx] = true; // 当前区间完全在更新范围内
        lazy[idx] = true; // 设置懒标记
        return;
    }
    push_down(idx); // 下推懒标记
    int mid = (l + r) / 2;
    if (ql <= mid)
        update(idx * 2, l, mid, ql, qr);
    if (qr > mid)
        update(idx * 2 + 1, mid + 1, r, ql, qr);
    tree[idx] = tree[idx * 2] && tree[idx * 2 + 1]; // 更新父节点
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int c;
    cin >> c; // 测试用例数量
    while (c--) {
        int n;
        cin >> n; // 海报数量
        vals.clear();
        mapping.clear();
        
        // 读取所有海报区间
        for (int i = 0; i < n; i++) {
            cin >> posters[i].l >> posters[i].r;
            vals.push_back(posters[i].l);
            vals.push_back(posters[i].r);
        }

        // 离散化处理
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        int m = vals.size(); // 离散化后的坐标数量
        // 建立映射关系
        for (int i = 0; i < m; i++) {
            mapping[vals[i]] = i + 1; // 索引从1开始
        }

        // 初始化线段树
        memset(tree, 0, sizeof(tree));
        memset(lazy, 0, sizeof(lazy));

        int visible = 0; // 可见海报计数器
        // 从后往前处理海报
        for (int i = n - 1; i >= 0; i--) {
            int l = mapping[posters[i].l]; // 映射左端点
            int r = mapping[posters[i].r]; // 映射右端点
            // 查询当前海报区间是否还有未被覆盖的部分
            if (!query(1, 1, m, l, r)) {
                visible++; // 有未被覆盖的部分，该海报可见
            }
            // 更新线段树，标记该区间为已覆盖
            update(1, 1, m, l, r);
        }
        cout << visible << "\n";
    }

    return 0;
}
