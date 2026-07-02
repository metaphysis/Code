// Gaston
// UVa ID: 564
// Verdict: Accepted
// Submission Date: 2026-06-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left, *right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// 递归计算子树大小（不依赖存储字段，实时计算）
int getSize(Node *p) {
    if (!p) return 0;
    return 1 + getSize(p->left) + getSize(p->right);
}

// BST 插入（不更新 size）
void insertBST(Node *&p, int v) {
    if (!p) { p = new Node(v); return; }
    if (v < p->val) insertBST(p->left, v);
    else insertBST(p->right, v);
}

// 寻找子树中的最小节点
Node* findMin(Node *p) {
    while (p && p->left) p = p->left;
    return p;
}

// 寻找子树中的最大节点
Node* findMax(Node *p) {
    while (p && p->right) p = p->right;
    return p;
}

// 删除子树中的最小节点（并释放内存）
void deleteMin(Node *&p) {
    if (!p) return;
    if (!p->left) {
        Node *tmp = p;
        p = p->right;
        delete tmp;
    } else {
        deleteMin(p->left);
    }
}

// 删除子树中的最大节点
void deleteMax(Node *&p) {
    if (!p) return;
    if (!p->right) {
        Node *tmp = p;
        p = p->left;
        delete tmp;
    } else {
        deleteMax(p->right);
    }
}

// 将值 v 插入到子树 p 中的最大位置（作为最右节点）
void insertMax(Node *&p, int v) {
    if (!p) { p = new Node(v); return; }
    if (!p->right) p->right = new Node(v);
    else insertMax(p->right, v);
}

// 将值 v 插入到子树 p 中的最小位置（作为最左节点）
void insertMin(Node *&p, int v) {
    if (!p) { p = new Node(v); return; }
    if (!p->left) p->left = new Node(v);
    else insertMin(p->left, v);
}

// 对单个节点执行一次平衡步骤，返回是否执行了操作
bool balanceNode(Node *&p) {
    if (!p) return false;
    int L = getSize(p->left);
    int R = getSize(p->right);

    // 右侧过重（左 < 右）
    if (L < R) {
        Node *minNode = findMin(p->right);
        int oldVal = p->val;
        int newVal = minNode->val;
        deleteMin(p->right);          // 移除重侧的最小节点
        p->val = newVal;              // 将其值赋给当前节点
        insertMax(p->left, oldVal);   // 旧值插入轻侧（最大位置）
        return true;
    }
    // 左侧过重（左 > 右 + 1）
    else if (L > R + 1) {
        Node *maxNode = findMax(p->left);
        int oldVal = p->val;
        int newVal = maxNode->val;
        deleteMax(p->left);           // 移除重侧的最大节点
        p->val = newVal;              // 将其值赋给当前节点
        insertMin(p->right, oldVal);  // 旧值插入轻侧（最小位置）
        return true;
    }
    return false;
}

// 从当前节点开始，按根、左、右顺序检查并执行一次平衡，返回是否执行
bool balanceCheck(Node *&p) {
    if (!p) return false;
    if (balanceNode(p)) return true;
    if (balanceCheck(p->left)) return true;
    if (balanceCheck(p->right)) return true;
    return false;
}

// 读取树的先序表示（0 表示空）
void readTree(Node *&p) {
    int x;
    cin >> x;
    if (x == 0) { p = nullptr; return; }
    p = new Node(x);
    readTree(p->left);
    readTree(p->right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        Node *root = nullptr;
        readTree(root);

        int steps = 0;

        int b;
        cin >> b;
        for (int i = 0; i < b; ++i) {
            int val;
            cin >> val;
            insertBST(root, val);
            // 插入后反复平衡直至整棵树满足条件
            while (balanceCheck(root)) ++steps;
        }

        cout << steps << '\n';
        // 此处可递归释放内存，但非必须
    }
    return 0;
}
