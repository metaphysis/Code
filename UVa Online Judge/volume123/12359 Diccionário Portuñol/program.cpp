// Diccionario Portuñol
// UVa ID: 12359
// Verdict: Accepted
// Submission Date: 2026-01-13
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int ALPHABET = 26;  // 小写字母数量

// 字典树节点结构
struct TrieNode {
    int next[ALPHABET];  // 子节点指针
    bool end;            // 是否为一个单词的终点
    
    TrieNode() {
        // 初始化为-1表示没有子节点
        memset(next, -1, sizeof(next));
        end = false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int P, S;
    // 循环处理每个测试用例，直到遇到0 0
    while (cin >> P >> S && (P || S)) {
        // 构建前缀字典树并统计cnt数组
        vector<TrieNode> prefTrie(1);  // 根节点
        vector<long long> charCnt(ALPHABET, 0);  // cnt[c]: 字符c作为x的第一个字符出现的次数
        
        // 处理葡萄牙语单词（前缀）
        for (int i = 0; i < P; ++i) {
            string word;
            cin >> word;
            int node = 0;  // 从根节点开始
            
            // 插入单词的所有前缀
            for (int j = 0; j < word.size(); ++j) {
                int c = word[j] - 'a';  // 字符转换为0-25的索引
                
                // 如果当前节点的c子节点不存在，创建新节点
                if (prefTrie[node].next[c] == -1) {
                    prefTrie[node].next[c] = prefTrie.size();
                    prefTrie.emplace_back();
                    
                    // 如果不是第一个字符，统计c作为x的第一个字符
                    // j>0表示这个字符不是单词的第一个字符
                    if (j > 0) charCnt[c]++;
                }
                
                // 移动到子节点
                node = prefTrie[node].next[c];
                // 标记当前节点为一个前缀的终点
                prefTrie[node].end = true;
            }
        }
        
        // 统计不同前缀的数量
        long long totalPref = 0;
        for (int i = 1; i < (int)prefTrie.size(); ++i)
            if (prefTrie[i].end) totalPref++;
        
        // 构建后缀字典树（反转）并计算重复数
        vector<TrieNode> suffTrie(1);  // 根节点
        long long duplicates = 0;      // 重复数
        
        // 处理西班牙语单词（后缀）
        for (int i = 0; i < S; ++i) {
            string word;
            cin >> word;
            // 反转单词，以便构建后缀字典树
            reverse(word.begin(), word.end());
            int node = 0;  // 从根节点开始
            
            // 插入反转后的单词（代表后缀）
            for (int j = 0; j < word.size(); ++j) {
                int c = word[j] - 'a';  // 字符转换为0-25的索引
                
                // 如果当前节点的c子节点不存在，创建新节点
                if (suffTrie[node].next[c] == -1) {
                    suffTrie[node].next[c] = suffTrie.size();
                    suffTrie.emplace_back();
                    
                    // 如果不是第一个字符，累加重复数
                    // j>0表示这个字符不是单词的第一个字符
                    if (j > 0) duplicates += charCnt[c];
                }
                
                // 移动到子节点
                node = suffTrie[node].next[c];
                // 标记当前节点为一个后缀的终点
                suffTrie[node].end = true;
            }
        }
        
        // 统计不同后缀的数量
        long long totalSuff = 0;
        for (int i = 1; i < (int)suffTrie.size(); ++i)
            if (suffTrie[i].end) totalSuff++;
        
        // 输出结果：总组合数减去重复数
        cout << totalPref * totalSuff - duplicates << '\n';
    }
    
    return 0;
}
