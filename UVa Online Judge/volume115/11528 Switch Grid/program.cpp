// Switch Grid
// UVa ID: 11528
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.050s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, M, S;
        cin >> N >> M >> S;
        int R = N - 1, C = M - 1;
        int V = R + C;
        vector<int> need(V, 0);
        vector<int> initRow(R);
        for (int i = 0; i < R; ++i) cin >> initRow[i];
        for (int i = 0; i < R; ++i) {
            int f;
            cin >> f;
            need[i] = initRow[i] ^ f;
        }
        vector<int> initCol(C);
        for (int j = 0; j < C; ++j) cin >> initCol[j];
        for (int j = 0; j < C; ++j) {
            int f;
            cin >> f;
            need[R + j] = initCol[j] ^ f;
        }
        vector<int> rows(S), cols(S);
        for (int i = 0; i < S; ++i) cin >> rows[i];
        for (int i = 0; i < S; ++i) cin >> cols[i];

        vector<vector<pair<int,int>>> adj(V);
        for (int i = 0; i < S; ++i) {
            int u = rows[i] - 1;
            int v = R + (cols[i] - 1);
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
        }

        vector<char> visited(V, 0);
        bool possible = true;
        for (int i = 0; i < V; ++i) if (!visited[i]) {
            int xorSum = 0;
            stack<int> st;
            st.push(i);
            visited[i] = 1;
            while (!st.empty()) {
                int u = st.top();
                st.pop();
                xorSum ^= need[u];
                for (auto &p : adj[u]) {
                    int v = p.first;
                    if (!visited[v]) {
                        visited[v] = 1;
                        st.push(v);
                    }
                }
            }
            if (xorSum != 0) {
                possible = false;
                break;
            }
        }

        if (!possible) {
            cout << -1 << '\n';
            continue;
        }

        vector<char> visited2(V, 0);
        vector<int> chooseEdge(S, 0);
        function<int(int,int,int)> dfs = [&](int u, int parentEdge, int parent) -> int {
            visited2[u] = 1;
            int cur = 0;
            for (auto &p : adj[u]) {
                int v = p.first;
                int eid = p.second;
                if (v == parent) continue;
                if (!visited2[v]) {
                    int childChoice = dfs(v, eid, u);
                    if (childChoice) {
                        chooseEdge[eid] = 1;
                        cur ^= 1;
                    }
                }
            }
            if (parentEdge != -1) {
                int chooseParent = (cur != need[u]) ? 1 : 0;
                return chooseParent;
            } else {
                return 0;
            }
        };

        for (int i = 0; i < V; ++i) if (!visited2[i]) {
            dfs(i, -1, -1);
        }

        int X = 0;
        for (int i = 0; i < S; ++i) if (chooseEdge[i]) ++X;
        cout << X;
        for (int i = 0; i < S; ++i) if (chooseEdge[i]) cout << ' ' << i;
        cout << '\n';
    }
    return 0;
}
