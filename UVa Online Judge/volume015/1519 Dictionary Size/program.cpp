// Dictionary Size
// UVa ID: 1519
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 1.210s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    int next[26];
    TrieNode() { fill(next, next + 26, -1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        unordered_set<string> suffixSet;
        suffixSet.reserve(n * 45);          // 预分配
        vector<TrieNode> trie(1);           // 根节点
        long long firstLevelCount = 0;      // 不同首字母数（长度1前缀数）
        long long lastCharCount[26] = {};   // 长度≥2前缀的末尾字符计数
        bool singleLetter[26] = {};         // 是否存在单字母词典词
        // 插入所有单词，构建Trie
        for (int i = 0; i < n; ++i) {
            string word;
            cin >> word;
            if (word.size() == 1) singleLetter[word[0] - 'a'] = true;
            int node = 0;
            for (int j = 0; j < (int)word.size(); ++j) {
                int c = word[j] - 'a';
                if (trie[node].next[c] == -1) {
                    trie[node].next[c] = (int)trie.size();
                    trie.emplace_back();
                    if (j == 0) ++firstLevelCount;
                    else ++lastCharCount[c];
                }
                node = trie[node].next[c];
            }
            // 收集该单词的所有后缀
            for (int j = 0; j < (int)word.size(); ++j) suffixSet.insert(word.substr(j));
        }
        // 统计 good[c]：以 c 开头的可缩短后缀数量
        long long good[26] = {};
        for (const string &s : suffixSet) {
            if (s.size() <= 1)
                continue;
            string shorter = s.substr(1);
            if (suffixSet.count(shorter)) ++good[s[0] - 'a'];
        }
        long long suffixCount = (long long)suffixSet.size();
        long long ans = firstLevelCount * suffixCount;
        for (int i = 0; i < 26; ++i) ans += lastCharCount[i] * (suffixCount - good[i]);
        for (int i = 0; i < 26; ++i)
            if (singleLetter[i])
                ++ans;
        cout << ans << '\n';
    }
    return 0;
}
