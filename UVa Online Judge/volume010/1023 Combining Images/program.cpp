// Combining Images
// UVa ID: 1023
// Verdict: Accepted
// Submission Date: 2026-07-25
// UVa Run Time: 0.010s
// https://blog.csdn.net/metaphysis/article/details/163183010

#include <bits/stdc++.h>
using namespace std;

struct Node {
    bool isLeaf;
    int color;
    vector<shared_ptr<Node>> children;
    Node(bool leaf, int c) : isLeaf(leaf), color(c) {}
    Node(bool leaf, int c, const vector<shared_ptr<Node>>& ch) : isLeaf(leaf), color(c), children(ch) {}
};

shared_ptr<Node> parse(const string& enc, int& pos) {
    char c = enc[pos++];
    if (c == '1') {
        int col = enc[pos++] - '0';
        return make_shared<Node>(true, col);
    } else {
        auto node = make_shared<Node>(false, -1);
        for (int i = 0; i < 4; ++i) node->children.push_back(parse(enc, pos));
        return node;
    }
}

string fromHex(const string& hex) {
    string bin;
    for (char ch : hex) {
        int val;
        if (ch >= '0' && ch <= '9') val = ch - '0';
        else if (ch >= 'A' && ch <= 'F') val = ch - 'A' + 10;
        else if (ch >= 'a' && ch <= 'f') val = ch - 'a' + 10;
        else continue;
        for (int i = 3; i >= 0; --i) bin += ((val >> i) & 1) ? '1' : '0';
    }
    size_t pos = bin.find('1');
    if (pos == string::npos) return "";
    return bin.substr(pos + 1);
}

string toHex(const string& raw) {
    string s = "1" + raw;
    int rem = s.length() % 4;
    if (rem) s = string(4 - rem, '0') + s;
    string hex;
    for (size_t i = 0; i < s.length(); i += 4) {
        int val = 0;
        for (int j = 0; j < 4; ++j) val = val * 2 + (s[i + j] - '0');
        if (val < 10) hex += char('0' + val);
        else hex += char('A' + val - 10);
    }
    return hex;
}

shared_ptr<Node> intersectNode(shared_ptr<Node> a, shared_ptr<Node> b) {
    if (a->isLeaf && b->isLeaf) {
        int col = a->color & b->color;
        return make_shared<Node>(true, col);
    }
    if (a->isLeaf) {
        if (a->color == 0) return make_shared<Node>(true, 0);
        else return b;
    }
    if (b->isLeaf) {
        if (b->color == 0) return make_shared<Node>(true, 0);
        else return a;
    }
    vector<shared_ptr<Node>> childs;
    for (int i = 0; i < 4; ++i) childs.push_back(intersectNode(a->children[i], b->children[i]));
    if (childs[0]->isLeaf && childs[1]->isLeaf && childs[2]->isLeaf && childs[3]->isLeaf) {
        int col = childs[0]->color;
        if (childs[1]->color == col && childs[2]->color == col && childs[3]->color == col)
            return make_shared<Node>(true, col);
    }
    auto node = make_shared<Node>(false, -1);
    node->children = childs;
    return node;
}

string encode(const shared_ptr<Node>& node) {
    if (node->isLeaf) {
        return string("1") + char('0' + node->color);
    } else {
        string res = "0";
        for (auto& ch : node->children) res += encode(ch);
        return res;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string a, b;
    int caseNo = 1;
    while (cin >> a >> b) {
        if (a == "0" && b == "0") break;
        string rawA = fromHex(a);
        string rawB = fromHex(b);
        int pos = 0;
        auto nodeA = parse(rawA, pos);
        pos = 0;
        auto nodeB = parse(rawB, pos);
        auto res = intersectNode(nodeA, nodeB);
        string rawRes = encode(res);
        string hexRes = toHex(rawRes);
        if (caseNo > 1) cout << "\n";
        cout << "Image " << caseNo << ": " << hexRes << "\n";
        ++caseNo;
    }
    return 0;
}
