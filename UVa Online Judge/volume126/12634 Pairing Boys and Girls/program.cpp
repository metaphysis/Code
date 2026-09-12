#include <bits/stdc++.h>
using namespace std;

struct Info {
    long long boy, girl, pair;
};

struct Node {
    int type, cnt;
    long long size, boy, girl, pair;
    unsigned priority;
    Node *left, *right;
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

Info joinInfo(Info a, Info b) {
    Info c = {0, 0, 0};
    long long cross = min(a.boy, b.girl);
    c.boy = a.boy - cross + b.boy;
    c.girl = a.girl + b.girl - cross;
    c.pair = a.pair + b.pair + cross;
    return c;
}

Info getInfo(Node *o) {
    if (!o) return {0, 0, 0};
    return {o->boy, o->girl, o->pair};
}

Info makeInfo(int type, long long cnt) {
    if (type == 0) return {cnt, 0, 0};
    return {0, cnt, 0};
}

Node *newNode(int type, int cnt) {
    Node *o = new Node();
    o->type = type;
    o->cnt = cnt;
    o->size = cnt;
    o->boy = type == 0 ? cnt : 0;
    o->girl = type == 1 ? cnt : 0;
    o->pair = 0;
    o->priority = rng();
    o->left = nullptr;
    o->right = nullptr;
    return o;
}

void pushUp(Node *o) {
    if (!o) return;
    Info a = getInfo(o->left), b = makeInfo(o->type, o->cnt), c = getInfo(o->right);
    Info d = joinInfo(joinInfo(a, b), c);
    o->size = (o->left ? o->left->size : 0) + o->cnt + (o->right ? o->right->size : 0);
    o->boy = d.boy;
    o->girl = d.girl;
    o->pair = d.pair;
}

Node *mergeTree(Node *a, Node *b) {
    if (!a) return b;
    if (!b) return a;
    if (a->priority > b->priority) {
        a->right = mergeTree(a->right, b);
        pushUp(a);
        return a;
    } else {
        b->left = mergeTree(a, b->left);
        pushUp(b);
        return b;
    }
}

void splitTree(Node *o, long long k, Node *&a, Node *&b) {
    if (!o) {
        a = nullptr;
        b = nullptr;
        return;
    }
    long long leftSize = o->left ? o->left->size : 0;
    if (k < leftSize) {
        splitTree(o->left, k, a, o->left);
        pushUp(o);
        b = o;
    } else if (k > leftSize + o->cnt) {
        splitTree(o->right, k - leftSize - o->cnt, o->right, b);
        pushUp(o);
        a = o;
    } else if (k == leftSize) {
        a = o->left;
        o->left = nullptr;
        pushUp(o);
        b = o;
    } else if (k == leftSize + o->cnt) {
        b = o->right;
        o->right = nullptr;
        pushUp(o);
        a = o;
    } else {
        int leftCnt = static_cast<int>(k - leftSize), rightCnt = o->cnt - leftCnt;
        Node *q = newNode(o->type, rightCnt);
        q->right = o->right;
        o->right = nullptr;
        o->cnt = leftCnt;
        pushUp(o);
        pushUp(q);
        a = o;
        b = q;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n;
        cin >> n;
        Node *root = newNode(0, 1), *leftTree, *rightTree, *midTree;
        cout << "Case " << cs << ":\n";
        for (int i = 0; i < n; i++) {
            int type, where, count;
            cin >> type >> where >> count;
            splitTree(root, where, leftTree, rightTree);
            midTree = newNode(type, count);
            root = mergeTree(mergeTree(leftTree, midTree), rightTree);
            cout << root->pair << '\n';
        }
    }
    return 0;
}
