#include <bits/stdc++.h>
using namespace std;

struct Val {
    bool num;
    long long x;
    string s;
};

struct Table {
    string name;
    vector<string> cols;
    vector<char> typ;
    vector<vector<Val>> rows;
    unordered_map<string, int> pos;
};

struct Tok {
    string s;
    bool str;
};

struct Item {
    bool name;
    string col;
    Val val;
};

struct Node {
    int kind;
    string op;
    Item a, b;
    Node *left, *right;
};

struct Ord {
    string col;
    bool down;
};

unordered_map<string, Table> tabs;
vector<Tok> toks;
int curPos;

string lowerStr(string s) {
    for (char &c : s) c = (char)tolower((unsigned char)c);
    return s;
}

bool isBlank(const string &s) {
    return s.find_first_not_of(" \t\r") == string::npos;
}

bool isNum(const string &s) {
    int n = (int)s.size(), p = 0;
    if (n == 0) return false;
    if (s[p] == '+' || s[p] == '-') p++;
    if (p == n) return false;
    for (; p < n; p++)
        if (!isdigit((unsigned char)s[p])) return false;
    return true;
}

bool isOp(const string &s) {
    return s == "=" || s == "<" || s == ">" || s == "<=" || s == ">=" || s == "<>";
}

bool isWord(char c) {
    return isalnum((unsigned char)c) || c == '_';
}

vector<Tok> tokenize(const string &s) {
    vector<Tok> res;
    int n = (int)s.size(), i = 0;
    while (i < n) {
        if (isspace((unsigned char)s[i])) {
            i++;
        } else if (s[i] == '"') {
            string t;
            i++;
            while (i < n && s[i] != '"') {
                if (s[i] == '\\' && i + 1 < n) {
                    t += s[i + 1];
                    i += 2;
                } else {
                    t += s[i++];
                }
            }
            if (i < n) i++;
            res.push_back({t, true});
        } else if (isalpha((unsigned char)s[i]) || s[i] == '_') {
            string t;
            while (i < n && isWord(s[i])) t += s[i++];
            res.push_back({t, false});
        } else if (isdigit((unsigned char)s[i]) || ((s[i] == '+' || s[i] == '-') && i + 1 < n && isdigit((unsigned char)s[i + 1]))) {
            string t;
            t += s[i++];
            while (i < n && isdigit((unsigned char)s[i])) t += s[i++];
            res.push_back({t, false});
        } else {
            string t;
            t += s[i++];
            if (i < n && ((t == "<" && (s[i] == '=' || s[i] == '>')) || (t == ">" && s[i] == '='))) t += s[i++];
            res.push_back({t, false});
        }
    }
    return res;
}

string readQuery() {
    string res, line;
    while (getline(cin, line)) {
        if (!isBlank(line)) {
            res = line;
            break;
        }
    }
    while (getline(cin, line)) {
        if (isBlank(line)) break;
        res += ' ';
        res += line;
    }
    return res;
}

bool accept(const string &s) {
    if (curPos < (int)toks.size() && lowerStr(toks[curPos].s) == lowerStr(s)) {
        curPos++;
        return true;
    }
    return false;
}

string take() {
    if (curPos >= (int)toks.size()) return "";
    return toks[curPos++].s;
}

int findCol(const Table &tab, const string &name) {
    return tab.pos.at(lowerStr(name));
}

bool sameVal(const Val &a, const Val &b) {
    if (a.num != b.num) return false;
    if (a.num) return a.x == b.x;
    return a.s == b.s;
}

Table joinTab(const Table &a, const Table &b, const string &ca, const string &cb) {
    Table res;
    int ia = findCol(a, ca), ib = findCol(b, cb);
    res.cols = a.cols;
    res.cols.insert(res.cols.end(), b.cols.begin(), b.cols.end());
    res.typ = a.typ;
    res.typ.insert(res.typ.end(), b.typ.begin(), b.typ.end());
    for (int i = 0; i < (int)res.cols.size(); i++) res.pos[lowerStr(res.cols[i])] = i;
    for (const vector<Val> &ra : a.rows) {
        for (const vector<Val> &rb : b.rows) {
            if (!sameVal(ra[ia], rb[ib])) continue;
            vector<Val> row = ra;
            row.insert(row.end(), rb.begin(), rb.end());
            res.rows.push_back(row);
        }
    }
    return res;
}

Table parseFrom();

Table parseInner() {
    if (accept("(")) {
        Table res = parseFrom();
        accept(")");
        return res;
    }
    return tabs.at(lowerStr(take()));
}

Table parseFrom() {
    Table res = parseInner();
    while (accept("INNER")) {
        accept("JOIN");
        Table right = parseInner();
        accept("ON");
        string leftCol = take();
        accept("=");
        string rightCol = take();
        res = joinTab(res, right, leftCol, rightCol);
    }
    return res;
}

Item parseItem() {
    Item res;
    Tok t = toks[curPos++];
    if (t.str) {
        res.name = false;
        res.val = {false, 0, t.s};
    } else if (isNum(t.s)) {
        res.name = false;
        res.val = {true, stoll(t.s), ""};
    } else {
        res.name = true;
        res.col = t.s;
    }
    return res;
}

Node *newNode(int kind) {
    Node *p = new Node;
    p->kind = kind;
    p->left = nullptr;
    p->right = nullptr;
    return p;
}

Node *parseExpr();

