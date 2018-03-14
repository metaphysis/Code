// Pre, In and Post
// UVa ID: 10701
// Verdict: Accepted
// Submission Date: 2018-02-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void postorder(string preorder, string inorder)
{
    if (preorder.length() == 0)
        return;

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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    string s1, s2;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> s1 >> s2;
        postorder(s1, s2);
        cout << '\n';
    }

    return 0;
}
