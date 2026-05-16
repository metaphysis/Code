#include <bits/stdc++.h>
using namespace std;

int n;
long long dp[20][10][2][2];  // 状态定义：dp[pos][last][tight][lead]
string s; // 将范围转换为字符串形式

long long dfs(int pos, int last, bool tight, bool lead) {
    // 如果前导零标志为假，表明成功构造了一个有效数
    if (pos == n) return !lead ? 1 : 0;
    // 记忆化技巧，避免重复计数，从而提高效率
    if (~dp[pos][last][tight][lead]) return dp[pos][last][tight][lead];
    long long r = 0;
    // 分情况进行状态的转移
    if (lead) {
        // 情况1：当前位继续不填（前导零）
        r += dfs(pos + 1, 0, false, true);
        // 情况2：当前位作为第一位开始填数
        int start = 1, end = tight ? (s[pos] - '0') : 9;
        for (int d = start; d <= end; d++)
            r += dfs(pos + 1, d, tight && (d == end), false);
    } else {
        // 情况3：已经开始填数，正常处理
        int start = 0, end = tight ? (s[pos] - '0') : 9;
        for (int d = start; d <= end; d++)
            if (abs(d - last) >= 2)
                r += dfs(pos + 1, d, tight && (d == end), false);
    }
    // 实际上，可以将上述三种情况予以合并，这样代码更为简洁
    // if (lead) r += dfs(pos + 1, 0, false, true);
    // int start = lead ? 1 : 0, end = tight ? (s[pos] - '0') : 9;
    // for (int d = start ; d <= end; d++)
    //     if (lead || abs(d - last) >= 2)
    //         r += dfs(pos + 1, d, tight && (d == end), false);
    return dp[pos][last][tight][lead] = r;
}

long long solve(long long x) {
    if (x == 0) return 0;
    s = to_string(x);
    n = s.length();
    memset(dp, -1, sizeof(dp));
    return dfs(0, 0, true, true);
}

int main() {
    long long L, R;
    while (cin >> L >> R) cout << (solve(R) - solve(L - 1)) << '\n';
    return 0;
}
