// RNA Secondary Structure
// UVa ID: 12547
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.830s

#include <bits/stdc++.h>
using namespace std;

bool canPair(char a, char b) {
    return (a == 'A' && b == 'U') || (a == 'U' && b == 'A') ||
           (a == 'C' && b == 'G') || (a == 'G' && b == 'C');
}

bool isCg(char a, char b) {
    return (a == 'C' && b == 'G') || (a == 'G' && b == 'C');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test;
    cin >> test;
    for (int cas = 1; cas <= test; cas++) {
        string code;
        int k;
        cin >> code >> k;
        vector<char> type;
        vector<int> count;
        for (int i = 0; i < (int)code.size();) {
            char c = code[i++];
            int num = 0;
            while (i < (int)code.size() && isdigit(code[i])) {
                num = num * 10 + code[i++] - '0';
            }
            type.push_back(c);
            count.push_back(num);
        }
        if (type.size() == 1) {
            cout << "Case " << cas << ": 0\n";
            continue;
        }
        int midLen = 0;
        for (int i = 1; i + 1 < (int)type.size(); i++) midLen += count[i];
        int base = 0;
        if (canPair(type.front(), type.back())) {
            base = min(count.front(), count.back());
            if (isCg(type.front(), type.back())) base = min(base, k);
        }
        int leftCnt = min(count.front() - base, midLen);
        int rightCnt = min(count.back() - base, midLen);
        int leftRemain = count.front() - base;
        int rightRemain = count.back() - base;
        if (leftRemain > midLen) leftRemain = midLen;
        if (rightRemain > midLen) rightRemain = midLen;
        string s;
        s.append(leftRemain, type.front());
        for (int i = 1; i + 1 < (int)type.size(); i++) s.append(count[i], type[i]);
        s.append(rightRemain, type.back());
        int n = s.size();
        int remainK = k;
        if (isCg(type.front(), type.back())) remainK -= base;
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(remainK + 1, 0)));
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                for (int used = 0; used <= remainK; used++) {
                    dp[l][r][used] = dp[l + 1][r][used];
                    for (int j = l + 1; j <= r; j++) {
                        if (!canPair(s[l], s[j])) continue;
                        int cost = isCg(s[l], s[j]) ? 1 : 0;
                        if (cost > used) continue;
                        for (int inside = 0; inside + cost <= used; inside++) {
                            int insideValue = j == l + 1 ? 0 : dp[l + 1][j - 1][inside];
                            int rightValue = j == r ? 0 : dp[j + 1][r][used - cost - inside];
                            dp[l][r][used] = max(dp[l][r][used], insideValue + rightValue + 1);
                        }
                    }
                }
            }
        }
        int answer = base;
        if (n > 0) answer += dp[0][n - 1][remainK];
        cout << "Case " << cas << ": " << answer << '\n';
    }
    return 0;
}
