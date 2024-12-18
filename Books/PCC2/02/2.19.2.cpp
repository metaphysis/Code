// treap

#include <bits/stdc++.h>

using namespace std;

typedef struct Node {
    int key, priority;
    int cnt, size;
    Node *leftChild, *rightChild;
    Node (int k) {
        key = k; size = cnt = 1; priority = rand();
        leftChild = rightChild = nullptr;
    }
}* Tree;

void pushUp(Tree &t) {
    if (t == nullptr) return;
    t->size = t->cnt;
    if (t->leftChild != nullptr) t->size += t->leftChild->size;
    if (t->rightChild != nullptr) t->size += t->rightChild->size;
}

void split(Tree t, Tree &x, Tree &y, int k) {
    if (t == nullptr) {
        x = y = nullptr;
        return;
    }
    if (t->key <= k) {
        x = t;
        split(t->rightChild, x->rightChild, y, k);
    } else {
        y = t;
        split(t->leftChild, x, y->leftChild, k);
    }
    pushUp(t);
}

void merge(Tree &t, Tree x, Tree y) {
    if (x == nullptr || y == nullptr) {
        t = x == nullptr ? y : x;
        return;
    }
    if (x->priority > y->priority) {
        t = x;
        merge(t->rightChild, x->rightChild, y);
    } else {
        t = y;
        merge(t->leftChild, x, y->leftChild);
    }
    pushUp(t);
}

void insert(Tree &t, int k) {
    Tree x, y, z;
    split(t, x, y, k);
    split(x, x, z, k - 1);
    if (z == nullptr) z = new Node(k);
    else { z->cnt++; z->size = z->cnt; }
    merge(x, x, z);
    merge(t, x, y);
}

void remove(Tree &t, int k) {
    Tree x, y, z;
    split(t, x, y, k);
    split(x, x, z, k - 1);
    if (z->cnt > 1) { z->cnt--; z->size = z->cnt; }
    else {
        delete z;
        z = nullptr;
    }
    merge(x, x, z);
    merge(t, x, y);
}

const int INF = 0x7f7f7f7f;

int getRank(Tree &t, int k) {
    if (t == nullptr) return -INF + 1;
    int s = t->leftChild == nullptr ? 0 : t->leftChild->size;
    if (k == t->key) return s + 1;
    if (k < t->key) return getRank(t->leftChild, k);
    return s + t->cnt + getRank(t->rightChild, k);
}

int getKth(Tree t, int k) {
    if (t == nullptr) return INF;
    int s = t->leftChild == nullptr ? 0 : t->leftChild->size;
    if (k <= s) return getKth(t->leftChild, k);
    if (k <= s + t->cnt) return t->key;
    return getKth(t->rightChild, k - s - t->cnt);
}

int getPrevious(Tree t, int x) {
    int r = INF;
    while (t != nullptr) {
        if (t->key < x) {
            r = t->key;
            t = t->rightChild;
        } else t = t->leftChild;
    }
    return r;
}

int getNext(Tree t, int x) {
    int r = INF;
    while (t != nullptr) {
        if (t->key > x) {
            r = t->key;
            t = t->leftChild;
        } else t = t->rightChild;
    }
    return r;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    Tree root = new Node(-INF);
    int n, cmd, x;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cmd >> x;
        if (cmd == 1) insert(root, x);
        if (cmd == 2) remove(root, x);
        if (cmd == 3) cout << getRank(root, x) - 1 << '\n';
        if (cmd == 4) cout << getKth(root, x + 1) << '\n';
        if (cmd == 5) cout << getPrevious(root, x) << '\n';
        if (cmd == 6) cout << getNext(root, x) << '\n';
    }
    return 0;
}
