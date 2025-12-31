// String Morphing
// UVa ID: 10981
// Verdict: Accepted
// Submission Date: 2025-12-30
// UVa Run Time: 0.550s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 特殊乘法表
char mult(char left, char right) {
    static const string table = "abc";
    static const char res[3][3] = {
        {'b', 'b', 'a'},
        {'c', 'b', 'a'},
        {'a', 'c', 'c'}
    };
    int li = left - 'a';
    int ri = right - 'a';
    return res[li][ri];
}

// 记录每个区间能变成的字符集合（用位掩码表示）
// 同时记录合并路径：par[i][j][ch] = 分割点k，左右子区间的结果字符
const int MAXN = 105;
int dp[MAXN][MAXN]; // 位掩码：1<<0='a', 1<<1='b', 1<<2='c'
pair<int, pair<char, char>> par[MAXN][MAXN][3]; // par[i][j][c] = (k, leftChar, rightChar)

bool solve(const string& s, char target) {
    int n = s.size();
    memset(dp, 0, sizeof(dp));

    // 初始化长度为1的区间
    for (int i = 0; i < n; i++) {
        int idx = s[i] - 'a';
        dp[i][i] = (1 << idx);
    }

    // 区间DP
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                int leftMask = dp[i][k];
                int rightMask = dp[k + 1][j];
                if (leftMask == 0 || rightMask == 0) continue;

                // 枚举左右可能的字符组合
                for (int li = 0; li < 3; li++) if (leftMask & (1 << li))
                    for (int ri = 0; ri < 3; ri++) if (rightMask & (1 << ri)) {
                        char lc = 'a' + li;
                        char rc = 'a' + ri;
                        char res = mult(lc, rc);
                        int ridx = res - 'a';
                        dp[i][j] |= (1 << ridx);
                        // 记录第一个可行的分割点（因为从左到右枚举k）
                        if (par[i][j][ridx].first == -1) {
                            par[i][j][ridx] = {k, {lc, rc}};
                        }
                    }
            }
        }
    }

    int tidx = target - 'a';
    return (dp[0][n - 1] & (1 << tidx)) != 0;
}

// 递归构造并输出变换步骤
vector<string> steps;
void buildPath(const string& s, int i, int j, char target) {
    if (i == j) return;
    int tidx = target - 'a';
    auto& p = par[i][j][tidx];
    int k = p.first;
    char lc = p.second.first;
    char rc = p.second.second;
    char res = mult(lc, rc); // 应等于target
    // 递归处理左区间
    buildPath(s, i, k, lc);
    // 递归处理右区间
    buildPath(s, k + 1, j, rc);
    // 构造当前步骤字符串
    string cur;
    for (int idx = i; idx <= j; idx++) cur += s[idx];
    steps.push_back(cur);
}

// 每次合并后更新字符串
string mergeString(const string& s, int i, int j, char target) {
    int tidx = target - 'a';
    auto& p = par[i][j][tidx];
    int k = p.first;
    char lc = p.second.first;
    char rc = p.second.second;
    // 递归合并左右区间
    string leftStr = (i == k) ? string(1, lc) : mergeString(s, i, k, lc);
    string rightStr = (k + 1 == j) ? string(1, rc) : mergeString(s, k + 1, j, rc);
    return leftStr + rightStr;
}

void outputSteps(const string& s, char target) {
    steps.clear();
    int n = s.size();
    // 先记录原始字符串
    steps.push_back(s);
    string cur = s;
    // 逐步合并，每次合并最左边可合并的两个字符
    while (cur.size() > 1) {
        // 从左到右找第一个可合并的位置，使得合并后仍可能达到target
        bool found = false;
        for (int i = 0; i < cur.size() - 1; i++) {
            char lc = cur[i];
            char rc = cur[i + 1];
            char res = mult(lc, rc);
            // 临时构造新字符串
            string nextStr = cur.substr(0, i) + res + cur.substr(i + 2);
            // 判断新字符串是否能变成target
            memset(dp, 0, sizeof(dp));
            if (solve(nextStr, target)) {
                cur = nextStr;
                steps.push_back(cur);
                found = true;
                break;
            }
        }
        if (!found) break;
    }
    // 输出步骤
    for (const string& step : steps) cout << step << endl;
}

int main() {
    int t; cin >> t;
    bool firstCase = true;
    while (t--) {
        if (!firstCase) cout << endl;
        firstCase = false;

        string s; cin >> s;
        char target; cin >> target;

        // 初始化par数组
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                for (int ch = 0; ch < 3; ch++)
                    par[i][j][ch].first = -1;

        if (solve(s, target)) outputSteps(s, target);
        else cout << "None exist!" << endl;
    }
    return 0;
}
