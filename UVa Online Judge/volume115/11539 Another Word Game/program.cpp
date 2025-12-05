// Another Word Game
// UVa ID: 11539
// Verdict: Accepted
// Submission Date: 2025-12-05
// UVa Run Time: 2.480s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_S_LEN = 10010;
const int MAX_WORD_LEN = 110;

struct TrieNode {
    int weight; // 单词结尾处的权重，-1表示不是单词结尾
    TrieNode* children[26];
    TrieNode() {
        weight = -1;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

void insertWord(TrieNode* root, const string& word, int w) {
    TrieNode* cur = root;
    for (char ch : word) {
        int idx = ch - 'a';
        if (cur->children[idx] == nullptr)
            cur->children[idx] = new TrieNode();
        cur = cur->children[idx];
    }
    cur->weight = w; // 记录该单词的权重
}

void destroy(TrieNode *root) {
    if (root == nullptr) return;
    for (int i = 0; i < 26; i++)
        destroy(root->children[i]);
    delete root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int caseNo = 1; caseNo <= t; caseNo++) {
        int n, penalty;
        cin >> n >> penalty;
        TrieNode* root = new TrieNode();
        for (int i = 0; i < n; i++) {
            string word;
            int w;
            cin >> word >> w;
            insertWord(root, word, w);
        }
        string s;
        cin >> s;
        int len = s.length();
        vector<long long> dp(len + 1, LLONG_MIN); // dp[i]表示处理完前i个字符的最大得分
        dp[0] = 0;
        for (int i = 0; i < len; i++) {
            if (dp[i] == LLONG_MIN) continue;
            TrieNode* cur = root;
            for (int j = i; j < len; j++) { // 枚举以i开头的子串
                int idx = s[j] - 'a';
                int wordLen = j - i + 1;
                // 无论是否匹配单词，都可以选择按非单词处理并扣分
                dp[j + 1] = max(dp[j + 1], dp[i] - penalty * wordLen);
                // 尝试匹配单词
                if (cur->children[idx] == nullptr) break; // 此后缀不在字典中，停止继续扩展
                cur = cur->children[idx];
                if (cur->weight != -1) // 构成一个字典中的单词
                    dp[j + 1] = max(dp[j + 1], dp[i] + cur->weight);
            }
        }
        cout << "Case " << caseNo << ": " << dp[len] << "\n";
        //destroy(root);
    }
    return 0;
}
