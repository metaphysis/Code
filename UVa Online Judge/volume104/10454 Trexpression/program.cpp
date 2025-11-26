// Trexpression
// UVa ID: 10454
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.300s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 256;
long long dp[MAXN][MAXN];
string expression;

long long dfs(int l, int r) {
    if (l > r) return 1;
    if (l == r) return 1;
    if (dp[l][r] != -1) return dp[l][r];
    
    long long &result = dp[l][r];
    result = 0;
    
    int left = 0, hasPlus = 0, hasMultiply = 0;
    
    // 扫描当前区间，找出括号外的运算符
    for (int i = l; i <= r; i++) {
        if (expression[i] == '(') left++;
        else if (expression[i] == ')') left--;
        else {
            if (left == 0) {
                if (expression[i] == '+') hasPlus = 1;
                if (expression[i] == '*') hasMultiply = 1;
            }
        }
    }
    
    // 如果整个表达式被括号包围且没有外层运算符，去掉括号
    if (hasPlus == 0 && hasMultiply == 0 && expression[l] == '(' && expression[r] == ')') 
        result += dfs(l + 1, r - 1);
    
    // 枚举分裂点
    left = 0;
    for (int i = l; i <= r; i++) {
        if (expression[i] == '(') left++;
        else if (expression[i] == ')') left--;
        else {
            if (left == 0) {
                if (expression[i] == '+') 
                    result += dfs(l, i - 1) * dfs(i + 1, r);
                if (expression[i] == '*' && hasPlus == 0) 
                    result += dfs(l, i - 1) * dfs(i + 1, r);
            }
        }
    }
    
    return result;
}

int main() {
    while (getline(cin, expression)) {
        memset(dp, -1, sizeof(dp));
        long long result = dfs(0, expression.length() - 1);
        cout << result << endl;
    }
    return 0;
}
