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

int getRank(Tree t, int x) {
    if (t == nullptr) return -1;
    int s = t->leftChild == nullptr ? 0 : t->leftChild->size;
    if (x == t->key) return s;
    if (x < t->key) return getRank(t->leftChild, x);
    return s + t->cnt + getRank(t->rightChild, x);
}

void traversal(Tree &t) {
    if (t == nullptr) return;
    cout << t->key << ' ' << t->priority << ' ' << t->cnt << ' ' << t->size << '\n';
    traversal(t->leftChild);
    traversal(t->rightChild);
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    srand(time(NULL));
    Tree root = new Node(1);
    insert(root, 2);
    insert(root, 8);
    insert(root, 5);
    insert(root, 2);
    cout << getRank(root, 5) << '\n';
    return 0;
}
