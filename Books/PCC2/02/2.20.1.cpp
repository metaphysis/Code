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

void pushUp(Tree t) {
    if (t == nullptr) return;
    t->size = t->cnt;
    if (t->leftChild != nullptr) t->size += t->leftChild->size;
    if (t->rightChild != nullptr) t->size += t->rightChild->size;
}

void rightRotate(Tree &t) {
    Tree lt = t->leftChild;
    t->leftChild = lt->rightChild;
    lt->rightChild = t;
    t = lt;
    pushUp(t->rightChild);
    pushUp(t);
}

void leftRotate(Tree &t) {
    Tree rt = t->rightChild;
    t->rightChild = rt->leftChild;
    rt->leftChild = t;
    t = rt;
    pushUp(t->leftChild);
    pushUp(t);
}

void insert(Tree &t, int k) {
    if (t == nullptr) {
        t = new Node(k);
    } else if (k == t->key) {
        t->cnt++;
    } else if (k < t->key) {
        insert(t->leftChild, k);
        if (t->priority < t->leftChild->priority) rightRotate(t);
    } else {
        insert(t->rightChild, k);
        if (t->priority < t->rightChild->priority) leftRotate(t);
    }
    pushUp(t);
}

void remove(Tree &t, int k) {
    if (t == nullptr) return;
    if (k == t->key) {
        if (t->cnt > 1) t->cnt--;
        else if (t->leftChild != nullptr || t->rightChild != nullptr) {
            if (t->rightChild == nullptr ||
                (t->leftChild != nullptr &&
                t->leftChild->priority > t->rightChild->priority)) {
                    rightRotate(t);
                    remove(t->rightChild, k);
                } else {
                    leftRotate(t);
                    remove(t->leftChild, k);
                }
        } else {
            delete t;
            t = nullptr;
        }
    } else if (k < t->key) remove(t->leftChild, k);
    else remove(t->rightChild, k);
    pushUp(t);
}

const int INF = 0x7f7f7f7f;

int getRank(Tree t, int k) {
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

int getPrevious(Tree t, int k) {
    int r = INF;
    while (t != nullptr) {
        if (t->key < k) {
            r = t->key;
            t = t->rightChild;
        } else t = t->leftChild;
    }
    return r;
}

int getNext(Tree t, int k) {
    int r = INF;
    while (t != nullptr) {
        if (t->key > k) {
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
