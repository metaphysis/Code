// Remember the Word
// UVa ID: 1401
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.100s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

const int MOD = 20071027; // 取模值
const int MAXN = 300010; // 最大字符串长度
const int ALPHABET = 26; // 字母表大小

int dp[MAXN]; // dp数组

// Trie树节点结构
struct TrieNode {
    TrieNode* children[ALPHABET]; // 子节点指针数组
    vector<int> wordLengths; // 存储以此节点结尾的单词长度
    TrieNode() {
        memset(children, 0, sizeof(children)); // 初始化子节点为空
    }
};

// 向Trie树中插入单词
void insert(TrieNode* root, const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        int idx = ch - 'a'; // 计算字母索引
        if (!node->children[idx]) {
            node->children[idx] = new TrieNode(); // 创建新节点
        }
        node = node->children[idx];
    }
    node->wordLengths.push_back(word.length()); // 记录单词长度
}

// 递归清理Trie树内存
void clearTrie(TrieNode* root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET; i++) {
        clearTrie(root->children[i]); // 递归清理子节点
    }
    delete root; // 删除当前节点
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string text;
    int caseNum = 1;
    while (cin >> text) { // 读取每个测试用例的目标字符串
        int S;
        cin >> S; // 读取字典大小
        TrieNode* root = new TrieNode(); // 创建Trie根节点
        
        // 插入所有字典单词
        for (int i = 0; i < S; i++) {
            string word;
            cin >> word;
            insert(root, word);
        }
        
        int n = text.length();
        memset(dp, 0, sizeof(dp)); // 初始化dp数组
        dp[0] = 1; // 空串有1种划分方式
        
        // 动态规划过程
        for (int i = 0; i < n; i++) {
            if (dp[i] == 0) continue; // 如果当前位置不可达，跳过
            TrieNode* node = root;
            // 从位置i开始，在Trie中最多匹配100个字符
            for (int j = i; j < n && j - i < 100; j++) {
                int idx = text[j] - 'a';
                if (!node->children[idx]) break; // 无匹配，退出
                node = node->children[idx];
                // 遍历所有以当前节点结尾的单词
                for (int len : node->wordLengths) {
                    if (i + len <= n) {
                        dp[i + len] = (dp[i + len] + dp[i]) % MOD; // 状态转移
                    }
                }
            }
        }
        
        cout << "Case " << caseNum++ << ": " << dp[n] << "\n"; // 输出结果
        clearTrie(root); // 清理Trie树内存
    }
    
    return 0;
}
