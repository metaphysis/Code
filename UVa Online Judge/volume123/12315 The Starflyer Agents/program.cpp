#include <bits/stdc++.h>
using namespace std;

struct Node {
    enum Type { VAR, CONST, FUNC };
    Type type;
    string name;
    vector<shared_ptr<Node>> args;
    Node(Type t, string n, vector<shared_ptr<Node>> a = {}) : type(t), name(n), args(a) {}
};

shared_ptr<Node> parse(const string& s, int& pos) {
    int st = pos;
    while (pos < (int)s.size() && isalpha(s[pos])) ++pos;
    string name = s.substr(st, pos - st);
    if (isupper(name[0])) return make_shared<Node>(Node::VAR, name);
    if (pos < (int)s.size() && s[pos] == '(') {
        ++pos;
        vector<shared_ptr<Node>> args;
        if (s[pos] != ')') {
            while (true) {
                args.push_back(parse(s, pos));
                if (pos < (int)s.size() && s[pos] == ',') { ++pos; continue; }
                break;
            }
        }
        if (pos < (int)s.size() && s[pos] == ')') ++pos;
        return make_shared<Node>(Node::FUNC, name, args);
    }
    return make_shared<Node>(Node::CONST, name);
}

shared_ptr<Node> applySubst(const map<string, shared_ptr<Node>>& subst, shared_ptr<Node> t) {
    if (t->type == Node::VAR) {
        auto it = subst.find(t->name);
        if (it != subst.end()) return applySubst(subst, it->second);
        return t;
    }
    if (t->type == Node::CONST) return t;
    vector<shared_ptr<Node>> newArgs;
    for (auto& a : t->args) newArgs.push_back(applySubst(subst, a));
    return make_shared<Node>(Node::FUNC, t->name, newArgs);
}

bool occurs(shared_ptr<Node> var, shared_ptr<Node> t) {
    if (t->type == Node::VAR) return t->name == var->name;
    if (t->type == Node::FUNC) {
        for (auto& a : t->args) if (occurs(var, a)) return true;
    }
    return false;
}

bool unify(shared_ptr<Node> t1, shared_ptr<Node> t2, map<string, shared_ptr<Node>>& subst) {
    shared_ptr<Node> u1 = applySubst(subst, t1), u2 = applySubst(subst, t2);
    if (u1->type == Node::VAR && u2->type == Node::VAR && u1->name == u2->name) return true;
    if (u1->type == Node::VAR) {
        if (occurs(u1, u2)) return false;
        subst[u1->name] = u2;
        return true;
    }
    if (u2->type == Node::VAR) {
        if (occurs(u2, u1)) return false;
        subst[u2->name] = u1;
        return true;
    }
    if (u1->type != u2->type || u1->name != u2->name || u1->args.size() != u2->args.size()) return false;
    for (size_t i = 0; i < u1->args.size(); ++i)
        if (!unify(u1->args[i], u2->args[i], subst)) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string name;
    int n;
    while (cin >> name) {
        if (name == "END") { cin >> n; break; }
        cin >> n;
        vector<shared_ptr<Node>> hs;
        string line;
        for (int i = 0; i < n; ++i) { cin >> line; int pos = 0; hs.push_back(parse(line, pos)); }
        map<string, shared_ptr<Node>> subst;
        bool ok = true;
        for (int i = 1; i < n; ++i) {
            if (!unify(hs[0], hs[i], subst)) { ok = false; break; }
        }
        if (ok) cout << "analysis inconclusive on " << name << "\n";
        else cout << name << " is a Starflyer agent\n";
    }
    return 0;
}
