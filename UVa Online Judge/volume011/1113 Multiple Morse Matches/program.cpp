// Multiple Morse Matches
// UVa ID: 1113
// Verdict: Accepted
// Submission Date: 2026-05-30
// UVa Run Time: 0.110s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 字母到莫尔斯码的映射
const string morseMap[26] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};

// 将单词转换为莫尔斯码
string wordToMorse(const string& word) {
    string res = "";
    for (char c : word) res += morseMap[c - 'A'];
    return res;
}

// Trie 树节点
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    vector<int> wordLengths; // 存储以当前节点结尾的单词的莫尔斯码长度
    
    TrieNode() {}
};

// 向 Trie 中插入莫尔斯码单词
void insertTrie(TrieNode* root, const string& morse, int len) {
    TrieNode* node = root;
    for (char c : morse) {
        if (!node->children.count(c))
            node->children[c] = new TrieNode();
        node = node->children[c];
    }
    node->wordLengths.push_back(len);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    
    for (int caseNum = 0; caseNum < T; ++caseNum) {
        if (caseNum > 0) cout << "\n"; // 用例之间空行
        
        string morse;
        cin >> morse; // 莫尔斯码字符串（连续，无空格）
        
        int N;
        cin >> N;
        
        // 构建 Trie 树
        TrieNode* root = new TrieNode();
        for (int i = 0; i < N; ++i) {
            string word;
            cin >> word;
            string morseWord = wordToMorse(word);
            insertTrie(root, morseWord, (int)morseWord.length());
        }
        
        int len = (int)morse.length();
        vector<long long> dp(len + 1, 0);
        dp[0] = 1;
        
        // 动态规划
        for (int i = 0; i < len; ++i) {
            if (dp[i] == 0) continue;
            
            TrieNode* node = root;
            // 从位置 i 开始向后匹配
            for (int j = i; j < len; ++j) {
                char c = morse[j];
                if (!node->children.count(c)) break;
                node = node->children[c];
                
                // 检查是否有单词在此结束
                for (int wlen : node->wordLengths) {
                    if (i + wlen <= len) {
                        dp[i + wlen] += dp[i];
                    }
                }
            }
        }
        
        cout << dp[len] << "\n";
        
        // 释放 Trie 内存（为简洁起见省略，实际竞赛中可接受）
    }
    
    return 0;
}
