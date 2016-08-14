// Tree Summing
// UVa ID: 112
// Verdict: Accepted
// Submission Date: 2016-04-04
// UVa Run Time: 0.039s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

struct TreeNode
{
    int weight;
    TreeNode *parent, *leftChild, *rightChild;
};

bool haveTargetSum, emptyTree;

// 前序遍历，将路径和保存在叶结点上。
void summingTree(TreeNode * current)
{
    if (current->leftChild != NULL)
    {
        current->leftChild->weight += current->weight;
        summingTree(current->leftChild);
    }

    if (current->rightChild != NULL)
    {
        current->rightChild->weight += current->weight;
        summingTree(current->rightChild);
    }
}

// 利用递归和cin.putback()，将输入解析为链表表示的树。
void parseTree(TreeNode * current)
{
    bool isLeaf = false;

    char c;
    while (cin >> c, c != '(')
        ;

    // 需要考虑负数的情况。
    cin >> c;
    if (isdigit(c) || c == '-')
    {
        int sign = c == '-' ? (-1) : 1;
        int number = 0;

        if (isdigit(c))
            number = c - '0';

        while (cin >> c, isdigit(c))
        {
            number *= 10;
            number += (c - '0');
        }

        cin.putback(c);
        current->weight = number * sign;
    }
    else
    {
        cin.putback(c);

        // 若当前结点为空，则将父结点的相应子结点设为空。
        if (current->parent != NULL)
        {
            if (current == current->parent->leftChild)
                current->parent->leftChild = NULL;
            else
                current->parent->rightChild = NULL;
        }
        else
            emptyTree = true;

        isLeaf = true;
    }

    // 若不是叶结点，则继续解析子树。
    if (!isLeaf)
    {
        TreeNode *left = new TreeNode;
        current->leftChild = left;
        left->parent = current;
        parseTree(left);

        TreeNode *right = new TreeNode;
        current->rightChild = right;
        right->parent = current;
        parseTree(right);
    }

    while (cin >> c, c != ')')
        ;
}

// 遍历树，检查叶结点保存的路径和是否为目标值。
void treeTraversal(TreeNode * current, int targetSum)
{
    if (haveTargetSum)
        return;

    if (current->leftChild == NULL && current->rightChild == NULL)
        if (current->weight == targetSum)
            haveTargetSum = true;

    if (current->leftChild != NULL)
        treeTraversal(current->leftChild, targetSum);

    if (current->rightChild != NULL)
        treeTraversal(current->rightChild, targetSum);
}

int main(int argc, char *argv[])
{
    int targetSum;
    while (cin >> targetSum)
    {
        TreeNode *root = new TreeNode;

        emptyTree = false;
        parseTree(root);

        summingTree(root);

        haveTargetSum = false;
        if (!emptyTree)
            treeTraversal(root, targetSum);

        cout << (haveTargetSum ? "yes\n" : "no\n");

        delete root;
    }

    return 0;
}
