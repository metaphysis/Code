#include <bits/stdc++.h>
using namespace std;

const int mod = 100007;

int dp[511][30], mark[511][30], freq[30];
int patternLen, passId;

int dfs(int freeCount, int index) {
    if (mark[freeCount][index] == passId) return dp[freeCount][index];
    mark[freeCount][index] = passId;
    if (freeCount == 0 && index >= patternLen) return dp[freeCount][index] = 1;
    int result = 0;
    if (freeCount > 0) result = (result + freeCount * dfs(freeCount - 1, index)) % mod;
    if (index < patternLen && freq[index] > 0) result = (result + freq[index] * dfs(freeCount + freq[index] - 1, index + 1)) % mod;
    return dp[freeCount][index] = result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int caseId = 1; caseId <= T; caseId++) {
        string s, p;
        cin >> s >> p;
        int countChar[26] = {}, freeCount = s.size();
        for (char ch : s) countChar[ch - 'A']++;
        patternLen = p.size();
        bool possible = true;
        for (int i = 0; i < patternLen; i++) {
            freq[i] = countChar[p[i] - 'A'];
            if (freq[i] == 0) possible = false;
            freeCount -= freq[i];
        }
        passId++;
        if (possible) cout << "Case " << caseId << ": " << dfs(freeCount, 0) << '\n';
        else cout << "Case " << caseId << ": 0\n";
    }
    return 0;
}
