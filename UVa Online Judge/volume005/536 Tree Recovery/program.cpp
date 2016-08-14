// Tree Recovery
// UVa ID: 536
// Verdict: Accepted
// Submission Date: 2016-08-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

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

void preorder(string postorder, string inorder)
{
    if (postorder.length() == 0)
        return;

    // 找到根结点。
    int root = 0;
    for (; root < inorder.length(); root++)
        if (inorder[root] == postorder.back())
            break;

    // 输出根。
    cout << postorder.back();

    // 在左子树中递归。
    preorder(postorder.substr(0, root), inorder.substr(0, root));

    // 在右子树中递归。
    preorder(postorder.substr(root, postorder.length() - root - 1),
        inorder.substr(root + 1));
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string order1, order2;
    while (cin >> order1 >> order2)
    {
        postorder(order1, order2);
        //preorder(order1, order2);
        cout << '\n';
    }

	return 0;
}
