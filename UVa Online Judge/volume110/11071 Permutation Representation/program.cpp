// Permutation Representation
// UVa ID: 11071
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.190s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// Treap 节点定义
struct Node {
    int val, prio, sz;
    Node *l, *r, *p;
    Node(int v) : val(v), prio(rand()), sz(1), l(nullptr), r(nullptr), p(nullptr) {}
};

// 获取子树大小
int size(Node* t) { return t ? t->sz : 0; }

// 更新节点信息并维护父指针
void update(Node* t) {
    if (!t) return;
    t->sz = 1 + size(t->l) + size(t->r);
    if (t->l) t->l->p = t;
    if (t->r) t->r->p = t;
}

// 合并两棵 Treap（a 的所有元素在 b 之前）
Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->prio < b->prio) {
        a->r = merge(a->r, b);
        update(a);
        return a;
    } else {
        b->l = merge(a, b->l);
        update(b);
        return b;
    }
}

// 按大小分裂：前 k 个元素归左树，其余归右树
pair<Node*, Node*> split(Node* t, int k) {
    if (!t) return {nullptr, nullptr};
    if (size(t->l) >= k) {
        auto p = split(t->l, k);
        t->l = p.second;
        update(t);
        if (p.first) p.first->p = nullptr;
        t->p = nullptr; // 作为新树根，断开旧父
        return {p.first, t};
    } else {
        auto p = split(t->r, k - size(t->l) - 1);
        t->r = p.first;
        update(t);
        if (p.second) p.second->p = nullptr;
        t->p = nullptr;
        return {t, p.second};
    }
}

// 获取节点 u 在树中的 1-based 位置
int getIndex(Node* u) {
    int idx = size(u->l) + 1;
    while (u->p) {
        if (u == u->p->r) idx += size(u->p->l) + 1;
        u = u->p;
    }
    return idx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n) {
        vector<int> domain(n), image(n);
        for (int i = 0; i < n; ++i) cin >> domain[i];
        for (int i = 0; i < n; ++i) cin >> image[i];
        // 构建排列 p: p[定义域元素] = 像元素
        vector<int> p(n + 1);
        for (int i = 0; i < n; ++i) p[domain[i]] = image[i];
        // 创建节点并构建初始 Treap，nodeOfVal[v] 指向值为 v 的节点
        vector<Node*> nodeOfVal(n + 1);
        Node* root = nullptr;
        for (int i = 1; i <= n; ++i) {
            nodeOfVal[p[i]] = new Node(p[i]);
            root = merge(root, nodeOfVal[p[i]]);
        }
        if (root) root->p = nullptr;
        vector<int> a(n + 1);
        a[1] = 0;
        // 从 n 到 2 逐步归位
        for (int k = n; k >= 2; --k) {
            Node* u = nodeOfVal[k];
            int x = getIndex(u);       // k 的当前位置
            int aK = (k - x) % k;      // 计算右移步数
            a[k] = aK;
            // 循环右移前缀 [1..k] 共 aK 步
            if (aK > 0) {
                pair<Node*, Node*> sp1 = split(root, k - aK);
                root = merge(sp1.second, sp1.first);
                if (root) root->p = nullptr;
            }
            // 移除已归位的元素 k（当前序列末尾）
            pair<Node*, Node*> sp2 = split(root, k - 1);
            root = sp2.first;
            if (root) root->p = nullptr;
            // 可选释放 k 对应节点：delete sp2.second;
        }
        // 输出结果
        for (int i = 1; i <= n; ++i) {
            if (i > 1) cout << ' ';
            cout << a[i];
        }
        cout << '\n';
        // 释放本测试用例分配的内存
        for (int i = 1; i <= n; ++i) delete nodeOfVal[i];
    }
    return 0;
}
