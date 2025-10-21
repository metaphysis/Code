// Cellphone Typing
// UVa ID: 12526
// Verdict: Accepted
// Submission Date: 2025-10-21
// UVa Run Time: 0.290s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int ALPHABET = 26;  // 小写字母数量

struct TrieNode {
    TrieNode* children[ALPHABET];  // 子节点指针数组
    int childCount;                 // 子节点数量
    bool isEndOfWord;               // 标记当前节点是否是单词结尾

    TrieNode() {
        memset(children, 0, sizeof(children));  // 初始化子节点为空
        childCount = 0;
        isEndOfWord = false;
    }
};

// 向 Trie 中插入单词
void insert(TrieNode* root, const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        int idx = ch - 'a';  // 计算字母对应的索引
        if (!node->children[idx]) {
            node->children[idx] = new TrieNode();
            node->childCount++;  // 新增子节点，计数增加
        }
        node = node->children[idx];
    }
    node->isEndOfWord = true;  // 标记单词结尾
}

// 计算输入单个单词所需的击键次数
int countKeystrokes(TrieNode* root, const string& word) {
    int keystrokes = 1;  // 第一个字母必须手动输入
    TrieNode* node = root->children[word[0] - 'a'];  // 移动到第一个字母对应的节点
    
    for (size_t i = 1; i < word.length(); i++) {
        // 如果当前节点是单词结尾或有多个子节点，需要手动输入下一个字母
        if (node->childCount > 1 || node->isEndOfWord) {
            keystrokes++;
        }
        node = node->children[word[i] - 'a'];  // 移动到下一个字母的节点
    }
    return keystrokes;
}

// 递归释放 Trie 内存
void clearTrie(TrieNode* node) {
    for (int i = 0; i < ALPHABET; i++) {
        if (node->children[i]) {
            clearTrie(node->children[i]);
            delete node->children[i];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<string> words(N);
        TrieNode* root = new TrieNode();

        // 读取所有单词并构建 Trie
        for (int i = 0; i < N; i++) {
            cin >> words[i];
            insert(root, words[i]);
        }

        // 计算总击键次数
        int totalKeystrokes = 0;
        for (const string& w : words) {
            totalKeystrokes += countKeystrokes(root, w);
        }

        // 计算并输出平均值
        double average = static_cast<double>(totalKeystrokes) / N;
        cout << fixed << setprecision(2) << average << "\n";

        // 释放 Trie 内存
        clearTrie(root);
        delete root;
    }

    return 0;
}
