#include <bits/stdc++.h>
using namespace std;

struct Node {
    char type;
    string text;
    Node *left, *right;
    Node(char t, const string &s, Node *l = nullptr, Node *r = nullptr) {
        type = t;
        text = s;
        left = l;
        right = r;
    }
};

string expr;
int pos;

Node* makeNode(char type, const string &text, Node *left = nullptr, Node *right = nullptr) {
    return new Node(type, text, left, right);
}

Node* parseAdd();

Node* parsePrimary() {
    int start = pos;
    if (expr.compare(pos, 2, "ln") == 0) {
        pos += 2;
        pos++;
        Node *child = parseAdd();
        pos++;
        return makeNode('l', expr.substr(start, pos - start), child);
    }
    if (expr[pos] == '(') {
        pos++;
        Node *child = parseAdd();
        pos++;
        return makeNode('p', expr.substr(start, pos - start), child);
    }
    if (expr[pos] == 'x') {
        pos++;
        return makeNode('x', "x");
    }
    if (expr[pos] == '+' || expr[pos] == '-') pos++;
    while (pos < (int)expr.size() && (isdigit(expr[pos]) || expr[pos] == '.')) pos++;
    return makeNode('c', expr.substr(start, pos - start));
}

Node* parseMul() {
    Node *left = parsePrimary();
    while (pos < (int)expr.size() && (expr[pos] == '*' || expr[pos] == '/')) {
        char op = expr[pos++];
        Node *right = parsePrimary();
        left = makeNode(op, left->text + op + right->text, left, right);
    }
    return left;
}

Node* parseAdd() {
    Node *left = parseMul();
    while (pos < (int)expr.size() && (expr[pos] == '+' || expr[pos] == '-')) {
        char op = expr[pos++];
        Node *right = parseMul();
        left = makeNode(op, left->text + op + right->text, left, right);
    }
    return left;
}

string addExpr(const string &left, const string &right) {
    if (right[0] == '-') return left + right;
    if (right[0] == '+') return left + "+" + right.substr(1);
    return left + "+" + right;
}

string derive(Node *node) {
    if (node->type == 'x') return "1";
    if (node->type == 'c') return "0";
    if (node->type == 'p') return "(" + derive(node->left) + ")";
    if (node->type == 'l') return "(" + derive(node->left) + ")/(" + node->left->text + ")";
    string leftDer = derive(node->left), rightDer = derive(node->right);
    if (node->type == '+') return leftDer + "+" + rightDer;
    if (node->type == '-') return leftDer + "-" + rightDer;
    if (node->type == '*') {
        string first = leftDer + "*" + node->right->text;
        string second = node->left->text + "*" + rightDer;
        return "(" + addExpr(first, second) + ")";
    }
    return "(" + leftDer + "*" + node->right->text + "-" + node->left->text + "*" + rightDer + ")/" + node->right->text + "^2";
}

void deleteTree(Node *node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> expr) {
        pos = 0;
        Node *root = parseAdd();
        cout << derive(root) << '\n';
        deleteTree(root);
    }
    return 0;
}
