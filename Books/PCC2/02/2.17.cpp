// binary search tree

#include <bits/stdc++.h>
using namespace std;

//++++++++++++++++++++++++++++++2.17.cpp++++++++++++++++++++++++++++++//
struct TreeNode {
    int key;
    TreeNode *leftChild, *rightChild;
};

// 查找
TreeNode* find(TreeNode* node, int key)
{
    if (node == nullptr) return nullptr;
    if (node->key == key) return node;
    if (node->key > key) return find(node->leftChild, key);
    else return find(node->rightChild, key);
}

// 插入
void insert(TreeNode* &node, int key)
{
    if (node == nullptr) {
        node = new TreeNode;
        node->key = key;
        node->leftChild = node->rightChild = nullptr;
    }
    if (node->key == key) return;
    if (node->key > key) insert(node->leftChild, key);
    else insert(node->rightChild, key);
}

// 删除
TreeNode* remove(TreeNode* &node, int key)
{
    if (node == nullptr) return node;
    if (key < node->key) return remove(node->leftChild, key);
    if (key > node->key) return remove(node->rightChild, key);
    if (node->leftChild == nullptr && node->rightChild == nullptr) {
        node = nullptr;
        return node;
    }
    if (node->leftChild != nullptr && node->rightChild == nullptr) {
        node = node->leftChild;
        return node;
    }
    if (node->leftChild == nullptr && node->rightChild != nullptr) {
        node = node->rightChild;
        return node;
    }
    // 查找左子树中的最大值
    TreeNode* tmp = node->leftChild;
    int maxInLeftTree = 0;
    while (tmp != nullptr) {
        maxInLeftTree = tmp->key;
        tmp = tmp->rightChild;
    }
    node->key = maxInLeftTree;
    node->leftChild = remove(node->leftChild, maxInLeftTree);
    return node;
}
//++++++++++++++++++++++++++++++2.17.cpp++++++++++++++++++++++++++++++//

void printUsage()
{
    cout << "usage: bst <command> <args>\n";
    cout << "The most commonly used git commands are:\n";
    cout << "insert insert a node to BST with specifed key\n";
    cout << "find   find a node in BST with specified key\n";
    cout << "remove remove a node in BST with specified key\n";
    cout << "exit   exit the program\n";
}

void traversal(TreeNode* root)
{
    if (root == nullptr) return;
    traversal(root->leftChild);
    cout << root->key << '\n';
    traversal(root->rightChild);
}

int main(int argc, char* argv[])
{
    string command1, command2;
    TreeNode *root = nullptr;
    int n;
    while (true)
    {
        cin >> command1;
        if (command1 != "bst") { cin.ignore(1024, '\n'); printUsage(); continue; }
        cin >> command2;
        if (command2 == "insert")
        {
            cin >> n;
            insert(root, n);
        }
        else if (command2 == "find")
        {
            cin >> n;
            if (root == nullptr) { cout << "The tree is empty.\n"; continue; }
            TreeNode* nd = find(root, n);
            if (nd == nullptr) cout << "The node with specified key not exist.\n";
            else cout << "The node with specified key is " << nd << '\n';
        }
        else if (command2 == "remove")
        {
            cin >> n;
            if (root == nullptr) { cout << "The tree is empty.\n"; continue; }
            remove(root, n);
        }
        else if (command2 == "print")
        {
            traversal(root);
        }
        else if (command2 == "exit")
        {
            break;
        }
        else
        {
            cin.ignore(1024, '\n'); printUsage(); continue;
        }
    }

    return 0;
}
