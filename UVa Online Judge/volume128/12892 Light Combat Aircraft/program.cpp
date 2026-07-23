// Light Combat Aircraft
// UVa ID: 12892
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N;
        cin >> N;
        vector<vector<int>> childList(N + 1);
        vector<int> parentArr(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            int p;
            cin >> p;
            parentArr[i] = p;
            if (p != 0) childList[p].push_back(i);
        }
        vector<int> rootList;
        for (int i = 1; i <= N; ++i)
            if (parentArr[i] == 0) rootList.push_back(i);
        vector<long long> subtreeSize(N + 1, 0);
        // 对每棵树后序遍历计算子树大小
        for (int root : rootList) {
            vector<int> order;
            stack<int> st;
            st.push(root);
            while (!st.empty()) {
                int u = st.top(); st.pop();
                order.push_back(u);
                for (int v : childList[u]) st.push(v);
            }
            // 逆序即为后序
            for (int i = (int)order.size() - 1; i >= 0; --i) {
                int u = order[i];
                long long sz = 1;
                for (int v : childList[u]) sz += subtreeSize[v];
                subtreeSize[u] = sz;
            }
        }
        vector<long long> answerCount(N + 1, 0);
        for (int u = 1; u <= N; ++u) {
            long long total = subtreeSize[u] * (subtreeSize[u] - 1) / 2;
            for (int v : childList[u])
                total -= subtreeSize[v] * (subtreeSize[v] - 1) / 2;
            answerCount[u] = total;
        }
        cout << "Forest#" << caseNo << ":";
        for (int i = 1; i <= N; ++i) cout << " " << answerCount[i];
        cout << "\n";
    }
    return 0;
}
