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

void pushUp(Tree &x) {
    if (x == nullptr) return;
    x->size = x->cnt;
    if (x->leftChild != nullptr) x->size += x->leftChild->size;
    if (x->rightChild != nullptr) x->size += x->rightChild->size;
}

void rightRotate(Tree &x) {
    Tree y = x->leftChild;
    x->leftChild = y->rightChild;
    y->rightChild = x;
    x = y;
    pushUp(x->rightChild);
    pushUp(x);
}

void leftRotate(Tree &x) {
    Tree y = x->rightChild;
    x->rightChild = y->leftChild;
    y->leftChild = x;
    x = y;
    pushUp(x->leftChild);
    pushUp(x);
}

void insert(Tree &x, int k) {
    if (x == nullptr) {
        x = new Node(k);
    } else if (k == x->key) {
        x->cnt++;
    } else if (k < x->key) {
        insert(x->leftChild, k);
        if (x->priority < x->leftChild->priority) rightRotate(x);
    } else {
        insert(x->rightChild, k);
        if (x->priority < x->rightChild->priority) leftRotate(x);
    }
    pushUp(x);
}

void remove(Tree &x, int k) {
    if (x == nullptr) return;
    if (k == x->key) {
        if (x->cnt > 1) x->cnt--;
        else if (x->leftChild != nullptr || x->rightChild != nullptr) {
            if (x->rightChild == nullptr ||
                (x->leftChild != nullptr &&
                x->leftChild->priority > x->rightChild->priority)) {
                    rightRotate(x);
                    remove(x->rightChild, k);
                } else {
                    leftRotate(x);
                    remove(x->leftChild, k);
                }
        } else {
            delete x;
            x = nullptr;
        }
    } else if (k < x->key) remove(x->leftChild, k);
    else remove(x->rightChild, k);
    pushUp(x);
}

void traversal(Tree &x) {
    if (x == nullptr) return;
    cout << x->key << ' ' << x->priority << ' ' << x->cnt << ' ' << x->size << '\n';
    traversal(x->leftChild);
    traversal(x->rightChild);
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    srand(time(NULL));
    Tree root = new Node(1);
    insert(root, 2);
    insert(root, 8);
    insert(root, 5);
    traversal(root);
    return 0;
}
