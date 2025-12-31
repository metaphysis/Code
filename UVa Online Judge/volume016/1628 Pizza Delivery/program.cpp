// Pizza Delivery
// UVa ID: 1628
// Verdict: Accepted
// Submission Date: 2025-12-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int cases;
int n;
int pos[MAXN], earn[MAXN];
int dp[MAXN][MAXN][MAXN][2];
bool visited[MAXN][MAXN][MAXN][2];

// s,e: 已经考虑了区间[s,e]（这些顾客不送）
// cnt: 还需要送的顾客数量
// position: 0=在s位置，1=在e位置
int dfs(int s, int e, int cnt, int position) {
    if (cnt == 0) return 0;
    if (visited[s][e][cnt][position]) return dp[s][e][cnt][position];
    visited[s][e][cnt][position] = true;
    int &answer = dp[s][e][cnt][position];
    answer = 0;
    int currentPos = (position == 0) ? pos[s] : pos[e];
    // 考虑下一个要送的顾客
    if (position == 0) {  // 当前在s位置
        // 选择左边还没考虑的顾客（0 ~ s-1）
        for (int i = 0; i < s; i++) {
            int distance = abs(pos[i] - currentPos);
            int profit = earn[i] - cnt * distance;
            answer = max(answer, profit + dfs(i, e, cnt - 1, 0));
        }
        // 选择右边还没考虑的顾客（e+1 ~ n-1）
        for (int i = e + 1; i < n; i++) {
            int distance = abs(pos[i] - currentPos);
            int profit = earn[i] - cnt * distance;
            answer = max(answer, profit + dfs(s, i, cnt - 1, 1));
        }
    } else {  // 当前在e位置
        // 选择左边还没考虑的顾客（0 ~ s-1）
        for (int i = 0; i < s; i++) {
            int distance = abs(pos[i] - currentPos);
            int profit = earn[i] - cnt * distance;
            answer = max(answer, profit + dfs(i, e, cnt - 1, 0));
        }
        // 选择右边还没考虑的顾客（e+1 ~ n-1）
        for (int i = e + 1; i < n; i++) {
            int distance = abs(pos[i] - currentPos);
            int profit = earn[i] - cnt * distance;
            answer = max(answer, profit + dfs(s, i, cnt - 1, 1));
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (cases = 1; cases <= T; cases++) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> pos[i];
        for (int i = 0; i < n; i++) cin >> earn[i];
        // 初始化visited数组
        memset(visited, 0, sizeof(visited));
        int answer = 0;
        // 枚举总共要送的人数k
        for (int k = 1; k <= n; k++) {
            // 枚举第一个送的顾客
            for (int i = 0; i < n; i++) {
                // 从0点出发到顾客i，花费时间abs(pos[i])，产生罚金k * abs(pos[i])
                int profit = earn[i] - k * abs(pos[i]);
                answer = max(answer, profit + dfs(i, i, k - 1, 0));
            }
        }
        cout << answer << "\n";
    }
    return 0;
}
