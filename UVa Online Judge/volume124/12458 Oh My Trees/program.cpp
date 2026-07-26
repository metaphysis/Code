// Oh My Trees
// UVa ID: 12458
// Verdict: Accepted
// Submission Date: 2026-07-
// UVa Run Time: s
// https://blog.csdn.net/metaphysis/article/details/163173402

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    string line;
    getline(cin, line); // 跳过第一行后的换行
    while (T--) {
        int H;
        cin >> H;
        getline(cin, line); // 跳过 H 后的换行
        vector<int> inputOrder;                 // 按输入顺序存储所有键
        unordered_map<int, int> depthMap;       // 键 -> 深度 (0-based)
        for (int level = 0; level < H; ++level) {
            getline(cin, line);
            stringstream ss(line);
            int key;
            while (ss >> key) {
                inputOrder.push_back(key);
                depthMap[key] = level;
            }
        }
        // 排序得到中序序列
        vector<int> sortedKeys = inputOrder;
        sort(sortedKeys.begin(), sortedKeys.end());
        unordered_map<int, int> leftChild, rightChild; // 存储孩子的键值，不存在则不记录
        vector<int> stk; // 单调栈，存储键值
        for (int key : sortedKeys) {
            int last = -1;
            // 弹出深度大于当前深度的节点
            while (!stk.empty() && depthMap[stk.back()] > depthMap[key]) {
                last = stk.back();
                stk.pop_back();
            }
            if (last != -1)
                leftChild[key] = last;
            if (!stk.empty())
                rightChild[stk.back()] = key;
            stk.push_back(key);
        }
        // 按输入顺序输出
        for (int key : inputOrder) {
            cout << key << ":";
            auto itL = leftChild.find(key);
            if (itL != leftChild.end()) cout << itL->second;
            cout << "-";
            auto itR = rightChild.find(key);
            if (itR != rightChild.end()) cout << itR->second;
            cout << "\n";
        }
    }
    return 0;
}
