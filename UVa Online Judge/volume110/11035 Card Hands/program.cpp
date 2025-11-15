// Card Hands
// UVa ID: 11035
// Verdict: Accepted
// Submission Date: 2025-11-15
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    unordered_map<string, TrieNode*> children;
};

int main() {
    int n;
    while (cin >> n && n) {
        TrieNode* root = new TrieNode();
        int nodeCount = 0;
        
        vector<vector<string>> hands(n);
        
        // 读取所有手牌
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            hands[i].resize(k);
            for (int j = 0; j < k; j++) {
                cin >> hands[i][j];
            }
        }
        
        // 从每手牌的末尾开始插入到Trie中
        for (int i = 0; i < n; i++) {
            TrieNode* curr = root;
            // 从最后一张牌开始向前插入
            for (int j = hands[i].size() - 1; j >= 0; j--) {
                string card = hands[i][j];
                if (curr->children.find(card) == curr->children.end()) {
                    curr->children[card] = new TrieNode();
                    nodeCount++;
                }
                curr = curr->children[card];
            }
        }
        
        cout << nodeCount << endl;
    }
    return 0;
}
