#include <bits/stdc++.h>
using namespace std;

struct Node {
    enum Type { CHAR, STAR, CONCAT, UNION } type;
    char ch;
    Node *l, *r;
    vector<int> first, last;
    bool nullable;
    int pos;
    Node(Type t, char c = 0, Node *left = nullptr, Node *right = nullptr)
        : type(t), ch(c), l(left), r(right), pos(0), nullable(false) {}
};

void uniqueVec(vector<int>& v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

Node* parseAtom(const string& s, int& i);
Node* parseTerm(const string& s, int& i) {
    Node* node = parseAtom(s, i);
    while (i < (int)s.size() && s[i] != '+' && s[i] != ')') {
        Node* rhs = parseAtom(s, i);
        node = new Node(Node::CONCAT, 0, node, rhs);
    }
    return node;
}
Node* parseExpr(const string& s, int& i) {
    Node* node = parseTerm(s, i);
    while (i < (int)s.size() && s[i] == '+') {
        ++i;
        Node* rhs = parseTerm(s, i);
        node = new Node(Node::UNION, 0, node, rhs);
    }
    return node;
}
Node* parseAtom(const string& s, int& i) {
    if (isdigit(s[i])) {
        char ch = s[i++];
        if (i < (int)s.size() && s[i] == '*') {
            ++i;
            Node* leaf = new Node(Node::CHAR, ch);
            return new Node(Node::STAR, 0, leaf);
        }
        return new Node(Node::CHAR, ch);
    } else if (s[i] == '(') {
        ++i;
        Node* node = parseExpr(s, i);
        if (i < (int)s.size() && s[i] == ')') ++i;
        if (i < (int)s.size() && s[i] == '*') {
            ++i;
            return new Node(Node::STAR, 0, node);
        }
        return node;
    }
    return nullptr;
}

void assignPos(Node* node, int& cnt) {
    if (!node) return;
    if (node->type == Node::CHAR) node->pos = ++cnt;
    else { assignPos(node->l, cnt); assignPos(node->r, cnt); }
}

void computeProps(Node* node) {
    if (!node) return;
    if (node->type == Node::CHAR) {
        node->nullable = false;
        node->first = {node->pos};
        node->last = {node->pos};
        return;
    }
    if (node->type == Node::STAR) {
        computeProps(node->l);
        node->nullable = true;
        node->first = node->l->first;
        node->last = node->l->last;
        return;
    }
    computeProps(node->l);
    computeProps(node->r);
    if (node->type == Node::CONCAT) {
        node->nullable = node->l->nullable && node->r->nullable;
        node->first = node->l->first;
        if (node->l->nullable) node->first.insert(node->first.end(), node->r->first.begin(), node->r->first.end());
        node->last = node->r->last;
        if (node->r->nullable) node->last.insert(node->last.end(), node->l->last.begin(), node->l->last.end());
    } else {
        node->nullable = node->l->nullable || node->r->nullable;
        node->first = node->l->first;
        node->first.insert(node->first.end(), node->r->first.begin(), node->r->first.end());
        node->last = node->l->last;
        node->last.insert(node->last.end(), node->r->last.begin(), node->r->last.end());
    }
    uniqueVec(node->first);
    uniqueVec(node->last);
}

vector<pair<int,int>> edges;
void addFollow(Node* node) {
    if (!node) return;
    if (node->type == Node::CONCAT) {
        for (int i : node->l->last) for (int j : node->r->first) edges.push_back({i,j});
        addFollow(node->l); addFollow(node->r);
    } else if (node->type == Node::STAR) {
        for (int i : node->l->last) for (int j : node->l->first) edges.push_back({i,j});
        addFollow(node->l);
    } else if (node->type == Node::UNION) {
        addFollow(node->l); addFollow(node->r);
    }
}

const int MAXM = 505;
const int MAXW = 8;
int charOfPos[MAXM];
vector<int> outEdge[MAXM][10];
unsigned long long finalMask[MAXW];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string R, T;
    while (cin >> n >> R >> T) {
        int idx = 0;
        Node* root = parseExpr(R, idx);
        int posCnt = 0;
        assignPos(root, posCnt);
        int M = posCnt + 1;
        int W = (M + 63) >> 6;
        for (int i = 0; i < M; ++i) charOfPos[i] = -1;
        function<void(Node*)> collect = [&](Node* node) {
            if (!node) return;
            if (node->type == Node::CHAR) charOfPos[node->pos] = node->ch - '0';
            else { collect(node->l); collect(node->r); }
        };
        collect(root);
        computeProps(root);
        for (int i = 0; i < MAXW; ++i) finalMask[i] = 0;
        for (int p : root->last) finalMask[p >> 6] |= 1ULL << (p & 63);
        edges.clear();
        addFollow(root);
        for (int p : root->first) edges.push_back({0, p});
        for (int i = 0; i < M; ++i) for (int c = 0; c < n; ++c) outEdge[i][c].clear();
        for (auto &e : edges) {
            int from = e.first, to = e.second;
            int c = charOfPos[to];
            if (c >= 0 && c < n) outEdge[from][c].push_back(to);
        }
        unsigned long long cur[MAXW] = {0};
        vector<int> ans;
        ans.reserve(1024);
        int active[MAXM], actCnt;
        for (int pos = 0; pos < (int)T.size(); ++pos) {
            cur[0] |= 1ULL;
            int c = T[pos] - '0';
            unsigned long long nxt[MAXW] = {0};
            actCnt = 0;
            for (int w = 0; w < W; ++w) {
                unsigned long long x = cur[w];
                while (x) {
                    int b = __builtin_ctzll(x);
                    active[actCnt++] = (w << 6) + b;
                    x &= x - 1;
                }
            }
            for (int i = 0; i < actCnt; ++i) {
                int st = active[i];
                for (int j : outEdge[st][c]) nxt[j >> 6] |= 1ULL << (j & 63);
            }
            bool ok = false;
            for (int w = 0; w < W; ++w) if (nxt[w] & finalMask[w]) { ok = true; break; }
            if (ok) ans.push_back(pos + 1);
            for (int w = 0; w < W; ++w) cur[w] = nxt[w];
        }
        for (size_t i = 0; i < ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
