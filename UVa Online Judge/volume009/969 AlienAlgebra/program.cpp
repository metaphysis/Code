#include <bits/stdc++.h>
using namespace std;

struct Node {
    char op;
    int a, b;
};

string text;
vector<Node> nodes;
int pos;

int parse() {
    char op = text[pos++];
    int a = -1, b = -1;
    if (op == '0') {
        nodes.push_back({op, a, b});
        return (int)nodes.size() - 1;
    }
    pos++;
    a = parse();
    if (op == 'i') {
        pos++;
        nodes.push_back({op, a, b});
        return (int)nodes.size() - 1;
    }
    pos++;
    b = parse();
    pos++;
    nodes.push_back({op, a, b});
    return (int)nodes.size() - 1;
}

void normalize(int u, string &res) {
    Node cur = nodes[u];
    if (cur.op == '0') {
        res += '0';
        return;
    }
    if (cur.op == 'i') {
        normalize(cur.a, res);
        return;
    }
    if (cur.op == 't') {
        res += "t(";
        normalize(cur.a, res);
        res += ',';
        normalize(cur.b, res);
        res += ')';
        return;
    }
    res += "t(";
    normalize(cur.b, res);
    res += ",t(";
    normalize(cur.a, res);
    res += ",0))";
}

string getNormal(string s) {
    text = s;
    nodes.clear();
    pos = 0;
    int root = parse();
    string res;
    normalize(root, res);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    while (n--) {
        string a, b;
        cin >> a >> b;
        if (getNormal(a) == getNormal(b)) cout << "true\n";
        else cout << "false\n";
    }
    return 0;
}
