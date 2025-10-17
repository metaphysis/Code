// Hyper Prefix Sets
// UVa ID: 11488
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.070s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Trie 节点结构
struct TrieNode {
    TrieNode* child[2];  // 子节点，0 和 1 两个分支
    int cnt;             // 经过该节点的字符串数量
    TrieNode() {
        child[0] = child[1] = nullptr;
        cnt = 0;
    }
};

int ans;  // 记录最大前缀优度

// DFS 遍历 Trie，计算每个节点的 depth * cnt
void dfs(TrieNode* node, int depth) {
    if (node == nullptr) return;
    // 更新最大前缀优度
    ans = max(ans, depth * node->cnt);
    // 递归遍历两个子节点
    for (int i = 0; i < 2; i++) {
        if (node->child[i] != nullptr) {
            dfs(node->child[i], depth + 1);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    TrieNode* root = new TrieNode();  // 创建 Trie 根节点
    // 插入所有字符串到 Trie 中
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        TrieNode* cur = root;
        for (char ch : s) {
            int idx = ch - '0';  // 将字符 '0'/'1' 转换为索引 0/1
            // 如果子节点不存在，则创建
            if (cur->child[idx] == nullptr) {
                cur->child[idx] = new TrieNode();
            }
            cur = cur->child[idx];  // 移动到子节点
            cur->cnt++;  // 增加经过该节点的计数
        }
    }
    ans = 0;
    dfs(root, 0);  // 从根节点开始 DFS，深度为 0
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
