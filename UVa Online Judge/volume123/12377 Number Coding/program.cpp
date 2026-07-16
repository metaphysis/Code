// Number Coding
// UVa ID: 12377
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long fact[10]; // 阶乘表，fact[i] = i!

// 比较两个字符串表示的整数（无前导零），返回 a <= b
bool isLessOrEqual(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a <= b;
}

int k;          // 当前测试用例的质因数个数
string S;       // 编码串去掉首字符后的剩余部分
long long ans;  // 当前测试用例的答案

// 深度优先搜索枚举所有分割
// idx: 当前处理的起始位置，parts: 已分割出的段数
// last: 上一段的字符串表示，cur: 当前已分割出的所有段
void dfs(int idx, int parts, const string& last, vector<string>& cur) {
    if (parts == k - 1) { // 最后一段直接取剩余部分
        string rem = S.substr(idx);
        if (rem.empty() || rem[0] == '0') return;          // 空串或前导零非法
        if (!last.empty() && !isLessOrEqual(last, rem)) return; // 不满足非递减
        cur.push_back(rem);
        // 统计各频率出现的次数
        map<string, int> mp;
        for (const auto& s : cur) mp[s]++;
        // 计算方案数：P(9, k) / prod(cnt(v)!)
        long long ways = fact[9] / fact[9 - k];
        for (const auto& p : mp) ways /= fact[p.second];
        ans += ways;
        cur.pop_back();
        return;
    }
    int remainParts = k - parts - 1; // 还需要分的段数（不包括当前段）
    int maxLen = (int)S.length() - idx - remainParts; // 当前段最大长度，保证后面每段至少1位
    for (int len = 1; len <= maxLen; ++len) {
        string sub = S.substr(idx, len);
        if (sub[0] == '0') continue;                     // 前导零非法
        if (!last.empty() && !isLessOrEqual(last, sub)) continue; // 不递增
        cur.push_back(sub);
        dfs(idx + len, parts + 1, sub, cur);
        cur.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 预计算阶乘
    fact[0] = 1;
    for (int i = 1; i <= 9; ++i) fact[i] = fact[i - 1] * i;
    int T;
    cin >> T;
    while (T--) {
        string C;
        cin >> C;
        k = C[0] - '0';          // 取首位作为质因数个数
        S = C.substr(1);         // 剩余部分
        ans = 0;
        if (k >= 1 && k <= 9 && (int)S.length() >= k) {
            vector<string> cur;
            dfs(0, 0, "", cur);
        }
        cout << ans << '\n';
    }
    return 0;
}
