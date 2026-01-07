// Phylogenetic Trees Inherited
// UVa ID: 10185
// Verdict: Accepted
// Submission Date: 2025-12-31
// UVa Run Time: 0.370s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 氨基酸到索引的映射表
const string aminoAcids = "ARNDCQEGHILKMFPSTWYV";
int aminoIndex[256];

// 初始化映射表
void initAminoIndex() {
    for (int i = 0; i < 20; ++i) aminoIndex[aminoAcids[i]] = i;
}

// 计算一个位置的最小成本和最优字符
pair<char, int> solvePosition(const vector<char>& leaves, int n) {
    // 计算树的高度
    int maxDepth = 0;
    int temp = n;
    while (temp > 1) {
        maxDepth++;
        temp >>= 1;
    }
    
    // 完全二叉树的节点总数
    int totalNodes = (1 << (maxDepth + 1)) - 1;
    vector<vector<int> > dp(totalNodes, vector<int>(20, INT_MAX / 2));
    
    // 叶节点索引顺序（从左到右）
    vector<int> leafIdx(n);
    for (int i = 0; i < n; ++i) leafIdx[i] = i;
    
    // 使用栈模拟后序遍历，避免递归
    int leafCounter = 0;
    stack<pair<int, int> > st;
    st.push(make_pair(0, 0)); // (node, depth)
    
    vector<pair<int, int> > traversalOrder;
    vector<int> parent(totalNodes, -1);
    vector<bool> processed(totalNodes, false);
    
    // 生成后序遍历的顺序
    while (!st.empty()) {
        int node = st.top().first;
        int depth = st.top().second;
        st.pop();
        
        traversalOrder.push_back(make_pair(node, depth));
        
        if (depth < maxDepth) {
            int left = node * 2 + 1;
            int right = node * 2 + 2;
            st.push(make_pair(right, depth + 1));
            st.push(make_pair(left, depth + 1));
            parent[left] = node;
            parent[right] = node;
        }
    }
    
    // 逆序处理（后序遍历）
    reverse(traversalOrder.begin(), traversalOrder.end());
    for (int i = 0; i < traversalOrder.size(); ++i) {
        int node = traversalOrder[i].first;
        int depth = traversalOrder[i].second;
        
        if (depth == maxDepth) {
            // 叶节点：字符固定
            for (int c = 0; c < 20; ++c) {
                dp[node][c] = (aminoAcids[c] == leaves[leafCounter]) ? 0 : INT_MAX / 2;
            }
            leafCounter++;
        } else {
            int left = node * 2 + 1;
            int right = node * 2 + 2;
            
            // 对于每个可能的字符c，计算dp[node][c]
            for (int c = 0; c < 20; ++c) {
                int leftBest = INT_MAX / 2;
                for (int cl = 0; cl < 20; ++cl) {
                    int cost = dp[left][cl] + (c != cl);
                    if (cost < leftBest) leftBest = cost;
                }
                
                int rightBest = INT_MAX / 2;
                for (int cr = 0; cr < 20; ++cr) {
                    int cost = dp[right][cr] + (c != cr);
                    if (cost < rightBest) rightBest = cost;
                }
                
                dp[node][c] = leftBest + rightBest;
            }
        }
    }
    
    // 根节点是0，选择最小成本的字符（字典序优先）
    int bestChar = 0;
    int minCost = dp[0][0];
    for (int c = 1; c < 20; ++c) {
        if (dp[0][c] < minCost || (dp[0][c] == minCost && aminoAcids[c] < aminoAcids[bestChar])) {
            minCost = dp[0][c];
            bestChar = c;
        }
    }
    
    return make_pair(aminoAcids[bestChar], minCost);
}

int main() {
    initAminoIndex();
    int n, l;
    while (cin >> n >> l && (n != 0 || l != 0)) {
        vector<string> leaves(n);
        for (int i = 0; i < n; ++i) cin >> leaves[i];
        
        string rootSeq(l, ' ');
        int totalCost = 0;
        
        // 对每个位置独立求解
        for (int pos = 0; pos < l; ++pos) {
            vector<char> leafChars(n);
            for (int i = 0; i < n; ++i) leafChars[i] = leaves[i][pos];
            pair<char, int> result = solvePosition(leafChars, n);
            rootSeq[pos] = result.first;
            totalCost += result.second;
        }
        
        cout << rootSeq << " " << totalCost << endl;
    }
    return 0;
}
