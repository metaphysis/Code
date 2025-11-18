// Rigging Elections
// UVa ID: 11748
// Verdict: Accepted
// Submission Date: 2025-11-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, c;
    while (cin >> n >> m >> c && (n || m || c)) {
        vector<vector<int>> ballots(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> ballots[i][j];
            }
        }

        vector<vector<bool>> beat(n + 1, vector<bool>(n + 1, false));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) continue;
                int wins = 0;
                for (int k = 0; k < m; k++) {
                    int posI = find(ballots[k].begin(), ballots[k].end(), i) - ballots[k].begin();
                    int posJ = find(ballots[k].begin(), ballots[k].end(), j) - ballots[k].begin();
                    if (posI < posJ) wins++;
                }
                if (wins > m / 2) beat[i][j] = true;
            }
        }

        vector<bool> visited(n + 1, false);
        queue<int> q;
        q.push(c);
        visited[c] = true;
        int count = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 1; v <= n; v++) {
                if (!visited[v] && beat[u][v]) {
                    visited[v] = true;
                    count++;
                    q.push(v);
                }
            }
        }

        if (count == n) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}
