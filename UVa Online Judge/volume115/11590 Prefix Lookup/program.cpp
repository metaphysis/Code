// Prefix Lookup
// UVa ID: 11590
// Verdict: Accepted
// Submission Date: 2025-11-26
// UVa Run Time: 0.440s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* children[2];
    bool hasPrefix;  // 是否有前缀在此结束
    int prefixLen;   // 前缀长度
    
    TrieNode() : hasPrefix(false), prefixLen(-1) {
        children[0] = children[1] = nullptr;
    }
};

class PrefixTrie {
private:
    TrieNode* root;
    int addressBits;
    map<string, __int128> results;
    
    void insert(const string& prefix) {
        TrieNode* node = root;
        int len = prefix.length() - 1;
        for (int i = 0; i < len; i++) {
            int bit = prefix[i] - '0';
            if (!node->children[bit]) {
                node->children[bit] = new TrieNode();
            }
            node = node->children[bit];
        }
        if (!node->hasPrefix) {
            node->hasPrefix = true;
            node->prefixLen = len;
        }
    }
    
    __int128 calculateExclusive(TrieNode* node, int depth, int bestLen) {
        if (!node) return 0;
        
        // 如果当前节点有前缀且比之前的最佳匹配更长，更新最佳匹配
        int currentBest = bestLen;
        if (node->hasPrefix && node->prefixLen > bestLen) {
            currentBest = node->prefixLen;
        }
        
        // 如果是叶子节点，计算这个路径的匹配结果
        if (depth == addressBits || (!node->children[0] && !node->children[1])) {
            if (currentBest == -1) {
                // 匹配默认前缀 "*"
                return __int128(1) << (addressBits - depth);
            }
            return 0;
        }
        
        __int128 result = 0;
        for (int i = 0; i < 2; i++) {
            if (node->children[i]) {
                result += calculateExclusive(node->children[i], depth + 1, currentBest);
            } else {
                // 没有子节点，继续使用当前最佳匹配
                if (currentBest == -1) {
                    result += __int128(1) << (addressBits - depth - 1);
                }
            }
        }
        return result;
    }
    
    void collectResults(TrieNode* node, const string& path, int depth) {
        if (!node) return;
        
        // 如果当前节点有前缀，计算它的独占匹配数
        if (node->hasPrefix) {
            string prefix = path + "*";
            // 临时计算这个前缀的匹配数
            __int128 count = 0;
            
            // 计算以这个节点为最佳匹配的地址数量
            stack<pair<TrieNode*, int>> st;
            st.push({node, depth});
            
            while (!st.empty()) {
                auto [curr, currDepth] = st.top();
                st.pop();
                
                if (currDepth == addressBits || (!curr->children[0] && !curr->children[1])) {
                    count += __int128(1) << (addressBits - currDepth);
                    continue;
                }
                
                for (int i = 0; i < 2; i++) {
                    if (curr->children[i]) {
                        // 检查子节点是否有更长的前缀
                        bool hasLonger = false;
                        TrieNode* child = curr->children[i];
                        if (child->hasPrefix && child->prefixLen > node->prefixLen) {
                            hasLonger = true;
                        }
                        
                        if (!hasLonger) {
                            st.push({child, currDepth + 1});
                        }
                    } else {
                        // 没有子节点，这个分支完全匹配当前前缀
                        count += __int128(1) << (addressBits - currDepth - 1);
                    }
                }
            }
            
            results[prefix] = count;
        }
        
        // 递归处理子节点
        for (int i = 0; i < 2; i++) {
            if (node->children[i]) {
                collectResults(node->children[i], path + char('0' + i), depth + 1);
            }
        }
    }
    
    void destroy(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < 2; i++) {
            destroy(node->children[i]);
        }
        delete node;
    }
    
public:
    PrefixTrie(int bits) : addressBits(bits) {
        root = new TrieNode();
        root->hasPrefix = true;  // 默认前缀 "*"
        root->prefixLen = 0;
    }
    
    ~PrefixTrie() {
        destroy(root);
    }
    
    void addPrefix(const string& prefix) {
        if (prefix == "*") return;  // 根节点已经处理了默认前缀
        insert(prefix);
    }
    
    map<string, __int128> calculateMatches() {
        results.clear();
        
        // 计算默认前缀 "*" 的匹配数
        __int128 defaultCount = __int128(1) << addressBits;
        TrieNode* node = root;
        
        // 减去被其他前缀覆盖的地址
        stack<pair<TrieNode*, int>> st;
        st.push({root, 0});
        
        while (!st.empty()) {
            auto [curr, currDepth] = st.top();
            st.pop();
            
            if (currDepth > 0 && curr->hasPrefix && curr->prefixLen > 0) {
                // 被其他前缀覆盖，从默认前缀中减去
                defaultCount -= results[getPrefixString(curr, currDepth)];
                continue;
            }
            
            for (int i = 0; i < 2; i++) {
                if (curr->children[i]) {
                    st.push({curr->children[i], currDepth + 1});
                }
            }
        }
        
        results["*"] = defaultCount;
        
        // 收集其他前缀的结果
        collectResults(root, "", 0);
        
        return results;
    }
    
private:
    string getPrefixString(TrieNode* node, int depth) {
        // 这个函数需要重构，暂时返回空字符串
        return "";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m && (n || m)) {
        vector<string> prefixes;
        
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            prefixes.push_back(s);
        }

        PrefixTrie trie(m);
        for (const auto& prefix : prefixes) {
            trie.addPrefix(prefix);
        }
        
        auto matches = trie.calculateMatches();

        int k;
        cin >> k;
        while (k--) {
            string q;
            cin >> q;
            __int128 val = matches[q];
            
            // 输出大整数
            string output;
            __int128 temp = val;
            do {
                output = char('0' + (temp % 10)) + output;
                temp /= 10;
            } while (temp > 0);
            cout << output << "\n";
        }
        cout << "\n";
    }

    return 0;
}
