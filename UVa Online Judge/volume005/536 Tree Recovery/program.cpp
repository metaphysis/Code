// Tree Recovery
// UVa ID: 536
// Verdict: Accepted
// Submission Date: 2016-08-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

void postorder(string preorder, string inorder) {
    if (preorder.length() == 0) return;
    // 找到根结点。
    int root = 0;
    for (; root < inorder.length(); root++)
        if (inorder[root] == preorder.front())
            break;
    // 在左子树中递归。
    postorder(preorder.substr(1, root), inorder.substr(0, root));
    // 在右子树中递归。
    postorder(preorder.substr(root + 1), inorder.substr(root + 1));
    // 输出根。
    cout << preorder.front();
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    string order1, order2;
    while (cin >> order1 >> order2) {
        postorder(order1, order2);
        cout << '\n';
    }
    return 0;
}
