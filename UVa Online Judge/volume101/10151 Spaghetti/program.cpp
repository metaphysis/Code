#include <bits/stdc++.h>
using namespace std;

struct Node {
    int type, to;
    string text;
};

struct Program {
    vector<Node> node;
};

string trimStr(string s) {
    int l = 0, r = (int)s.size() - 1;
    while (l <= r && isspace((unsigned char)s[l])) l++;
    while (l <= r && isspace((unsigned char)s[r])) r--;
    return l > r ? "" : s.substr(l, r - l + 1);
}

string removeSpace(const string &s) {
    string t;
    for (char c : s)
        if (!isspace((unsigned char)c)) t += c;
    return t;
}

Program buildProgram(const vector<string> &line) {
    Program p;
    unordered_map<int, int> pos;
    vector<int> lab;
    for (int i = 0; i < (int)line.size(); i++) {
        string s = line[i];
        int a = 0, b, x = -1;
        while (a < (int)s.size() && isspace((unsigned char)s[a])) a++;
        b = a;
        while (b < (int)s.size() && isdigit((unsigned char)s[b])) b++;
        if (b > a && b < (int)s.size() && isspace((unsigned char)s[b])) {
            x = stoi(s.substr(a, b - a));
            s = s.substr(b);
        }
        s = removeSpace(s);
        Node cur;
        cur.to = -1;
        if (s.rfind("goto", 0) == 0) {
            cur.type = 0;
            cur.to = stoi(s.substr(4));
        } else if (s.rfind("if(", 0) == 0) {
            int k = s.find(")goto");
            cur.type = 2;
            cur.text = s.substr(0, k + 5);
            cur.to = stoi(s.substr(k + 5));
        } else if (s == "stop") {
            cur.type = 3;
            cur.text = s;
        } else {
            cur.type = 1;
            cur.text = s;
        }
        p.node.push_back(cur);
        lab.push_back(x);
        if (x != -1) pos[x] = i;
    }
    for (Node &x : p.node)
        if (x.type == 0 || x.type == 2) x.to = pos[x.to];
    return p;
}

int normalize(const Program &p, int x) {
    vector<int> vis(p.node.size());
    while (true) {
        if (x >= (int)p.node.size()) return -1;
        if (p.node[x].type != 0) return x;
        if (vis[x]) return -2;
        vis[x] = 1;
        x = p.node[x].to;
    }
}

bool equivalent(const Program &a, const Program &b) {
    vector<pair<int, int>> st;
    unordered_set<long long> vis;
    st.push_back({0, 0});
    while (!st.empty()) {
        auto [u, v] = st.back();
        st.pop_back();
        u = normalize(a, u);
        v = normalize(b, v);
        if (u < 0 || v < 0) {
            if (u != v) return false;
            continue;
        }
        long long key = 1LL * u * 1005 + v;
        if (vis.count(key)) continue;
        vis.insert(key);
        const Node &x = a.node[u];
        const Node &y = b.node[v];
        if (x.type != y.type || x.text != y.text) return false;
        if (x.type == 1 || x.type == 3) st.push_back({u + 1, v + 1});
        else if (x.type == 2) {
            st.push_back({u + 1, v + 1});
            st.push_back({x.to, y.to});
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<string>> block;
    vector<string> cur;
    string s;
    while (getline(cin, s)) {
        if (trimStr(s).empty()) {
            if (!cur.empty()) {
                block.push_back(cur);
                cur.clear();
            }
        } else cur.push_back(s);
    }
    if (!cur.empty()) block.push_back(cur);
    for (int i = 0; i + 1 < (int)block.size(); i += 2) {
        Program a = buildProgram(block[i]);
        Program b = buildProgram(block[i + 1]);
        if (equivalent(a, b)) cout << "The programs are equivalent.\n";
        else cout << "The programs are not equivalent.\n";
    }
    return 0;
}
