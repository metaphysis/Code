// Structural Equivalence
// UVa ID: 10904
// Verdict: Accepted
// Submission Date: 2026-06-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

enum Prim { INT, REAL, CHAR };

struct Expr {
    enum Kind { PRIM, STRUCT, REF } kind;
    Prim prim;
    vector<char> fields;
    char ref;
};

struct Node {
    enum Kind { PRIMITIVE, STRUCT } kind;
    Prim prim;
    vector<Node*> fields;
};

struct DSU {
    int p[26];
    DSU() { for (int i = 0; i < 26; ++i) p[i] = i; }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) { p[find(a)] = find(b); }
};

string trim(const string& s) {
    size_t l = s.find_first_not_of(" \t"), r = s.find_last_not_of(" \t");
    return l == string::npos ? "" : s.substr(l, r - l + 1);
}

// 解析一行定义，成功返回 true
bool parseLine(const string& line, char& name, Expr& expr) {
    int i = 0, n = line.size();
    while (i < n && isspace(line[i])) ++i;
    if (line.compare(i, 4, "type") != 0) return false;
    i += 4;
    while (i < n && isspace(line[i])) ++i;
    if (i >= n || !isupper(line[i])) return false;
    name = line[i++];
    while (i < n && isspace(line[i])) ++i;
    if (i >= n || line[i] != '=') return false;
    ++i;
    while (i < n && isspace(line[i])) ++i;

    if (line.compare(i, 6, "struct") == 0) {
        i += 6;
        while (i < n && isspace(line[i])) ++i;
        if (i >= n || line[i] != '(') return false;
        ++i;
        expr.kind = Expr::STRUCT;
        expr.fields.clear();
        while (i < n && line[i] != ')') {
            while (i < n && isspace(line[i])) ++i;
            if (i < n && line[i] == ')') break;
            if (i < n && isupper(line[i])) { expr.fields.push_back(line[i++]); }
            else return false;
        }
        if (i >= n || line[i] != ')') return false;
        return true;
    }
    if (line.compare(i, 3, "int") == 0) { expr.kind = Expr::PRIM; expr.prim = INT; return true; }
    if (line.compare(i, 4, "real") == 0) { expr.kind = Expr::PRIM; expr.prim = REAL; return true; }
    if (line.compare(i, 4, "char") == 0) { expr.kind = Expr::PRIM; expr.prim = CHAR; return true; }
    if (i < n && isupper(line[i])) { expr.kind = Expr::REF; expr.ref = line[i]; return true; }
    return false;
}

// 递归比较两个结构节点是否等价，visiting 记录当前路径避免循环
bool equiv(Node* a, Node* b, set<pair<Node*, Node*>>& vis) {
    if (a == b) return true;
    if (a->kind != b->kind) return false;
    if (a->kind == Node::PRIMITIVE) return a->prim == b->prim;
    if (a->fields.size() != b->fields.size()) return false;
    Node *p1 = min(a, b), *p2 = max(a, b);
    auto key = make_pair(p1, p2);
    if (vis.count(key)) return true;
    vis.insert(key);
    for (size_t i = 0; i < a->fields.size(); ++i)
        if (!equiv(a->fields[i], b->fields[i], vis)) { vis.erase(key); return false; }
    vis.erase(key);
    return true;
}

void processCase(const vector<string>& lines) {
    Expr defs[26];        // 存储每个字母的定义
    bool hasDef[26] = {};
    for (const string& line : lines) {
        char name; Expr expr;
        if (parseLine(line, name, expr)) {
            defs[name - 'A'] = expr;
            hasDef[name - 'A'] = true;
        }
    }

    DSU dsu;              // 先用并查集合并显式引用
    for (int i = 0; i < 26; ++i)
        if (hasDef[i] && defs[i].kind == Expr::REF)
            dsu.unite(i, defs[i].ref - 'A');

    // 为每个并查集根创建节点（仅对非引用定义）
    Node* rootNode[26] = {};
    for (int i = 0; i < 26; ++i) {
        if (!hasDef[i]) continue;
        int r = dsu.find(i);
        if (rootNode[r]) continue;
        if (defs[i].kind == Expr::REF) continue;  // 引用不创建节点
        Node* nd = new Node;
        if (defs[i].kind == Expr::PRIM) {
            nd->kind = Node::PRIMITIVE;
            nd->prim = defs[i].prim;
        } else { // STRUCT
            nd->kind = Node::STRUCT;
            nd->fields.clear();
        }
        rootNode[r] = nd;
    }
    // 若某个根没有节点（全是引用链），则创建一个占位节点（实际不会发生）
    for (int i = 0; i < 26; ++i)
        if (rootNode[i] == nullptr && dsu.find(i) == i && hasDef[i]) {
            Node* nd = new Node;
            nd->kind = Node::PRIMITIVE;
            nd->prim = INT;
            rootNode[i] = nd;
        }

    // 填充结构体的字段指针
    for (int i = 0; i < 26; ++i) {
        if (!hasDef[i] || defs[i].kind != Expr::STRUCT) continue;
        int r = dsu.find(i);
        Node* nd = rootNode[r];
        if (nd && nd->kind == Node::STRUCT) {
            nd->fields.clear();
            for (char f : defs[i].fields) {
                int fr = dsu.find(f - 'A');
                if (rootNode[fr]) nd->fields.push_back(rootNode[fr]);
            }
        }
    }

    // 获取所有有定义的根
    vector<int> roots;
    for (int i = 0; i < 26; ++i)
        if (hasDef[i]) {
            int r = dsu.find(i);
            if (find(roots.begin(), roots.end(), r) == roots.end())
                roots.push_back(r);
        }

    // 在根之间进行结构等价比较，合并等价根
    for (size_t i = 0; i < roots.size(); ++i)
        for (size_t j = i + 1; j < roots.size(); ++j) {
            int ri = roots[i], rj = roots[j];
            if (dsu.find(ri) == dsu.find(rj)) continue;
            Node* ni = rootNode[ri], *nj = rootNode[rj];
            set<pair<Node*, Node*>> vis;
            if (equiv(ni, nj, vis))
                dsu.unite(ri, rj);
        }

    // 按最终根分组，输出
    map<int, vector<char>> groups;
    for (int i = 0; i < 26; ++i)
        if (hasDef[i])
            groups[dsu.find(i)].push_back(char('A' + i));

    vector<string> outLines;
    for (auto& kv : groups) {
        auto& v = kv.second;
        sort(v.begin(), v.end());
        string s;
        for (char c : v) { if (!s.empty()) s.push_back(' '); s.push_back(c); }
        outLines.push_back(s);
    }
    sort(outLines.begin(), outLines.end());

    for (size_t i = 0; i < outLines.size(); ++i) {
        if (i) cout << '\n';
        cout << outLines[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> caseLines;
    string line;
    bool first = true;
    while (getline(cin, line)) {
        string t = trim(line);
        if (t == "-" || t == "--") {
            if (!caseLines.empty()) {
                if (!first) cout << '\n';
                processCase(caseLines);
                cout << '\n';
                first = false;
                caseLines.clear();
            }
        } else if (!t.empty())
            caseLines.push_back(line);
    }
    return 0;
}
