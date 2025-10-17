// Tree Reconstruction
// UVa ID: 10410
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> pos(n + 1);  // 记录每个节点在BFS中的位置
        vector<vector<int>> children(n + 1);  // 存储每个节点的子节点列表
        
        // 读取BFS序列并记录位置
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            pos[x] = i;
        }
        
        // 读取DFS序列
        vector<int> dfs(n);
        for (int i = 0; i < n; i++) {
            cin >> dfs[i];
        }
        
        int root = dfs[0];  // DFS第一个节点是根节点
        stack<int> st;
        st.push(root);
        
        // 处理DFS序列的剩余节点
        for (int i = 1; i < n; i++) {
            int x = dfs[i];  // 当前处理的节点
            while (true) {
                int u = st.top();  // 栈顶节点
                // 关键判断：如果u是根节点，或者x在BFS中的位置足够靠后
                if (u == root || pos[u] + 1 < pos[x]) {
                    children[u].push_back(x);  // x是u的子节点
                    st.push(x);  // 将x压入栈，因为它可能是后续节点的父节点
                    break;
                } else {
                    st.pop();  // u没有更多子节点，弹出
                }
            }
        }
        
        // 输出结果
        for (int i = 1; i <= n; i++) {
            cout << i << ":";
            // 对子节点排序以满足题目要求的升序输出
            sort(children[i].begin(), children[i].end());
            for (int child : children[i]) {
                cout << " " << child;
            }
            cout << endl;
        }
    }
    return 0;
}
