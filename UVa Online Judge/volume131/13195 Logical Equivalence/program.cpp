#include <bits/stdc++.h>
using namespace std;

struct Node {
    char kind;
    int left, right, var;
};

class ExprParser {
private:
    string text;
    int pos;
    vector<Node> &tree;
    array<int, 26> &varId;

    int addNode(char kind, int left, int right, int var) {
        tree.push_back({kind, left, right, var});
        return (int)tree.size() - 1;
    }

    int parsePrimary() {
        if (text[pos] == '(') {
            pos++;
            int result = parseOr();
            pos++;
            return result;
        }
        int result = addNode('v', -1, -1, varId[text[pos] - 'a']);
        pos++;
        return result;
    }

    int parseUnary() {
        if (text[pos] == '~') {
            pos++;
            int child = parseUnary();
            return addNode('~', child, -1, -1);
        }
        return parsePrimary();
    }

    int parseAnd() {
        int result = parseUnary();
        while (pos < (int)text.size() && text[pos] == '&') {
            pos++;
            int right = parseUnary();
            result = addNode('&', result, right, -1);
        }
        return result;
    }

    int parseXor() {
        int result = parseAnd();
        while (pos < (int)text.size() && text[pos] == '^') {
            pos++;
            int right = parseAnd();
            result = addNode('^', result, right, -1);
        }
        return result;
    }

    int parseOr() {
        int result = parseXor();
        while (pos < (int)text.size() && text[pos] == '|') {
            pos++;
            int right = parseXor();
            result = addNode('|', result, right, -1);
        }
        return result;
    }

public:
    ExprParser(const string &value, int start, vector<Node> &nodes, array<int, 26> &ids) : text(value), pos(start), tree(nodes), varId(ids) {
    }

    int parseExpression() {
        return parseOr();
    }

    int getPosition() {
        return pos;
    }
};

bool evaluate(int index, int mask, const vector<Node> &tree) {
    const Node &node = tree[index];
    if (node.kind == 'v')
        return (mask >> node.var) & 1;
    if (node.kind == '~')
        return !evaluate(node.left, mask, tree);
    bool leftValue = evaluate(node.left, mask, tree), rightValue = evaluate(node.right, mask, tree);
    if (node.kind == '&')
        return leftValue && rightValue;
    if (node.kind == '^')
        return leftValue ^ rightValue;
    return leftValue || rightValue;
}

string filterText(const string &line) {
    string result;
    for (char ch : line)
        if (isalpha(ch) || ch == '|' || ch == '&' || ch == '^' || ch == '~' || ch == '(' || ch == ')')
            result += ch;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    string line;
    getline(cin, line);
    while (testCount--) {
        getline(cin, line);
        string text = filterText(line);
        array<int, 26> varId;
        varId.fill(-1);
        int varCount = 0;
        for (char ch : text)
            if (varId[ch - 'a'] == -1)
                varId[ch - 'a'] = varCount++;
        vector<Node> tree;
        ExprParser parser(text, 0, tree, varId);
        int firstRoot = parser.parseExpression();
        int splitPosition = parser.getPosition();
        int secondRoot = parser.parseExpression();
        bool equivalent = true;
        int totalAssignment = 1 << varCount;
        for (int mask = 0; mask < totalAssignment; mask++) {
            if (evaluate(firstRoot, mask, tree) != evaluate(secondRoot, mask, tree)) {
                equivalent = false;
                break;
            }
        }
        cout << (equivalent ? "Yes" : "No") << '\n';
    }
    return 0;
}
