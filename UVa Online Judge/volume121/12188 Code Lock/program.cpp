// Code Lock
// UVa ID: 12188
// Verdict: Accepted
// Submission Date: 2026-08-03
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

int solve(const string &s) {
    int n = s.length();
    vector<int> diff(n + 1);
    diff[0] = s[0] - 'a';
    for (int i = 1; i < n; i++) {
        diff[i] = (s[i] - s[i - 1] + 26) % 26;
    }
    diff[n] = (26 - (s[n - 1] - 'a')) % 26;
    int total = 0;
    for (int value : diff) total += value;
    sort(diff.begin(), diff.end(), greater<int>());
    int cnt = total / 26;
    int ans = total;
    for (int i = 0; i < cnt; i++) ans -= diff[i];
    return ans;
}

int main() {
    string s;
    while (cin >> s) {
        if (s == "*") return 0;
        cout << solve(s) << '\n';
    }
    return 0;
}
