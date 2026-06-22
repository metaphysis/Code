// Crazy Calculator
// UVa ID: 354
// Verdict: Wrong Answer
// Submission Date: 2026-06-21
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

unordered_map<char, char> localToStd;   // 本地符号 -> 标准运算符
unordered_map<char, int> localPrec;     // 本地符号 -> 优先级
unordered_map<char, char> localAssoc;   // 本地符号 -> 结合性

struct Node {
    int val;
    string stdExpr;
};

// 函数原型声明
int applyOp(int a, int b, char stdOp);
Node parsePrimary();
Node parseExpr(int minPrec);

string expr;
int pos, n;

int applyOp(int a, int b, char stdOp) {
    switch (stdOp) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b == 0) ? 0 : a / b;
    }
    return 0;
}

Node parsePrimary() {
    if (pos < n && expr[pos] == '(') {
        ++pos; // 跳过 '('
        Node inner = parseExpr(0);
        if (pos < n && expr[pos] == ')') ++pos;
        return {inner.val, "(" + inner.stdExpr + ")"};
    } else {
        int num = 0;
        while (pos < n && isdigit(expr[pos])) {
            num = num * 10 + (expr[pos] - '0');
            ++pos;
        }
        return {num, to_string(num)};
    }
}

Node parseExpr(int minPrec) {
    Node left = parsePrimary();
    while (pos < n && localToStd.find(expr[pos]) != localToStd.end()) {
        char op = expr[pos];
        int prec = localPrec[op];
        char assoc = localAssoc[op];
        if ((assoc == 'L' && prec < minPrec) || (assoc == 'R' && prec <= minPrec))
            break;
        ++pos; // 消费运算符
        Node right = parseExpr((assoc == 'L') ? prec + 1 : prec);
        int res = applyOp(left.val, right.val, localToStd[op]);
        string stdExpr = left.stdExpr + localToStd[op] + right.stdExpr;
        left = {res, stdExpr};
    }
    return left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    int T = stoi(line);
    getline(cin, line); // 空行

    for (int cs = 0; cs < T; ++cs) {
        if (cs) cout << '\n';
        localToStd.clear();
        localPrec.clear();
        localAssoc.clear();

        for (int k = 0; k < 4; ++k) {
            getline(cin, line);
            char stdOp = line[0];
            char localSym = line[1];
            int prec = line[2] - '0';
            char assoc = line[3];
            localToStd[localSym] = stdOp;
            localPrec[localSym] = prec;
            localAssoc[localSym] = assoc;
        }

        while (getline(cin, line)) {
            if (line.empty()) break;
            expr = line;
            pos = 0;
            n = expr.size();
            Node root = parseExpr(0);
            cout << root.stdExpr << " = " << root.val << '\n';
        }
    }

    return 0;
}
