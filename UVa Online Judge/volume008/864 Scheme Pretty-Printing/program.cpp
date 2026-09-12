#include <bits/stdc++.h>
using namespace std;

struct Node {
    bool atom;
    string val;
    vector<shared_ptr<Node>> son;
};

vector<string> tok, ans;
int pos;

shared_ptr<Node> parseExpr() {
    shared_ptr<Node> cur = make_shared<Node>();
    if (tok[pos] != "(") {
        cur->atom = true;
        cur->val = tok[pos++];
        return cur;
    }
    cur->atom = false;
    pos++;
    while (tok[pos] != ")")
        cur->son.push_back(parseExpr());
    pos++;
    return cur;
}

bool isName(const shared_ptr<Node> &cur, const string &s) {
    return cur->atom && cur->val == s;
}

bool hasList(const shared_ptr<Node> &cur) {
    for (auto x : cur->son)
        if (!x->atom) return true;
    return false;
}

string inlineText(const shared_ptr<Node> &cur) {
    if (cur->atom) return cur->val;
    string res = "(";
    for (int i = 0; i < (int)cur->son.size(); i++) {
        if (i) res += " ";
        res += inlineText(cur->son[i]);
    }
    return res + ")";
}

void putText(const string &s) {
    ans.back() += s;
}

void newLine(int sp) {
    ans.push_back(string(sp, ' '));
}

void printExpr(const shared_ptr<Node> &cur, int ind) {
    if (cur->atom) {
        putText(cur->val);
        return;
    }
    int n = cur->son.size(), col = ans.back().size();
    if (n == 0) {
        putText("()");
        return;
    }
    if (isName(cur->son[0], "define") && n == 3) {
        if (cur->son[2]->atom) {
            putText(inlineText(cur));
            return;
        }
        putText("(define ");
        printExpr(cur->son[1], col);
        newLine(col + 3);
        printExpr(cur->son[2], col + 3);
        putText(")");
        return;
    }
    if (isName(cur->son[0], "lambda") && n >= 2) {
        putText("(lambda ");
        printExpr(cur->son[1], col);
        for (int i = 2; i < n; i++) {
            newLine(col + 3);
            printExpr(cur->son[i], col + 3);
        }
        putText(")");
        return;
    }
    if (isName(cur->son[0], "if") && n >= 2) {
        putText("(if ");
        printExpr(cur->son[1], col);
        for (int i = 2; i < n; i++) {
            newLine(col + 4);
            printExpr(cur->son[i], col + 4);
        }
        putText(")");
        return;
    }
    if (!hasList(cur) || n < 2) {
        putText(inlineText(cur));
        return;
    }
    putText("(");
    printExpr(cur->son[0], col);
    putText(" ");
    int align = ans.back().size();
    printExpr(cur->son[1], col);
    for (int i = 2; i < n; i++) {
        newLine(align);
        printExpr(cur->son[i], align);
    }
    putText(")");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string all, line;
    while (getline(cin, line)) {
        all += line;
        all += '\n';
    }
    for (int i = 0; i < (int)all.size();) {
        if (isspace((unsigned char)all[i])) {
            i++;
            continue;
        }
        if (all[i] == '(' || all[i] == ')') {
            tok.push_back(string(1, all[i++]));
            continue;
        }
        if (all[i] == '"') {
            string s;
            bool esc = false;
            s += all[i++];
            while (i < (int)all.size()) {
                char c = all[i++];
                s += c;
                if (c == '"' && !esc) break;
                if (c == '\\' && !esc) esc = true;
                else esc = false;
            }
            tok.push_back(s);
            continue;
        }
        string s;
        while (i < (int)all.size() && !isspace((unsigned char)all[i]) && all[i] != '(' && all[i] != ')')
            s += all[i++];
        tok.push_back(s);
    }
    while (pos < (int)tok.size()) {
        ans.push_back("");
        printExpr(parseExpr(), 0);
    }
    for (const string &s : ans)
        cout << s << '\n';
    return 0;
}
