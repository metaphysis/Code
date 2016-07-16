// Tree Summing
// UVa ID: 112
// Verdict: Accepted
// Submission Date: 2016-04-04
// UVa Run Time: 0.042s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 本题可以归结为数据结构问题。
//
// 使用链表来表示树，若是使用数组，可能因为树的深度较大导致数组过大。关键是如何将输入
// 解析成链表表示的树，本题解利用了 cin.putback() 帮助完成。解析完成，剩下的就是树遍
// 历的问题了。

#include <iostream>

using namespace std;

struct node
{
    int value;
    node *parent, *leftChild, *rightChild;
};

bool pathSumFound, emptyTree;
int pathSum;

// 前序遍历，将路径和保存在叶子节点上。
void summingTree(node *current)
{
    if (pathSumFound)
        return;
        
    if (current->leftChild != NULL)
    {
        current->leftChild->value += current->value;
        summingTree(current->leftChild);
    }
    
    if (current->rightChild != NULL)
    {
        current->rightChild->value += current->value;
        summingTree(current->rightChild);
    }
    
    if (current->leftChild == NULL &&
        current->rightChild == NULL && current->value == pathSum)
    {
        pathSumFound = true;
    }
}

// 利用递归和cin.putback()，将输入解析为链表表示的树。
void parseTree(node *current)
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
        current->value = number * sign;
    }
    else
    {
        cin.putback(c);

        // 若当前节点为空，则将父节点的相应子节点设为空。
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

    // 若不是叶子节点，则继续解析子树。
    if (!isLeaf)
    {
        node *left = new node;
        current->leftChild = left;
        left->parent = current;
        parseTree(left);

        node *right = new node;
        current->rightChild = right;
        right->parent = current;
        parseTree(right);
    }

    while (cin >> c, c != ')')
        ;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int targetSum;
    while (cin >> pathSum)
    {
        node *root = new node;

        emptyTree = false;
        parseTree(root);

        pathSumFound = false;
        if (!emptyTree)
            summingTree(root);
            
        cout << (pathSumFound ? "yes\n" : "no\n");

        delete root;
    }

    return 0;
}
