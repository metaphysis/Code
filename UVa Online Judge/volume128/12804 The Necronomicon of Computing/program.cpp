// The Necronomicon of Computing
// UVa ID: 12804
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int L;
        cin >> L;
        int totalNodes = L + 1;                 // 节点 1..L，L+1 为终止状态
        vector<vector<int>> adj(totalNodes + 1); // 出边
        vector<vector<int>> pred(totalNodes + 1); // 入边（前驱）
        vector<int> outDeg(totalNodes + 1, 0);   // 出度
        for (int i = 1; i <= L; ++i) {
            string op;
            cin >> op;
            if (op == "A") {
                int nxt = i + 1;
                adj[i].push_back(nxt);
                pred[nxt].push_back(i);
                outDeg[i] = 1;
            } else if (op == "J") {
                int N;
                cin >> N;
                adj[i].push_back(N);
                pred[N].push_back(i);
                outDeg[i] = 1;
            } else { // "C"
                int N;
                cin >> N;
                int nxt1 = N;
                int nxt2 = i + 1;
                adj[i].push_back(nxt1);
                pred[nxt1].push_back(i);
                adj[i].push_back(nxt2);
                pred[nxt2].push_back(i);
                outDeg[i] = 2;
            }
        }
        // 计算所有“必然终止”的节点（good）
        vector<bool> good(totalNodes + 1, false);
        vector<int> cnt = outDeg;          // 剩余未确定为 good 的后继数量
        queue<int> q;
        good[L + 1] = true;
        q.push(L + 1);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u : pred[v]) {
                if (!good[u]) {
                    --cnt[u];
                    if (cnt[u] == 0) {
                        good[u] = true;
                        q.push(u);
                    }
                }
            }
        }
        if (good[1]) cout << "ALWAYS\n";
        else {
            // 检查是否存在路径到达 L+1（可达性）
            vector<bool> visited(totalNodes + 1, false);
            stack<int> st;
            st.push(1);
            visited[1] = true;
            bool reachable = false;
            while (!st.empty()) {
                int u = st.top(); st.pop();
                if (u == L + 1) {
                    reachable = true;
                    break;
                }
                for (int nxt : adj[u]) {
                    if (!visited[nxt]) {
                        visited[nxt] = true;
                        st.push(nxt);
                    }
                }
            }
            if (!reachable) cout << "NEVER\n";
            else cout << "SOMETIMES\n";
        }
    }
    return 0;
}
