// Assembly Line
// UVa ID: 12276
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.500s
// https://blog.csdn.net/metaphysis/article/details/163220706

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int timeTable[26][26];
int resultTable[26][26];

// 求解单个字符串的最优组装时间和结果类型
pair<int, char> solveString(const string& s, int k, const vector<char>& symbols, const vector<int>& order) {
    int n = (int)s.length();
    // dp[i][j][t] 表示区间 [i, j] 合并成类型 t 的最小时间
    vector<vector<array<int, 26>>> dp(n, vector<array<int, 26>>(n));
    // reach[i][j] 存储区间 [i, j] 可达的所有类型索引
    vector<vector<vector<int>>> reach(n, vector<vector<int>>(n));
    // 初始化所有 dp 为 INF
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int t = 0; t < k; ++t)
                dp[i][j][t] = INF;
    // 长度为 1 的区间
    for (int i = 0; i < n; ++i) {
        int idx = order[s[i] - 'a'];
        dp[i][i][idx] = 0;
        reach[i][i].push_back(idx);
    }
    // 区间 DP，按长度递增
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            // 清空当前区间的 dp，准备合并
            for (int t = 0; t < k; ++t) dp[i][j][t] = INF;
            for (int mid = i; mid < j; ++mid) {
                const auto& leftReach = reach[i][mid];
                const auto& rightReach = reach[mid + 1][j];
                for (int l : leftReach) {
                    int leftTime = dp[i][mid][l];
                    for (int r : rightReach) {
                        int rightTime = dp[mid + 1][j][r];
                        int t = resultTable[l][r];
                        int cost = leftTime + rightTime + timeTable[l][r];
                        if (cost < dp[i][j][t]) dp[i][j][t] = cost;
                    }
                }
            }
            // 收集当前区间可达的类型
            for (int t = 0; t < k; ++t)
                if (dp[i][j][t] != INF) reach[i][j].push_back(t);
        }
    }
    // 寻找全局最小时间，若有并列选择符号列表中靠前的类型（索引小优先）
    int minTime = INF, bestIdx = 0;
    for (int t = 0; t < k; ++t) {
        if (dp[0][n - 1][t] < minTime) {
            minTime = dp[0][n - 1][t];
            bestIdx = t;
        }
    }
    return {minTime, symbols[bestIdx]};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    bool firstCase = true;
    while (cin >> k && k) {
        // 每个测试用例之间输出空行
        if (!firstCase) cout << '\n';
        firstCase = false;
        vector<char> symbols(k);
        vector<int> order(26, -1);
        for (int i = 0; i < k; ++i) {
            cin >> symbols[i];
            order[symbols[i] - 'a'] = i;
        }
        // 读入组装表
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                string token;
                cin >> token;
                size_t pos = token.find('-');
                int time = stoi(token.substr(0, pos));
                char resChar = token[pos + 1];
                int resIdx = order[resChar - 'a'];
                timeTable[i][j] = time;
                resultTable[i][j] = resIdx;
            }
        }
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            auto ans = solveString(s, k, symbols, order);
            cout << ans.first << '-' << ans.second << '\n';
        }
    }
    return 0;
}
