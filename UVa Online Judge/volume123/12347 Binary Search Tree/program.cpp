// Binary Search Tree
// UVa ID: 12347
// Verdict: Accepted
// Submission Date: 2018-02-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct TreeNode
{
    int value;
    TreeNode *leftchild, *rightchild;
};

void add(TreeNode *father, TreeNode *child, bool isLeft, int number)
{
    if (child == NULL)
    {
        child = new TreeNode;
        child->value = number;
        child->leftchild = child->rightchild = NULL;
        if (isLeft) father->leftchild = child;
        else father->rightchild = child;
        return;
    }
    if (number > child->value) add(child, child->rightchild, false, number);
    else add(child, child->leftchild, true, number);
}

void traversal(TreeNode *child)
{
    if (child->leftchild != NULL) traversal(child->leftchild);
    if (child->rightchild != NULL) traversal(child->rightchild);
    cout << child->value << '\n';
    delete child;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int number;
    cin >> number;
    TreeNode *root = new TreeNode;
    root->value = number;
    root->leftchild = root->rightchild = NULL;

    while (cin >> number) add(root, root, true, number);

    traversal(root);

    return 0;
}
