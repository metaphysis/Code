// Fibonacci Words
// UVa ID: 1282
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int MAXN = 105;

struct FibData {
    ull count;
    string prefix, suffix;
};

FibData dp[MAXN];
string pattern;
int patternLen;
vector<int> lps;

void computeLPS() {
    lps.resize(patternLen);
    lps[0] = 0;
    int len = 0, i = 1;
    while (i < patternLen) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else {
            if (len != 0) len = lps[len - 1];
            else lps[i++] = 0;
        }
    }
}

ull kmpCount(const string &text) {
    int n = text.size();
    if (n < patternLen) return 0;
    ull res = 0;
    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) { i++; j++; }
        if (j == patternLen) { res++; j = lps[j - 1]; }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return res;
}

void solve(int n) {
    if (dp[n].count != -1) return;
    if (n == 0) {
        dp[n].count = kmpCount("0");
        dp[n].prefix = dp[n].suffix = "0";
        return;
    }
    if (n == 1) {
        dp[n].count = kmpCount("1");
        dp[n].prefix = dp[n].suffix = "1";
        return;
    }
    solve(n - 1);
    solve(n - 2);
    
    string suffixPart = dp[n - 1].suffix;
    string prefixPart = dp[n - 2].prefix;
    if (suffixPart.size() > patternLen - 1) suffixPart = suffixPart.substr(suffixPart.size() - (patternLen - 1));
    if (prefixPart.size() > patternLen - 1) prefixPart = prefixPart.substr(0, patternLen - 1);
    ull cross = (suffixPart + prefixPart).size() >= patternLen ? kmpCount(suffixPart + prefixPart) : 0;
    
    dp[n].count = dp[n - 1].count + dp[n - 2].count + cross;
    
    dp[n].prefix = dp[n - 1].prefix;
    if (dp[n].prefix.size() < patternLen - 1) {
        string temp = dp[n - 1].prefix + dp[n - 2].prefix;
        dp[n].prefix = temp.size() > patternLen - 1 ? temp.substr(0, patternLen - 1) : temp;
    }
    
    dp[n].suffix = dp[n - 2].suffix;
    if (dp[n].suffix.size() < patternLen - 1) {
        string temp = dp[n - 1].suffix + dp[n - 2].suffix;
        dp[n].suffix = temp.size() > patternLen - 1 ? temp.substr(temp.size() - (patternLen - 1)) : temp;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, caseNo = 1;
    while (cin >> n) {
        cin >> pattern;
        patternLen = pattern.size();
        computeLPS();
        for (int i = 0; i < MAXN; i++) dp[i].count = -1;
        solve(n);
        cout << "Case " << caseNo++ << ": " << dp[n].count << "\n";
    }
    return 0;
}
