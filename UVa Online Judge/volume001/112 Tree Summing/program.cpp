// Tree Summing
// UVa ID: 112
// Verdict: Accepted
// Submission Date: 2017-05-08
// UVa Run Time: 0.030s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct TreeNode
{
    int weight;
    TreeNode *parent, *leftChild, *rightChild;
};

bool exist, empty;

void summing(TreeNode *node)
{
    if (node->leftChild != NULL)
    {
        node->leftChild->weight += node->weight;
        summing(node->leftChild);
    }

    if (node->rightChild != NULL)
    {
        node->rightChild->weight += node->weight;
        summing(node->rightChild);
    }
}

void parse(TreeNode *node)
{
    bool isLeaf = false;

    char c;
    while (cin >> c, c != '(') { }

    cin >> c;
    if (isdigit(c) || c == '-')
    {
        int sign = (c == '-' ? (-1) : 1), number = 0;
        if (isdigit(c)) number = c - '0';
        while (cin >> c, isdigit(c)) number *= 10, number += (c - '0');
        cin.putback(c);
        node->weight = number * sign;
    }
    else
    {
        cin.putback(c);

        if (node->parent != NULL)
        {
            if (node == node->parent->leftChild)
                node->parent->leftChild = NULL;
            else
                node->parent->rightChild = NULL;
        }
        else
            empty = true;

        isLeaf = true;
    }

    if (!isLeaf)
    {
        TreeNode *left = new TreeNode;
        node->leftChild = left;
        left->parent = node;
        parse(left);

        TreeNode *right = new TreeNode;
        node->rightChild = right;
        right->parent = node;
        parse(right);
    }

    while (cin >> c, c != ')') { }
}

void traversal(TreeNode *node, int sum)
{
    if (exist) return;

    if (node->leftChild == NULL && node->rightChild == NULL)
        if (node->weight == sum)
            exist = true;

    if (node->leftChild != NULL) traversal(node->leftChild, sum);
    if (node->rightChild != NULL) traversal(node->rightChild, sum);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int sum;
    while (cin >> sum)
    {
        empty = false, exist = false;
        
        TreeNode *root = new TreeNode;
        parse(root);
        summing(root);
        if (!empty) traversal(root, sum);

        cout << (exist ? "yes" : "no") << '\n';

        delete root;
    }

    return 0;
}
