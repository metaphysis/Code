// Brackets Sequence
// UVa ID: 1626
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.330s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 105;
const int INF = 1e9;

int dp[MAXN][MAXN];  // dp[i][j]：子串s[i..j]的最短合法超序列长度
int path[MAXN][MAXN]; // 记录构造路径
string s;

// 判断两个字符是否匹配的括号
bool match(char a, char b) {
    return (a == '(' && b == ')') || (a == '[' && b == ']');
}

// 递归构造最优解
void print(int i, int j) {
    if (i > j) return;
    if (i == j) { // 单字符情况
        if (s[i] == '(' || s[i] == ')') cout << "()";
        else cout << "[]";
        return;
    }
    if (path[i][j] == -1) { // 两端加括号的情况
        cout << s[i];
        print(i + 1, j - 1);
        cout << s[j];
    } else { // 分割的情况
        int k = path[i][j];
        print(i, k);
        print(k + 1, j);
    }
}

void solve() {
    int n = s.length();
    if (n == 0) {
        cout << "\n";
        return;
    }

    // 初始化DP数组
    for (int i = 0; i < n; i++) {
        dp[i][i] = 2; // 单字符需要两个字符的括号对
        dp[i + 1][i] = 0; // 空串长度为0
    }

    // 区间DP
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;

            // 情况1：如果两端字符匹配
            if (match(s[i], s[j])) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
                path[i][j] = -1;
            }

            // 情况2：枚举分割点
            for (int k = i; k < j; k++) {
                if (dp[i][k] + dp[k + 1][j] < dp[i][j]) {
                    dp[i][j] = dp[i][k] + dp[k + 1][j];
                    path[i][j] = k;
                }
            }
        }
    }

    // 输出结果
    print(0, n - 1);
    cout << "\n";
}

int main() {
    int t;
    cin >> t;
    cin.ignore(); // 忽略第一行末尾的换行
    while (t--) {
        getline(cin, s); // 读取空行或数据
        if (s.empty()) getline(cin, s); // 如果读到空行，再读一次
        solve();
        if (t) cout << "\n"; // 输出案例间空行
    }
    return 0;
}
