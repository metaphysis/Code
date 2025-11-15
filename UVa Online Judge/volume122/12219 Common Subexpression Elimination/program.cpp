// Common Subexpression Elimination
// UVa ID: 12219
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.860s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>
using namespace std;

struct Node {
    string name;
    Node* left;
    Node* right;
    int treeId; // 规范化id，用于判断子树是否相同

    Node(const string& n) : name(n), left(nullptr), right(nullptr), treeId(0) {}
};

// 解析表达式
Node* parse(const string& s, int& p) {
    int start = p;
    while (p < s.length() && islower(s[p])) p++;
    string name = s.substr(start, p - start);
    Node* node = new Node(name);

    if (p < s.length() && s[p] == '(') {
        p++; // '('
        node->left = parse(s, p);
        p++; // ','
        node->right = parse(s, p);
        p++; // ')'
    }
    return node;
}

// 规范化子树，分配 treeId
void normalize(Node* node, map<tuple<string, int, int>, int>& treeIdMap, int& idCounter) {
    if (!node) return;
    normalize(node->left, treeIdMap, idCounter);
    normalize(node->right, treeIdMap, idCounter);

    int leftId = node->left ? node->left->treeId : 0;
    int rightId = node->right ? node->right->treeId : 0;
    auto key = make_tuple(node->name, leftId, rightId);

    if (treeIdMap.count(key)) {
        node->treeId = treeIdMap[key];
    } else {
        node->treeId = ++idCounter;
        treeIdMap[key] = node->treeId;
    }
}

// 输出表达式，分配输出编号
void print(Node* node, map<int, int>& outputIdMap, int& outputIdCounter) {
    if (!node) return;

    // 检查该子树是否已经分配输出编号
    if (outputIdMap.count(node->treeId)) {
        cout << outputIdMap[node->treeId];
        return;
    }

    // 第一次输出该子树
    cout << node->name;
    // 立即分配输出编号，这样后续引用时这个节点已经输出
    outputIdMap[node->treeId] = ++outputIdCounter;
    if (node->left) {
        cout << '(';
        print(node->left, outputIdMap, outputIdCounter);
        cout << ',';
        print(node->right, outputIdMap, outputIdCounter);
        cout << ')';
    }
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        string s;
        cin >> s;
        int p = 0;
        Node* root = parse(s, p);

        // 规范化
        map<tuple<string, int, int>, int> treeIdMap;
        int treeIdCounter = 0;
        normalize(root, treeIdMap, treeIdCounter);

        // 输出
        map<int, int> outputIdMap; // treeId -> outputId
        int outputIdCounter = 0;
        print(root, outputIdMap, outputIdCounter);
        cout << endl;

        // 清理内存（略）
    }
    return 0;
}
