#include <bits/stdc++.h>
using namespace std;

int solveCase(const string &str, const string &bad) {
    int n = str.size(), ans = 0;
    bool badChar[256] = {};
    for (char ch : bad)
        badChar[(unsigned char)ch] = true;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (!badChar[(unsigned char)str[i]] && !badChar[(unsigned char)str[j]] && str[i] == str[j]) {
                dp[i][j] = dp[i + 1][j + 1] + 1;
                ans = max(ans, min(dp[i][j], j - i));
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    string str, bad;
    cin >> t;
    getline(cin, str);
    for (int caseId = 1; caseId <= t; caseId++) {
        getline(cin, str);
        if (!str.empty() && str.back() == '\r')
            str.pop_back();
        getline(cin, bad);
        if (!bad.empty() && bad.back() == '\r')
            bad.pop_back();
        cout << "Case #" << caseId << ": " << solveCase(str, bad) << '\n';
    }
    return 0;
}
