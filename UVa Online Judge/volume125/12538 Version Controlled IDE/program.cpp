// Version Controlled IDE
// UVa ID: 12538
// Verdict: Accepted
// Submission Date: 2023-02-27
// UVa Run Time: 0.210s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef struct Node {
    int key, priority;
    int size;
    Node *leftChild, *rightChild;
    Node (int k) {
        key = k; size = 1; priority = rand();
        leftChild = rightChild = nullptr;
    }
}* Tree;

inline void copy(Tree &x, Tree &y) {
    if (y == nullptr) x = y;
    else {
        x = new Node(-1);
        *x = *y;
    }
}

inline void pushUp(Tree &t) {
    if (t == nullptr) return;
    t->size = 1;
    if (t->leftChild != nullptr) t->size += t->leftChild->size;
    if (t->rightChild != nullptr) t->size += t->rightChild->size;
}

inline int getSize(Tree &t) {
    return t == nullptr ? 0 : t->size;
}

void split(Tree t, Tree &x, Tree &y, int k) {
    if (!k) {
        copy(y, t);
        x = nullptr;
    }
    else if (getSize(t) <= k) {
        copy(x, t);
        y = nullptr;
    }
    else if (getSize(t->leftChild) >= k) {
        copy(y, t);
        split(t->leftChild, x, y->leftChild, k);
        pushUp(y);
    } else {
        copy(x, t);
        split(t->rightChild, x->rightChild, y, k - getSize(t->leftChild) - 1);
        pushUp(x);
    }
}

void merge(Tree &t, Tree x, Tree y) {
    if (x == nullptr) copy(t, y);
    else if (y == nullptr) copy(t, x);
    else if (x->priority > y->priority) {
        copy(t, x);
        merge(t->rightChild, x->rightChild, y);
    } else {
        copy(t, y);
        merge(t->leftChild, x, y->leftChild);
    }
    pushUp(t);
}

string s;

void build(Tree &t, int l, int r) {
    if (l > r) return;
    int m = (l + r) >> 1;
    t = new Node(s[m]);
    build(t->leftChild, l, m - 1);
    build(t->rightChild, m + 1, r);
    pushUp(t);
}

void insert(Tree &tt, Tree &t, int p) {
    Tree x, y, z;
    split(t, x, y, p);
    build(z, 0, (int)s.length() - 1);
    merge(x, x, z);
    merge(tt, x, y);
}

void remove(Tree &tt, Tree &t, int p, int w) {
    Tree x, y, z;
    split(t, x, y, p - 1);
    split(y, y, z, w);
    merge(tt, x, z);
}

int delta = 0;

void traversal(Tree t) {
    if (t == nullptr) return;
    traversal(t->leftChild);
    cout << (char)(t->key);
    if (t->key == 'c') delta++;
    traversal(t->rightChild);
}

void print(Tree t, int p, int w) {
    Tree x, y, z;
    split(t, x, y, p - 1);
    split(y, y, z, w);
    traversal(y);
    cout << '\n';
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    srand(time(NULL));
    Tree root[50010];
    root[0] = nullptr;
    int n, cmd, v, p, c, vnow = 0;
    cin >> n;
    while (n--) {
        cin >> cmd;
        if (cmd == 1) {
            cin >> p >> s;
            p -= delta;
            insert(root[vnow + 1], root[vnow], p);
            vnow++;
        } else if (cmd == 2) {
            cin >> p >> c;
            p -= delta, c -= delta;
            remove(root[vnow + 1], root[vnow], p, c);
            vnow++;
        } else {
            cin >> v >> p >> c;
            v -= delta, p -= delta, c -= delta;
            print(root[v], p, c);
        }
    }
    return 0;
}
