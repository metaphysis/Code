// Parenthesizing Palindromes
// UVa ID: 10788
// Verdict: Accepted
// Submission Date: 2025-12-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
int dp[MAXN][MAXN];
string s;

int dfs(int l, int r) {
    // 区间长度必须为偶数
    if ((r - l + 1) % 2) return 0;
    // 当为相邻两个字符，如果相等则表明可以组成一对括号，否则无法构成合法的括号
    if (l + 1 == r) return s[l] == s[r];
    // 返回备忘值
    if (~dp[l][r]) return dp[l][r];
    int &answer = dp[l][r];
    answer = 0;
    if (s[l] == s[r]) answer = dfs(l + 1, r - 1);
    if (answer > 2) answer = 2;
    for (int i = l + 1; i < r; i++) {
        if (s[l] == s[i]) answer += dfs(l, i) * dfs(i + 1, r);
        if (answer > 2) answer = 2;
    }
    return answer;
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case " << t << ": ";
        cin >> s;
        int n = s.size();
        if (n % 2) { cout << "Invalid\n"; continue; }
        memset(dp, -1, sizeof(dp));
        int answer = dfs(0, n - 1);
        if (answer == 0) cout << "Invalid\n";
        else if (answer == 1) cout << "Valid, Unique\n";
        else cout << "Valid, Multiple\n";
    }
    return 0;
}
