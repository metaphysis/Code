// Falling Leaves
// UVa ID: 1525
// Verdict: Accepted
// Submission Date: 2025-12-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// BST 结点定义
struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char c) : data(c), left(nullptr), right(nullptr) {}
};

// 向 BST 插入一个字符
TreeNode* insertBST(TreeNode* root, char ch) {
    if (root == nullptr) return new TreeNode(ch);
    if (ch < root->data) root->left = insertBST(root->left, ch);
    else root->right = insertBST(root->right, ch);
    return root;
}

// 前序遍历并收集结果
void preorderTraversal(TreeNode* root, string& result) {
    if (root == nullptr) return;
    result.push_back(root->data);
    preorderTraversal(root->left, result);
    preorderTraversal(root->right, result);
}

int main() {
    string line;
    vector<vector<string>> allDataSets;

    // 读取所有数据集
    while (true) {
        vector<string> dataSet;
        while (cin >> line && line != "*" && line != "$") dataSet.push_back(line);
        allDataSets.push_back(dataSet);
        if (line == "$") break;
    }

    // 处理每个数据集
    for (const auto& dataSet : allDataSets) {
        TreeNode* root = nullptr;
        // 逆序插入：从最后一轮开始
        for (auto it = dataSet.rbegin(); it != dataSet.rend(); ++it) {
            for (char ch : *it) root = insertBST(root, ch);
        }
        string result;
        preorderTraversal(root, result);
        cout << result << endl;
    }

    return 0;
}

