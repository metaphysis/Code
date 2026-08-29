#include <bits/stdc++.h>
using namespace std;

struct Node {
    int childCnt;
    Node *left, *right;
    Node(int cnt) : childCnt(cnt), left(NULL), right(NULL) {}
};

int globalAns;

Node* buildTree() {
    int cnt;
    cin >> cnt;
    Node* u = new Node(cnt);
    if (cnt >= 1) u->left = buildTree();
    if (cnt == 2) u->right = buildTree();
    return u;
}

int dfsSolve(Node* u) {
    if (!u) return 0;
    int leftDp = dfsSolve(u->left);
    int rightDp = dfsSolve(u->right);
    int curDp = 0;
    if (u->childCnt == 2) curDp = 1 + min(leftDp, rightDp);
    if (curDp > globalAns) globalAns = curDp;
    return curDp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        Node* root = buildTree();
        globalAns = 0;
        dfsSolve(root);
        cout << globalAns << "\n";
    }
    return 0;
}
