// The Joys of Farming
// UVa ID: 11331
// Verdict: Accepted
// Submission Date: 2023-04-26
// UVa Run Time: 0.050s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
vector<int> g[2010];
int visited[2010], black, white, no;
int dp[2010][2010];
void dfs(int u, int mark) {
    if (no) return;
    visited[u] = mark;
    if (mark == 0) black++;
    else white++;
    for (auto v : g[u])
        if (visited[v] == -1)
            dfs(v, 1 - mark);
        else {
            if (visited[v] == mark) {
                no = 1;
                return;
            }
        }
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, b, c, a, t;
    cin >> T;
    while (T--) {
        cin >> b >> c >> a;
        if (a == 0) { cout << "yes\n"; continue; }
        t = b + c;
        for (int i = 1; i <= t; i++) g[i].clear();
        for (int i = 0, u, v; i < a; i++) {
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        memset(visited, -1, sizeof visited);
        memset(dp, 0, sizeof dp);
        dp[0][0] = 1;
        int row = 0, cnt = 0;
        for (int i = 1; i <= t; i++)
            if (visited[i] == -1) {
                no = black = white = 0;
                dfs(i, 0);
                if (no) break;
                cnt += black + white;
                for (int k = 0; k <= cnt; k++)
                    if (dp[row][k]) {
                        if (k + black <= cnt) dp[row + 1][k + black] = 1;
                        if (k + white <= cnt) dp[row + 1][k + white] = 1;
                    }
                row++;
            }
        if (no) { cout << "no\n"; continue; }
        if (b > c) swap(b, c);
        int flag = 0;
        for (int i = 1; i <= t; i++)
            if (dp[row][i]) {
                int bb = i, cc = cnt - i;
                if (bb > cc) swap(bb, cc);
                if (bb <= b && cc <= c) {
                    flag = 1;
                    break;
                }
            }
        if (flag) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}
