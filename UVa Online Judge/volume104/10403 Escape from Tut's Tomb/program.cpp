// Escape from Tut's Tomb
// UVa ID: 10403
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXS = 400; // 足够容纳 totalSum <= 351

int n, m;
int fullMask;
int totalSum;
vector<pair<int, char>> constraints; // leftMask, op
int weight[26];
bool used[27];

bool canMakeSum(int cnt, int target, const vector<int>& rem) {
    if (cnt == 0) return target == 0;
    if (target < 0 || target >= MAXS) return false;
    vector<bitset<MAXS>> dp(cnt + 1);
    dp[0][0] = 1;
    for (int x : rem) {
        for (int c = cnt; c >= 1; --c) {
            dp[c] |= (dp[c - 1] << x);
        }
    }
    return dp[cnt][target];
}

bool checkConstraints() {
    vector<int> rem;
    for (int i = 1; i <= n; ++i) if (!used[i]) rem.push_back(i);
    sort(rem.begin(), rem.end());
    int sz = (int)rem.size();
    vector<int> pref(sz + 1, 0);
    for (int i = 0; i < sz; ++i) pref[i + 1] = pref[i] + rem[i];
    auto getMinSum = [&](int cnt) { return cnt == 0 ? 0 : pref[cnt]; };
    auto getMaxSum = [&](int cnt) { return cnt == 0 ? 0 : pref[sz] - pref[sz - cnt]; };
    for (auto &c : constraints) {
        int leftMask = c.first;
        char op = c.second;
        int rightMask = fullMask ^ leftMask;
        int leftSum = 0, rightSum = 0;
        int leftCnt = 0, rightCnt = 0;
        for (int i = 0; i < n; ++i) {
            if (leftMask & (1 << i)) {
                if (weight[i] != -1) leftSum += weight[i];
                else ++leftCnt;
            } else {
                if (weight[i] != -1) rightSum += weight[i];
                else ++rightCnt;
            }
        }
        int minLeft = leftSum + getMinSum(leftCnt);
        int maxLeft = leftSum + getMaxSum(leftCnt);
        int minRight = rightSum + getMinSum(rightCnt);
        int maxRight = rightSum + getMaxSum(rightCnt);
        if (op == '<') {
            if (minLeft >= maxRight) return false;
        } else if (op == '>') {
            if (maxLeft <= minRight) return false;
        } else { // '='
            // 区间必要条件
            if (max(minLeft, minRight) > min(maxLeft, maxRight)) return false;
            // 精确判断：由等式推出左边未知子集和必须为 target
            int numerator = totalSum - 2 * leftSum;
            if (numerator % 2 != 0) return false;
            int target = numerator / 2;
            if (target < getMinSum(leftCnt) || target > getMaxSum(leftCnt)) return false;
            if (!canMakeSum(leftCnt, target, rem)) return false;
        }
    }
    return true;
}

bool dfs(int idx) {
    if (idx == n) return true;
    for (int w = 1; w <= n; ++w) {
        if (!used[w]) {
            weight[idx] = w;
            used[w] = true;
            if (checkConstraints()) {
                if (dfs(idx + 1)) return true;
            }
            used[w] = false;
            weight[idx] = -1;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m) {
        string line;
        getline(cin, line); // 读取第一行后的换行
        vector<pair<int, char>> raw;
        for (int i = 0; i < m; ++i) {
            getline(cin, line);
            vector<char> chars;
            for (char ch : line) if (!isspace(ch)) chars.push_back(ch);
            int sep = -1;
            for (int j = 0; j < (int)chars.size(); ++j)
                if (chars[j] == '<' || chars[j] == '=' || chars[j] == '>') {
                    sep = j;
                    break;
                }
            int leftMask = 0;
            for (int j = 0; j < sep; ++j) {
                char ch = chars[j];
                int idx;
                if (ch >= 'a' && ch <= 'z') idx = ch - 'a';
                else if (ch >= 'A' && ch <= 'Z') idx = ch - 'A';
                else continue;
                leftMask |= (1 << idx);
            }
            char op = chars[sep];
            raw.push_back({leftMask, op});
        }
        // 去重
        set<pair<int, char>> s(raw.begin(), raw.end());
        constraints.assign(s.begin(), s.end());
        fullMask = (1 << n) - 1;
        totalSum = n * (n + 1) / 2;
        for (int i = 0; i < n; ++i) weight[i] = -1;
        for (int i = 1; i <= n; ++i) used[i] = false;
        if (dfs(0)) {
            cout << "Solution:";
            for (int i = 0; i < n; ++i) cout << " " << weight[i];
            cout << "\n";
        } else cout << "No solution possible!\n";
    }
    return 0;
}
