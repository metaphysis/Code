// Arranging Cards
// UVa ID: 11421
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.280s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

typedef cpp_int bigint;

bigint C[55][55], fact[55];

void init() {
    for (int i = 0; i <= 50; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    fact[0] = 1;
    for (int i = 1; i <= 50; ++i) fact[i] = fact[i - 1] * i;
}

bigint productFact(const vector<int>& cnt) {
    bigint res = 1;
    for (int x : cnt) res *= fact[x];
    return res;
}

// 返回只考虑 rank 的合法排列数，若 forbidden 为 -1 表示无首项限制，
// 否则要求首项不能是 forbidden 这个 rank。
bigint rankWays(const vector<int>& cnt, int forbidden) {
    int N = 0;
    for (int x : cnt) N += x;
    // 常规 DP，计算所有合法 rank 序列数
    vector<bigint> dp(N + 1, 0);
    dp[0] = 1;
    int curMax = 0;
    for (int i = 0; i < 13; ++i) {
        if (cnt[i] == 0) continue;
        vector<bigint> ndp(N + 1, 0);
        for (int j = 0; j < cnt[i]; ++j) {
            int k = cnt[i] - j;
            bigint coeff = C[cnt[i] - 1][j];
            if (j & 1) coeff = -coeff;
            for (int b = 0; b <= curMax; ++b) {
                if (dp[b] == 0) continue;
                ndp[b + k] += dp[b] * C[b + k][k] * coeff;
            }
        }
        dp.swap(ndp);
        curMax += cnt[i];
    }
    bigint F = 0;
    for (int b = 0; b <= N; ++b) F += dp[b];
    if (forbidden == -1) return F;
    if (cnt[forbidden] == 0) return F;
    // 计算首项为 forbidden 的合法排列数 H
    // 先计算除 forbidden 以外的 rank 的 DP
    vector<bigint> dpOther(N + 1, 0);
    dpOther[0] = 1;
    curMax = 0;
    for (int i = 0; i < 13; ++i) {
        if (i == forbidden || cnt[i] == 0) continue;
        vector<bigint> ndp(N + 1, 0);
        for (int j = 0; j < cnt[i]; ++j) {
            int k = cnt[i] - j;
            bigint coeff = C[cnt[i] - 1][j];
            if (j & 1) coeff = -coeff;
            for (int b = 0; b <= curMax; ++b) {
                if (dpOther[b] == 0) continue;
                ndp[b + k] += dpOther[b] * C[b + k][k] * coeff;
            }
        }
        dpOther.swap(ndp);
        curMax += cnt[i];
    }
    int f = forbidden;
    bigint H = 0;
    for (int j = 0; j < cnt[f]; ++j) {
        int kf = cnt[f] - j;
        bigint coeff = C[cnt[f] - 1][j];
        if (j & 1) coeff = -coeff;
        bigint sum = 0;
        for (int b = 0; b <= N; ++b) {
            if (dpOther[b] == 0) continue;
            // 将 kf - 1 个剩余的 f 块插入到 b 个非 f 块中
            sum += dpOther[b] * C[b + kf - 1][b];
        }
        H += coeff * sum;
    }
    return F - H;
}

bigint totalWays(const vector<int>& cnt) {
    return rankWays(cnt, -1) * productFact(cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    unordered_map<char, int> rankMap = {
        {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4},
        {'7', 5}, {'8', 6}, {'9', 7}, {'T', 8}, {'J', 9},
        {'Q', 10}, {'K', 11}, {'A', 12}
    };
    int n, caseNo = 0;
    long long kLL;
    while (cin >> n >> kLL && n != 0) {
        ++caseNo;
        vector<string> cards(n);
        for (int i = 0; i < n; ++i) cin >> cards[i];
        sort(cards.begin(), cards.end());
        vector<int> cnt(13, 0);
        for (const string& s : cards) cnt[rankMap[s[0]]]++;
        bigint K = kLL;
        if (totalWays(cnt) < K) {
            cout << "Case " << caseNo << ": Not found\n";
            continue;
        }
        vector<bool> used(n, false);
        vector<string> seq;
        int lastRank = -1;
        bool ok = true;
        for (int pos = 0; pos < n; ++pos) {
            bool chosen = false;
            for (int idx = 0; idx < n; ++idx) {
                if (used[idx]) continue;
                int r = rankMap[cards[idx][0]];
                if (r == lastRank) continue;
                // 尝试选择这张牌
                cnt[r]--;
                bigint ways = rankWays(cnt, r) * productFact(cnt);
                if (ways < K) {
                    K -= ways;
                    cnt[r]++;   // 恢复
                } else {
                    // 选中
                    used[idx] = true;
                    seq.push_back(cards[idx]);
                    lastRank = r;
                    chosen = true;
                    break;
                }
            }
            if (!chosen) {
                ok = false;
                break;
            }
        }
        if (!ok) cout << "Case " << caseNo << ": Not found\n";
        else {
            cout << "Case " << caseNo << ": ";
            for (int i = 0; i < (int)seq.size(); ++i) {
                if (i) cout << ' ';
                cout << seq[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
