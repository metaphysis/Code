// Parse Tree
// UVa ID: 10467
// Verdict: Accepted
// Submission Date: 2026-07-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Node {
    char label;
    vector<Node*> children;
    int col;
    int depth;
    Node(char c) : label(c), col(0), depth(0) {}
};

string expr;
int pos;

Node* parseF();
Node* parseT();
Node* parseE();

// F → i | (E)
Node* parseF() {
    if (expr[pos] == 'i') {
        Node* f = new Node('F');
        f->children.push_back(new Node('i'));
        ++pos;
        return f;
    } else { // '('
        ++pos;
        Node* e = parseE();
        ++pos; // ')'
        Node* f = new Node('F');
        f->children.push_back(new Node('('));
        f->children.push_back(e);
        f->children.push_back(new Node(')'));
        return f;
    }
}

// T → T * F | T / F | T → F  （总是先应用 T → F，再处理运算符）
Node* parseT() {
    Node* left = parseF();                // 左部为 F
    Node* cur = new Node('T');            // 应用 T → F
    cur->children.push_back(left);
    while (pos < (int)expr.size() && (expr[pos] == '*' || expr[pos] == '/')) {
        char op = expr[pos++];
        Node* right = parseF();           // 右部为 F
        Node* t = new Node('T');          // 应用 T → T * F 或 T → T / F
        t->children.push_back(cur);       // 左子节点为已有的 T
        t->children.push_back(new Node(op));
        t->children.push_back(right);
        cur = t;
    }
    return cur;
}

// E → E + T | E - T | E → T  （总是先应用 E → T，再处理运算符）
Node* parseE() {
    Node* left = parseT();                // 左部为 T
    Node* cur = new Node('E');            // 应用 E → T
    cur->children.push_back(left);
    while (pos < (int)expr.size() && (expr[pos] == '+' || expr[pos] == '-')) {
        char op = expr[pos++];
        Node* right = parseT();           // 右部为 T
        Node* e = new Node('E');          // 应用 E → E + T 或 E → E - T
        e->children.push_back(cur);       // 左子节点为已有的 E
        e->children.push_back(new Node(op));
        e->children.push_back(right);
        cur = e;
    }
    return cur;
}

// 中序遍历收集所有叶子（终结符）
void collectLeaves(Node* node, vector<Node*>& leaves) {
    if (node->children.empty()) {
        leaves.push_back(node);
        return;
    }
    for (Node* ch : node->children) collectLeaves(ch, leaves);
}

// 后序遍历计算深度和列（列取所有子结点列的中位数）
void calcColsAndDepth(Node* node, int depth, int& maxDepth) {
    node->depth = depth;
    maxDepth = max(maxDepth, depth);
    if (node->children.empty()) return;
    for (Node* ch : node->children) calcColsAndDepth(ch, depth + 1, maxDepth);
    vector<int> childCols;
    for (Node* ch : node->children) childCols.push_back(ch->col);
    sort(childCols.begin(), childCols.end());
    // 子结点数总为 1 或 3，取中位数
    node->col = childCols[childCols.size() / 2];
}

// 按深度填充输出字符数组
void fillTree(Node* node, vector<string>& lines) {
    int symRow = node->depth * 2;          // 符号行
    int barRow = symRow + 1;               // '=' 行（含 '|'）
    lines[symRow][node->col] = node->label;
    if (node->children.empty()) return;
    int mn = INT_MAX, mx = INT_MIN;
    for (Node* ch : node->children) {
        mn = min(mn, ch->col);
        mx = max(mx, ch->col);
    }
    for (int c = mn; c <= mx; ++c)
        lines[barRow][c] = '=';
    lines[barRow][node->col] = '|';
    for (Node* ch : node->children) fillTree(ch, lines);
}

int main() {
    bool firstCase = true;
    while (getline(cin, expr)) {
        if (expr.empty()) continue;
        pos = 0;
        Node* root = parseE();
        // 1. 收集叶子并分配列（0 基，对应输出第 1、4、7…列）
        vector<Node*> leaves;
        collectLeaves(root, leaves);
        for (int i = 0; i < (int)leaves.size(); ++i) leaves[i]->col = i * 3;
        // 2. 计算内部结点列和最大深度
        int maxDepth = 0;
        calcColsAndDepth(root, 0, maxDepth);
        // 3. 最大列索引（最后一叶的列）
        int maxCol = leaves.empty() ? 0 : leaves.back()->col;
        // 4. 初始化输出行（总行数 = 2 * maxDepth + 1）
        int totalRows = 2 * maxDepth + 1;
        vector<string> lines(totalRows, string(maxCol + 1, ' '));
        // 5. 填充树
        fillTree(root, lines);
        // 6. 输出，两个用例间空行
        if (!firstCase) cout << '\n';
        firstCase = false;
        for (const string& line : lines) {
            int end = (int)line.size() - 1;
            while (end >= 0 && line[end] == ' ') --end;
            if (end >= 0) cout << line.substr(0, end + 1) << '\n';
        }
    }
    return 0;
}