Node *parseUnary() {
    bool isNot = curPos < (int)toks.size() && lowerStr(toks[curPos].s) == "not";
    bool isColumn = curPos + 1 < (int)toks.size() && isOp(toks[curPos + 1].s);
    if (isNot && !isColumn) {
        curPos++;
        Node *p = newNode(1);
        p->left = parseUnary();
        return p;
    }
    if (accept("(")) {
        Node *p = parseExpr();
        accept(")");
        return p;
    }
    Node *p = newNode(0);
    p->a = parseItem();
    if (curPos < (int)toks.size() && isOp(toks[curPos].s)) p->op = take();
    else p->op = "=";
    p->b = parseItem();
    return p;
}

Node *parseExpr() {
    Node *res = parseUnary();
    while (curPos < (int)toks.size()) {
        string op = lowerStr(toks[curPos].s);
        if (op != "and" && op != "or") break;
        curPos++;
        Node *p = newNode(op == "and" ? 2 : 3);
        p->left = res;
        p->right = parseUnary();
        res = p;
    }
    return res;
}

Val getVal(const Item &item, const Table &tab, const vector<Val> &row) {
    if (item.name) return row[findCol(tab, item.col)];
    return item.val;
}

bool cmpVal(const Val &a, const Val &b, const string &op) {
    if (a.num) {
        if (op == "=") return a.x == b.x;
        if (op == "<") return a.x < b.x;
        if (op == ">") return a.x > b.x;
        if (op == "<=") return a.x <= b.x;
        if (op == ">=") return a.x >= b.x;
        return a.x != b.x;
    }
    if (op == "=") return a.s == b.s;
    if (op == "<") return a.s < b.s;
    if (op == ">") return a.s > b.s;
    if (op == "<=") return a.s <= b.s;
    if (op == ">=") return a.s >= b.s;
    return a.s != b.s;
}

bool eval(Node *p, const Table &tab, const vector<Val> &row) {
    if (p->kind == 0) return cmpVal(getVal(p->a, tab, row), getVal(p->b, tab, row), p->op);
    if (p->kind == 1) return !eval(p->left, tab, row);
    if (p->kind == 2) return eval(p->left, tab, row) && eval(p->right, tab, row);
    return eval(p->left, tab, row) || eval(p->right, tab, row);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int tc = 0; tc < testCount; tc++) {
        int tableCount;
        cin >> tableCount;
        tabs.clear();
        for (int i = 0; i < tableCount; i++) {
            Table tab;
            int m, n;
            cin >> tab.name >> m >> n;
            tab.cols.resize(m);
            tab.typ.resize(m);
            for (int j = 0; j < m; j++) {
                cin >> tab.cols[j] >> tab.typ[j];
                tab.pos[lowerStr(tab.cols[j])] = j;
            }
            tab.rows.resize(n, vector<Val>(m));
            for (int r = 0; r < n; r++) {
                for (int j = 0; j < m; j++) {
                    string value;
                    cin >> value;
                    if (tab.typ[j] == 'I') tab.rows[r][j] = {true, stoll(value), ""};
                    else tab.rows[r][j] = {false, 0, value};
                }
            }
            tabs[lowerStr(tab.name)] = tab;
        }
        string line;
        getline(cin, line);
        string query = readQuery();
        toks = tokenize(query);
        curPos = 0;
        accept("SELECT");
        bool all = false;
        vector<string> selected;
        if (accept("*")) {
            all = true;
        } else {
            while (true) {
                selected.push_back(take());
                if (!accept(",")) break;
            }
        }
        accept("FROM");
        Table searchTab = parseFrom();
        Node *root = nullptr;
        if (accept("WHERE")) root = parseExpr();
        vector<Ord> orders;
        if (accept("ORDER")) {
            accept("BY");
            while (true) {
                Ord ord;
                ord.col = take();
                ord.down = false;
                if (accept("DESCENDING")) ord.down = true;
                else accept("ASCENDING");
                orders.push_back(ord);
                if (!accept(",")) break;
            }
        }
        vector<vector<Val>> result;
        for (const vector<Val> &row : searchTab.rows)
            if (root == nullptr || eval(root, searchTab, row)) result.push_back(row);
        stable_sort(result.begin(), result.end(), [&](const vector<Val> &a, const vector<Val> &b) {
            for (const Ord &ord : orders) {
                Val x = a[findCol(searchTab, ord.col)];
                Val y = b[findCol(searchTab, ord.col)];
                bool less, greater;
                if (x.num) {
                    less = x.x < y.x;
                    greater = x.x > y.x;
                } else {
                    less = x.s < y.s;
                    greater = x.s > y.s;
                }
                if (less) return !ord.down;
                if (greater) return ord.down;
            }
            return false;
        });
        vector<int> outputCols;
        if (all) {
            for (int i = 0; i < (int)searchTab.cols.size(); i++) outputCols.push_back(i);
        } else {
            for (const string &name : selected) outputCols.push_back(findCol(searchTab, name));
        }
        if (tc) cout << '\n';
        cout << outputCols.size() << ' ' << result.size() << '\n';
        for (int col : outputCols) cout << searchTab.cols[col] << '\n';
        for (const vector<Val> &row : result) {
            for (int i = 0; i < (int)outputCols.size(); i++) {
                if (i) cout << ' ';
                const Val &value = row[outputCols[i]];
                if (value.num) cout << value.x;
                else cout << value.s;
            }
            cout << '\n';
        }
    }
    return 0;
}
