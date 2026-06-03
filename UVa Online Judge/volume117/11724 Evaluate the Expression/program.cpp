// Evaluate the Expression
// UVa ID: 11724
// Verdict: Accepted
// Submission Date: 2026-06-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 表达式节点类型
enum NodeType { VAR, ADD, MUL };

struct ExprNode {
    NodeType type;
    char var;                     // 当 type == VAR 时有效
    ExprNode *left, *right;       // 当 type == ADD 或 MUL 时有效
    ExprNode(char v) : type(VAR), var(v), left(nullptr), right(nullptr) {}
    ExprNode(NodeType t, ExprNode *l, ExprNode *r) : type(t), left(l), right(r), var(0) {}
};

// 解析表达式（递归下降）
ExprNode* parseExpr(const string &s, int &pos);
ExprNode* parseTerm(const string &s, int &pos);
ExprNode* parseFactor(const string &s, int &pos);

ExprNode* parseExpr(const string &s, int &pos) {
    ExprNode *node = parseTerm(s, pos);
    while (pos < (int)s.size() && s[pos] == '+') {
        pos++; // 跳过 '+'
        ExprNode *right = parseTerm(s, pos);
        node = new ExprNode(ADD, node, right);
    }
    return node;
}

ExprNode* parseTerm(const string &s, int &pos) {
    ExprNode *node = parseFactor(s, pos);
    while (pos < (int)s.size() && s[pos] == '*') {
        pos++; // 跳过 '*'
        ExprNode *right = parseFactor(s, pos);
        node = new ExprNode(MUL, node, right);
    }
    return node;
}

ExprNode* parseFactor(const string &s, int &pos) {
    if (s[pos] == '(') {
        pos++; // 跳过 '('
        ExprNode *node = parseExpr(s, pos);
        pos++; // 跳过 ')'
        return node;
    } else {
        // 变量
        return new ExprNode(s[pos++]);
    }
}

// 收集表达式中的所有变量
void collectVars(ExprNode *root, set<char> &vars) {
    if (root->type == VAR) {
        vars.insert(root->var);
    } else {
        collectVars(root->left, vars);
        collectVars(root->right, vars);
    }
}

// 计算表达式的值
int evalExpr(ExprNode *root, map<char, int> &val) {
    if (root->type == VAR) return val[root->var];
    int leftVal = evalExpr(root->left, val);
    int rightVal = evalExpr(root->right, val);
    if (root->type == ADD) return leftVal + rightVal;
    else return leftVal * rightVal;
}

// 释放表达式树内存
void freeExpr(ExprNode *root) {
    if (root->type != VAR) {
        freeExpr(root->left);
        freeExpr(root->right);
    }
    delete root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    cin.ignore(); // 忽略换行

    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        string expr;
        getline(cin, expr);

        int I;
        cin >> I;
        cin.ignore();

        // 建图：graph[u] 表示 u 大于哪些节点
        vector<vector<char>> graph(26);
        vector<int> indeg(26, -1); // -1 表示该变量未出现

        set<char> varsSet;
        // 先收集表达式中的变量
        int pos = 0;
        ExprNode *root = parseExpr(expr, pos);
        collectVars(root, varsSet);

        for (char v : varsSet) indeg[v - 'a'] = 0;

        bool consistent = true;

        for (int i = 0; i < I; ++i) {
            string line;
            getline(cin, line);
            if (!consistent) continue;

            char x = line[0], y = line[2];
            // x > y  =>  y -> x   (x 至少是 y+1)
            // 但注意：x 和 y 必须出现在表达式中，题目保证如此
            if (indeg[x - 'a'] == -1 || indeg[y - 'a'] == -1) continue;

            graph[y - 'a'].push_back(x);
            indeg[x - 'a']++;
        }

        // 拓扑排序求最小赋值
        queue<char> q;
        map<char, int> val;
        for (char v : varsSet) {
            if (indeg[v - 'a'] == 0) {
                q.push(v);
                val[v] = 1;
            }
        }

        int processed = 0;
        while (!q.empty()) {
            char u = q.front(); q.pop();
            processed++;

            for (char v : graph[u - 'a']) {
                // v 至少比 u 大 1
                val[v] = max(val[v], val[u] + 1);
                indeg[v - 'a']--;
                if (indeg[v - 'a'] == 0) q.push(v);
            }
        }

        if (processed != (int)varsSet.size()) {
            consistent = false;
        }

        if (!consistent) {
            cout << "Case " << caseNum << ": -1\n";
        } else {
            int result = evalExpr(root, val);
            cout << "Case " << caseNum << ": " << result << "\n";
        }

        freeExpr(root);
    }

    return 0;
}
