[UVa 112 Tree Summing](https://blog.csdn.net/metaphysis/article/details/156641586)

## 问题描述

本题给定一系列用 $\texttt{LISP}$ $\texttt{S-}$表达式表示的二叉树，要求判断对于每棵树，是否存在从根结点到某个叶结点的路径，使得路径上所有结点值的和等于给定的目标整数。

例如，对于表达式：

```
(5 (4 (11 (7 () ()) (2 () ()) ) ()) (8 (13 () ()) (4 () (1 () ()) ) ))
```

该树对应的结构如下图所示（见题目原文），共有四条根到叶子的路径，其路径和分别为 $27$、$22$、$26$ 和 $18$。

输入中包含多个测试用例，每个测试用例由一个整数（目标值）和一个合法的 $\texttt{S‑}$表达式组成。表达式可以跨越多行，且可以包含空白字符。对于每个测试用例，如果存在一条根到叶子的路径和等于目标整数，则输出 `yes` ，否则输出 `no`。

---

## 题目分析与解题思路

### 1. 输入格式与解析

$\texttt{S-}$表达式的语法定义如下：

- 空树： `()`
- 树：可以是空树，也可以是 `(整数 左子树 右子树)`。

例如，`(5 (4 () ()) (3 () ()))` 表示一个根结点值为 $5$，左子树是一个值为 $4$ 的叶子，右子树是一个值为 $3$ 的叶子的二叉树。

**输入特点**：
- 表达式可以跨行、带空格，但一定是合法格式。
- 每个测试用例的格式是：一个整数，然后是一个 $\texttt{S‑}$表达式。
- 输入以 $\texttt{EOF}$ 结束。

### 2. 核心思路

本题的本质是一个 **树上的路径搜索问题**。由于需要判断是否存在从根到叶子的路径和等于给定值，我们可以采用 **深度优先搜索（$\texttt{DFS}$）** 的思路，在递归构建树的同时，累加路径和，并在到达叶子结点时进行比较。

具体步骤：
1. 递归解析 $\texttt{S‑}$表达式，同时构建二叉树。
2. 在递归过程中，从根结点开始，将当前结点的值加到从根到当前结点的路径和上，并传递给子结点。
3. 当遇到叶子结点（即左右子树均为空）时，检查累计和是否等于目标值。
4. 若任意一条路径满足条件，则标记存在（`exist = true`），并在后续递归中尽早终止（剪枝）。

### 3. 实现细节

- **树的表示**：使用结构体 `TreeNode`，包含 `weight`（结点值）、`parent`、`leftChild`、`rightChild`。
- **解析过程**：
  - 每次遇到 `(` 开始解析一个结点。
  - 如果下一个字符是数字或负号，则读取整数值，创建结点；否则遇到 `()` 表示空树，需要将该子树从父结点中删除（置为 `NULL`）。
  - 递归解析左右子树。
  - 遇到 `)` 结束当前子树解析。
- **路径和累加**：可以在解析完成后进行一次后序遍历，将父结点的 `weight` 累加到子结点上（`summing` 函数），也可以在递归解析时直接传递累加和。
- **搜索判断**：遍历所有叶子结点，检查其 `weight`（此时已是从根到该叶子的路径和）是否等于目标值。

### 4. 边界情况

- **空树**：题目明确说明，空树没有任何根到叶子的路径，因此对于任意目标值都应输出 `no`。
- **负数和零**：结点值可以是负数，目标值也可以是负数或零，累加过程需正确处理符号。
- **大数**：虽然题目未明确数值范围，但一般整数范围在 $32$ 位有符号整数内，累加和不会溢出。

### 5. 复杂度分析

- 时间复杂度：$O(N)$，其中 $N$ 为树的结点数。每个结点仅被访问常数次。
- 空间复杂度：$O(N)$，用于存储树结构。

---

## 参考代码

```cpp
// Tree Summing
// UVa ID: 112
// Verdict: Accepted
// Submission Date: 2017-05-08
// UVa Run Time: 0.030s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int weight;
    TreeNode *parent, *leftChild, *rightChild;
};

bool exist, empty;

void summing(TreeNode *node) {
    if (node->leftChild != NULL) {
        node->leftChild->weight += node->weight;
        summing(node->leftChild);
    }
    if (node->rightChild != NULL) {
        node->rightChild->weight += node->weight;
        summing(node->rightChild);
    }
}

void parse(TreeNode *node) {
    bool isLeaf = false;
    char c;
    while (cin >> c, c != '(') { }
    cin >> c;
    if (isdigit(c) || c == '-') {
        int sign = (c == '-' ? (-1) : 1), number = 0;
        if (isdigit(c)) number = c - '0';
        while (cin >> c, isdigit(c)) number *= 10, number += (c - '0');
        cin.putback(c);
        node->weight = number * sign;
    } else {
        cin.putback(c);
        if (node->parent != NULL) {
            if (node == node->parent->leftChild) node->parent->leftChild = NULL;
            else node->parent->rightChild = NULL;
        } else empty = true;
        isLeaf = true;
    }
    if (!isLeaf) {
        TreeNode *left = new TreeNode;
        node->leftChild = left;
        left->parent = node;
        parse(left);
        TreeNode *right = new TreeNode;
        node->rightChild = right;
        right->parent = node;
        parse(right);
    }
    while (cin >> c, c != ')') { }
}

void traversal(TreeNode *node, int sum) {
    if (exist) return;
    if (node->leftChild == NULL && node->rightChild == NULL)
        if (node->weight == sum)
            exist = true;
    if (node->leftChild != NULL) traversal(node->leftChild, sum);
    if (node->rightChild != NULL) traversal(node->rightChild, sum);
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int sum;
    while (cin >> sum) {
        empty = false, exist = false;
        TreeNode *root = new TreeNode;
        parse(root);
        summing(root);
        if (!empty) traversal(root, sum);
        cout << (exist ? "yes" : "no") << '\n';
        delete root;
    }
    return 0;
}
```

---

## 总结

本题考察了递归解析特定格式输入（$\texttt{LISP S‑}$表达式）的能力以及树上的 $\texttt{DFS}$ 路径搜索。关键点在于正确处理输入中的括号和空格，并在构建树的同时或之后进行路径和的计算与判断。使用递归方法可以很自然地匹配 $\texttt{S‑}$表达式的嵌套结构，实现简洁且高效。
