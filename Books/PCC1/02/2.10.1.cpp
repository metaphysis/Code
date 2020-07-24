#include <bits/stdc++.h>

using namespace std;

struct TreeNode
{
    int id, weight;
    TreeNode *parent, *leftChild, *rightChild;
};

void preorderTraversal(TreeNode* root)
{
    if (root == NULL)
        return;

    cout << ' ' << root->id;
    preorderTraversal(root->leftChild);
    preorderTraversal(root->rightChild);
}

void inorderTraversal(TreeNode* root)
{
    if (root == NULL)
        return;

    inorderTraversal(root->leftChild);
    cout << ' ' << root->id;
    inorderTraversal(root->rightChild);
}

void postorderTraversal(TreeNode* root)
{
    if (root == NULL)
        return;

    postorderTraversal(root->leftChild);
    postorderTraversal(root->rightChild);
    cout << ' ' << root->id;
}

int main(int argc, char *argv[])
{
    TreeNode *root = new TreeNode;
    
    preorderTraversal(root);
    inorderTraversal(root);
    postorderTraversal(root);
    
    return 0;
}
